//
// Created by adrian on 10/6/23.
//
#include "simulacion.hpp"

#include "../sim/progargs.hpp"

/*Simulacion::Simulacion() : num_iteraciones(0), num_particulas(0), ppm(0.0) {
                                             Calculadora inst_calculadora(ppm);
                                             calculadora = inst_calculadora;
                                             Malla inst_malla(calculadora.indice_bloques(),
   calculadora.indice_bloques(), calculadora.indice_bloques()) malla = inst_malla;
                                           };*/

// Etapa inicial de la simulación
void Simulacion::iterador() {
  if (num_iteraciones == 0) { return; }
  malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) {
    malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
  }
  poblar_malla();
  colisiones_particulas();
  colision_particula_limite();
  movimiento_particulas();
  rebote_particula_limite();
  for (int i = 1; i < num_iteraciones; i++) { iteracion(); }
}

void Simulacion::iteracion() {
  reposicionamiento();
  colisiones_particulas();
  colision_particula_limite();
  movimiento_particulas();
  rebote_particula_limite();
}

void Simulacion::poblar_malla() {
  for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d<int> bloque_coords = calc.indice_bloque(particulas.pos[cont]);
    bloque_coords               = malla.fuera_de_rango(bloque_coords);
    int const ind_real          = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    malla.bloques[ind_real].particulas.push_back(cont);
  }
}

// Sección 4.3.1 - Página 7 - Reposicionamiento de partículas en la malla
void Simulacion::reposicionamiento() {
  for (int i = 0; i < malla.tamano; i++) {
    // Limpio las partículas de cada bloue
    malla.bloques[i].particulas.clear();
  }
  // Y la vuelvo a repoblar
  for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d<int> bloque_coords = calc.indice_bloque(particulas.pos[cont]);
    bloque_coords               = malla.fuera_de_rango(bloque_coords);
    int const ind_real          = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    malla.bloques[ind_real].particulas.push_back(cont);
  }
}

// Sección 4.3.2 - Página 8 - Cálculo de las aceleraciones
void Simulacion::colisiones_particulas() {
  // En cada iteración se reinician los valores de densidad y aceleración para todas las particulas
  for (int i = 0; i < num_particulas; ++i) {
    particulas.dens[i]        = 0.0;
    particulas.aceleracion[i] = gravedad;
  }

  // Función encargada de actualizar las densidades de cada particula
  Simulacion::colisiones_particulas_densidad();
  // función para actualizar la aceleración de todas las particulas, cuyas densidades tienen que
  // estar actualizadas
  Simulacion::colisiones_particulas_aceleracion();
}

void Simulacion::colisiones_particulas_densidad() {
  for (int indice_bloque = 0; indice_bloque < malla.tamano; ++indice_bloque) {
    for (auto const & ind_part : malla.bloques[indice_bloque].particulas) {
      for (auto const & contiguo : malla.bloques[indice_bloque].bloques_contiguos) {
        for (int const & i_p_nueva : malla.bloques[contiguo].particulas) {
          if (i_p_nueva > ind_part) {
            double const distancia_cuadrado =
                Vector3d<double>::sq_distancia(particulas.pos[ind_part], particulas.pos[i_p_nueva]);
            if (distancia_cuadrado < (calc.suavizado * calc.suavizado)) {
              // comprobar que realmente interactuan
              double const cambio_densidad  = calc.delta_densidades(distancia_cuadrado);
              particulas.dens[ind_part]    += cambio_densidad;
              particulas.dens[i_p_nueva]   += cambio_densidad;  // actualizar ambas densidades
            }
          }
        }
      }
    }
  }
  for (int contador = 0; contador < num_particulas; contador++) {
    particulas.dens[contador] = calc.transform_densidad(particulas.dens[contador]);
  }
}


void Simulacion::colisiones_particulas_aceleracion() {
  for (int indice_bloque = 0; indice_bloque < malla.tamano; ++indice_bloque) {
    //std::vector<int> const contiguos = malla.bloques[indice_bloque].bloques_contiguos;
    for (auto const & part1 : malla.bloques[indice_bloque].particulas) {
      for (auto const & contiguo : malla.bloques[indice_bloque].bloques_contiguos) {
        for (int const & part2 : malla.bloques[contiguo].particulas) {
          if (part2 > part1) {
            double const distancia =
                Vector3d<double>::sq_distancia(particulas.pos[part1], particulas.pos[part2]);
            double const suavizado_cuadrado = (calc.suavizado * calc.suavizado);
            if (distancia < suavizado_cuadrado) {
              Vector3d<double> op_1 = calc.acel_p1(particulas.pos[part1], particulas.pos[part2],
                                                   particulas.dens[part1], particulas.dens[part2]);
              Vector3d<double> const op_2 =
                  calc.acel_p2(particulas.velocidad[part1], particulas.velocidad[part2]);
              Vector3d<double> const cambio_aceleracion = Calculadora::transferencia_aceleracion(
                  op_1, op_2, particulas.dens[part1] * particulas.dens[part2]);
              particulas.aceleracion[part1] += cambio_aceleracion;
              particulas.aceleracion[part2] -= cambio_aceleracion;
            }
          }
        }
      }
    }
  }
}


// Sección 4.3.3 - Página 9 - Colisiones de partículas (con límites)
// Eduardo Alarcón
void Simulacion::colision_particula_limite() {
  for (int i = 0; i < num_particulas; ++i) {
    int const c_x = calc.indice_bloque(particulas.pos[i]).x;
    if (c_x <= 0) {
      colision_particula_limite_x(i, 0);
    } else if (c_x >= malla.n_x - 1) {
      colision_particula_limite_x(i, -1);
    }
    int const c_y = calc.indice_bloque(particulas.pos[i]).y;
    if (c_y <= 0) {
      colision_particula_limite_y(i, 0);
    } else if (c_y >= malla.n_y - 1) {
      colision_particula_limite_y(i, -1);
    }
    int const c_z = calc.indice_bloque(particulas.pos[i]).z;
    if (c_z <= 0) {
      colision_particula_limite_z(i, 0);
    } else if (c_z >= malla.n_z - 1) {
      colision_particula_limite_z(i, -1);
    }
  }
}

void Simulacion::colision_particula_limite_x(int indice, int bloque) {
  double const nueva_x = particulas.pos[indice].x + particulas.gradiente[indice].x * delta_t;
  if (bloque == 0) {
    double const delta_x = d_p - (nueva_x - b_min.x);
    if (delta_x > dist_max_a_limite) {
      particulas.aceleracion[indice].x +=
          Calculadora::colisiones_limite_eje_x(bloque, delta_x, particulas.velocidad[indice]);
    }
  } else if (bloque == -1) {
    double const delta_x = d_p - (b_max.x - nueva_x);
    if (delta_x > dist_max_a_limite) {
      particulas.aceleracion[indice].x +=
          Calculadora::colisiones_limite_eje_x(bloque, delta_x, particulas.velocidad[indice]);
    }
  }
}

void Simulacion::colision_particula_limite_y(int indice, int bloque) {
  double const nueva_y = particulas.pos[indice].y + particulas.gradiente[indice].y * delta_t;
  if (bloque == 0) {
    double const delta_y = d_p - (nueva_y - b_min.y);
    if (delta_y > dist_max_a_limite) {
      particulas.aceleracion[indice].y +=
          Calculadora::colisiones_limite_eje_y(bloque, delta_y, particulas.velocidad[indice]);
    }
  } else if (bloque == -1) {
    double const delta_y = d_p - (b_max.y - nueva_y);
    if (delta_y > dist_max_a_limite) {
      particulas.aceleracion[indice].y +=
          Calculadora::colisiones_limite_eje_y(bloque, delta_y, particulas.velocidad[indice]);
    }
  }
}

void Simulacion::colision_particula_limite_z(int indice, int bloque) {
  double const nueva_z = particulas.pos[indice].z + particulas.gradiente[indice].z * delta_t;
  if (bloque == 0) {
    double const delta_z = d_p - (nueva_z - b_min.z);
    if (delta_z > dist_max_a_limite) {
      particulas.aceleracion[indice].z +=
          Calculadora::colisiones_limite_eje_z(bloque, delta_z, particulas.velocidad[indice]);
    }
  } else if (bloque == -1) {
    double const delta_z = d_p - (b_max.z - nueva_z);
    if (delta_z > dist_max_a_limite) {
      particulas.aceleracion[indice].z +=
          Calculadora::colisiones_limite_eje_z(bloque, delta_z, particulas.velocidad[indice]);
    }
  }
}

// Sección 4.3.4 - Página 10 - Movimiento de las partículas
void Simulacion::movimiento_particulas() {
  for (int i = 0; i < num_particulas; ++i) {
    particulas.pos[i] = Calculadora::actualizar_posicion(particulas.pos[i], particulas.gradiente[i],
                                                         particulas.aceleracion[i]);
    particulas.velocidad[i] =
        Calculadora::actualizar_velocidad(particulas.gradiente[i], particulas.aceleracion[i]);
    particulas.gradiente[i] =
        Calculadora::actualizar_gradiente(particulas.gradiente[i], particulas.aceleracion[i]);
  }
}

// Sección 4.3.5 - Página 11 - Interacciones con los límites del recinto
// Eduardo Alarcón
void Simulacion::rebote_particula_limite() {
  for (int j = 0; j < malla.n_y; j++) {
    for (int k = 0; k < malla.n_z; k++) {
      rebote_particula_limite_x(malla.bloques[malla.get_pos(0, j, k)].particulas, 0);
      rebote_particula_limite_x(malla.bloques[malla.get_pos(malla.n_x - 1, j, k)].particulas, -1);
    }
    for (int i = 0; i < malla.n_x; i++) {
      rebote_particula_limite_z(malla.bloques[malla.get_pos(i, j, 0)].particulas, 0);
      rebote_particula_limite_z(malla.bloques[malla.get_pos(i, j, malla.n_z - 1)].particulas, -1);
    }
  }
  for (int i = 0; i < malla.n_x; i++) {
    for (int k = 0; k < malla.n_z; k++) {
      rebote_particula_limite_y(malla.bloques[malla.get_pos(i, 0, k)].particulas, 0);
      rebote_particula_limite_y(malla.bloques[malla.get_pos(i, malla.n_y - 1, k)].particulas, -1);
    }
  }
}

/*
for (int i = 0; i < num_particulas; ++i) {
  if (i == 26) { std::cout << "Tiempo\n"; }
  int const c_x = calculadora.indice_bloque(particulas.posicion[i]).x;
  if (c_x <= 0) {
    rebote_particula_limite_x(i, 0);
  } else if (c_x >= malla.n_x - 1) {
    rebote_particula_limite_x(i, -1);
  }
  int const c_y = calculadora.indice_bloque(particulas.posicion[i]).y;
  if (c_y <= 0) {
    rebote_particula_limite_y(i, 0);
  } else if (c_y >= malla.n_x - 1) {
    rebote_particula_limite_y(i, -1);
  }
  int const c_z = calculadora.indice_bloque(particulas.posicion[i]).z;
  if (c_z <= 0) {
    rebote_particula_limite_z(i, 0);
  } else if (c_z >= malla.n_x - 1) {
    rebote_particula_limite_z(i, -1);
  }
}
}
*/
void Simulacion::rebote_particula_limite_x(std::vector<int> & part, int bloque) {
  if (bloque == 0) {
    for (auto indice : part) {
      double const d_x = particulas.pos[indice].x - b_min.x;
      if (d_x < 0.0) {
        particulas.pos[indice].x       = Calculadora::interacciones_limite_eje_x(d_x, bloque);
        particulas.velocidad[indice].x = -particulas.velocidad[indice].x;
        particulas.gradiente[indice].x = -particulas.gradiente[indice].x;
      }
    }
  } else if (bloque == -1) {
    for (auto indice : part) {
      double const d_x = b_max.x - particulas.pos[indice].x;
      if (d_x < 0.0) {
        particulas.pos[indice].x       = Calculadora::interacciones_limite_eje_x(d_x, bloque);
        particulas.velocidad[indice].x = -particulas.velocidad[indice].x;
        particulas.gradiente[indice].x = -particulas.gradiente[indice].x;
      }
    }
  }
}

void Simulacion::rebote_particula_limite_y(std::vector<int> & part, int bloque) {
  if (bloque == 0) {
    for (auto indice : part) {
      double const d_y = particulas.pos[indice].y - b_min.y;
      if (d_y < 0.0) {
        particulas.pos[indice].y       = Calculadora::interacciones_limite_eje_y(d_y, bloque);
        particulas.velocidad[indice].y = -particulas.velocidad[indice].y;
        particulas.gradiente[indice].y = -particulas.gradiente[indice].y;
      }
    }
  } else if (bloque == -1) {
    for (auto indice : part) {
      double const d_y = b_max.y - particulas.pos[indice].y;
      if (d_y < 0.0) {
        particulas.pos[indice].y       = Calculadora::interacciones_limite_eje_y(d_y, bloque);
        particulas.velocidad[indice].y = -particulas.velocidad[indice].y;
        particulas.gradiente[indice].y = -particulas.gradiente[indice].y;
      }
    }
  }
}

void Simulacion::rebote_particula_limite_z(std::vector<int> & part, int bloque) {
  if (bloque == 0) {
    for (auto indice : part) {
      double const d_z = particulas.pos[indice].z - b_min.z;
      if (d_z < 0.0) {
        particulas.pos[indice].z       = Calculadora::interacciones_limite_eje_z(d_z, bloque);
        particulas.velocidad[indice].z = -particulas.velocidad[indice].z;
        particulas.gradiente[indice].z = -particulas.gradiente[indice].z;
      }
    }
  } else if (bloque == -1) {
    for (auto indice : part) {
      double const d_z = b_max.z - particulas.pos[indice].z;
      if (d_z < 0.0) {
        particulas.pos[indice].z       = Calculadora::interacciones_limite_eje_z(d_z, bloque);
        particulas.velocidad[indice].z = -particulas.velocidad[indice].z;
        particulas.gradiente[indice].z = -particulas.gradiente[indice].z;
      }
    }
  }
}

void Simulacion::print_simulation_parameters() const {
  Vector3d<double> const tamanio_bloque = calc.tamanio_bloque();
  std::cout << "Number of particles: " << num_particulas
            << "\n"
            //<< "Particles per meter: " << ppm << "\n"
            << "Smoothing length: " << calc.suavizado << "\n"
            << "Particle mass: " << calc.masa << "\n"
            << "Grid size: " << malla.n_x << " x " << malla.n_y << " x " << malla.n_z << "\n"
            << "Number of blocks: " << malla.tamano << "\n"
            << "Block size: " << tamanio_bloque.x << " x " << tamanio_bloque.y << " x "
            << tamanio_bloque.z << "\n";
}


void Simulacion::add_particulas(int index, Vector3d<float> & pos, Vector3d<float> & hv,
                                Vector3d<float> & v) {
  particulas.pos[index] = pos.to_double();
  particulas.gradiente[index] = hv.to_double();
  particulas.velocidad[index] = v.to_double();
  particulas.aceleracion[index] = Vector3d<float>(0.0, 0.0, 0.0).to_double();
}

