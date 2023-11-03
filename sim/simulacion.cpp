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
    Vector3d<int> bloque_coords = calculadora.indice_bloque(particulas.posicion[cont]);
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
    Vector3d<int> bloque_coords = calculadora.indice_bloque(particulas.posicion[cont]);
    bloque_coords               = malla.fuera_de_rango(bloque_coords);
    int const ind_real          = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    malla.bloques[ind_real].particulas.push_back(cont);
  }
}

// Sección 4.3.2 - Página 8 - Cálculo de las aceleraciones
void Simulacion::colisiones_particulas() {
  // En cada iteración se reinician los valores de densidad y aceleración para todas las particulas
  for (int i = 0; i < num_particulas; ++i) {
    particulas.densidad[i]    = 0.0;
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
    std::vector<int> const contiguos = malla.bloques[indice_bloque].bloques_contiguos;
    for (auto const & ind_part : malla.bloques[indice_bloque].particulas) {
      for (auto const & contiguo : contiguos) {  // bucle que reccore los bloques contiguos
        for (int const & i_p_nueva :
             malla.bloques[contiguo].particulas) {  // en cada bucle se buscan todas las particulas
          if (i_p_nueva > ind_part) {
            double const distancia_cuadrado = Vector3d<double>::sq_distancia(
                particulas.posicion[ind_part], particulas.posicion[i_p_nueva]);
            if (distancia_cuadrado < (calculadora.suavizado * calculadora.suavizado)) {
              // comprobar que realmente interactuan
              double const cambio_densidad    = calculadora.delta_densidades(distancia_cuadrado);
              particulas.densidad[ind_part]  += cambio_densidad;
              particulas.densidad[i_p_nueva] += cambio_densidad;  // actualizar ambas densidades
            }
          }
        }
      }
    }
  }
  for (int contador = 0; contador < num_particulas; contador++) {
    particulas.densidad[contador] = calculadora.transform_densidad(particulas.densidad[contador]);
  }
}

/*void Simulacion::colisiones_particulas_densidad() {
  for(int i = 0; i < num_particulas; ++i){  //bucle que recorre todas las particulas
    //estas 3 lineas son para tener la lista de bloques contiguos
    Vector3d<int> const mi_bloque = calculadora.indice_bloque(particulas.posicion[i]);
    //std::cout << mi_bloque.x << mi_bloque.y << mi_bloque.z;
    int const indice = malla.get_pos(mi_bloque.x, mi_bloque.y, mi_bloque.z);
    std::vector<Bloque> const contiguos = malla.bloques[indice].bloques_contiguos;
    for(const auto & contiguo : contiguos) { //bucle que reccore los bloques contiguos
      for(int  const& i_p_nueva : contiguo.particulas) {//en cada bucle se buscan todas las
particulas if (i_p_nueva > i){ //para que solo se ejecute cada par 1 vez double const
distancia_cuadrado = Calculadora::cuadrado_distancias( particulas.posicion[i],
particulas.posicion[i_p_nueva]); if (distancia_cuadrado < (calculadora.suavizado *
calculadora.suavizado)) {//comprobar que realmente interactuan double const cambio_densidad =
calculadora.delta_densidades(distancia_cuadrado); particulas.densidad[i],
particulas.densidad[i_p_nueva] += cambio_densidad;//actualizar ambas densidades
          }
        }
      }
    }
    particulas.densidad[i] = calculadora.transform_densidad(particulas.densidad[i]);//transformación
final para cada particula
  }
}*/

void Simulacion::colisiones_particulas_aceleracion() {
  for (int indice_bloque = 0; indice_bloque < malla.tamano; ++indice_bloque) {
    std::vector<int> const contiguos = malla.bloques[indice_bloque].bloques_contiguos;
    for (auto const & ind_part : malla.bloques[indice_bloque].particulas) {
      for (auto const & contiguo : contiguos) {
        for (int const & i_p_nueva : malla.bloques[contiguo].particulas) {
          if (i_p_nueva > ind_part) {
            double const distancia_cuadrado = Vector3d<double>::sq_distancia(
                particulas.posicion[ind_part], particulas.posicion[i_p_nueva]);
            double const suavizado_cuadrado = (calculadora.suavizado * calculadora.suavizado);
            if (distancia_cuadrado < suavizado_cuadrado) {
              Vector3d<double> operador_1 = calculadora.aceleracion_primera_parte(
                  particulas.posicion[ind_part], particulas.posicion[i_p_nueva],
                  particulas.densidad[ind_part], particulas.densidad[i_p_nueva]);
              Vector3d<double> const operador_2 = calculadora.aceleracion_segunda_parte(
                  particulas.velocidad[ind_part], particulas.velocidad[i_p_nueva]);
              Vector3d<double> const cambio_aceleracion = Calculadora::transferencia_aceleracion(
                  operador_1, operador_2,
                  particulas.densidad[ind_part] * particulas.densidad[i_p_nueva]);
              particulas.aceleracion[ind_part] += cambio_aceleracion;
              particulas.aceleracion[i_p_nueva] -= cambio_aceleracion;
            }
          }
        }
      }
    }
  }
}

/*void Simulacion::colisiones_particulas_aceleracion() {
for(int i = 0; i < num_particulas; ++i){
  Vector3d<int> const mi_bloque = calculadora.indice_bloque(particulas.posicion[i]);
  int const indice = malla.get_pos(mi_bloque.x, mi_bloque.y, mi_bloque.z);
  std::vector<Bloque> const contiguos = malla.bloques[indice].bloques_contiguos;
  for(const auto & contiguo : contiguos) {
    for(int  const& i_p_nueva : contiguo.particulas){
      if (i_p_nueva > i) {
        double const distancia_cuadrado = Calculadora::cuadrado_distancias(particulas.posicion[i],
particulas.posicion[i_p_nueva]); if (distancia_cuadrado < (calculadora.suavizado *
calculadora.suavizado)) { Vector3d<double> operador_1 = calculadora.aceleracion_primera_parte(
            particulas.posicion[i], particulas.posicion[i_p_nueva],
            particulas.densidad[i], particulas.densidad[i_p_nueva]);
          Vector3d<double> operador_2 = calculadora.aceleracion_segunda_parte(
            particulas.velocidad[i], particulas.velocidad[i_p_nueva]);
          Vector3d<double> const cambio_aceleracion = calculadora.transferencia_aceleracion(
            operador_1, operador_2,particulas.densidad[i] * particulas.densidad[i_p_nueva]);
          particulas.aceleracion[i] += cambio_aceleracion; //actualizaciones de aceleración
          particulas.aceleracion[i_p_nueva] -= cambio_aceleracion;
        }
      }
    }
  }
}
}*/

// Sección 4.3.3 - Página 9 - Colisiones de partículas (con límites)
// Eduardo Alarcón
void Simulacion::colision_particula_limite() {
  for (int i = 0; i < num_particulas; ++i) {
    int const c_x = calculadora.indice_bloque(particulas.posicion[i]).x;
    if (c_x <= 0) {
      colision_particula_limite_x(i, 0);
    } else if (c_x >= malla.n_x - 1) {
      colision_particula_limite_x(i, -1);
    }
    int const c_y = calculadora.indice_bloque(particulas.posicion[i]).y;
    if (c_y <= 0) {
      colision_particula_limite_y(i, 0);
    } else if (c_y >= malla.n_y - 1) {
      colision_particula_limite_y(i, -1);
    }
    int const c_z = calculadora.indice_bloque(particulas.posicion[i]).z;
    if (c_z <= 0) {
      colision_particula_limite_z(i, 0);
    } else if (c_z >= malla.n_z - 1) {
      colision_particula_limite_z(i, -1);
    }
  }
}

void Simulacion::colision_particula_limite_x(int indice, int bloque) {
  double const nueva_x = particulas.posicion[indice].x + particulas.gradiente[indice].x * delta_t;
  if (bloque == 0) {
    double const delta_x = d_p - (nueva_x - b_min.x);
    if (delta_x > 1e-10) {
      particulas.aceleracion[indice].x +=
          Calculadora::colisiones_limite_eje_x(bloque, delta_x, particulas.velocidad[indice]);
    }
  } else if (bloque == -1) {
    double const delta_x = d_p - (b_max.x - nueva_x);
    if (delta_x > 1e-10) {
      particulas.aceleracion[indice].x +=
          Calculadora::colisiones_limite_eje_x(bloque, delta_x, particulas.velocidad[indice]);
    }
  }
}

void Simulacion::colision_particula_limite_y(int indice, int bloque) {
  double const nueva_y = particulas.posicion[indice].y + particulas.gradiente[indice].y * delta_t;
  if (bloque == 0) {
    double const delta_y = d_p - (nueva_y - b_min.y);
    if (delta_y > 1e-10) {
      particulas.aceleracion[indice].y +=
          Calculadora::colisiones_limite_eje_y(bloque, delta_y, particulas.velocidad[indice]);
    }
  } else if (bloque == -1) {
    double const delta_y = d_p - (b_max.y - nueva_y);
    if (delta_y > 1e-10) {
      particulas.aceleracion[indice].y +=
          Calculadora::colisiones_limite_eje_y(bloque, delta_y, particulas.velocidad[indice]);
    }
  }
}

void Simulacion::colision_particula_limite_z(int indice, int bloque) {
  double const nueva_z = particulas.posicion[indice].z + particulas.gradiente[indice].z * delta_t;
  if (bloque == 0) {
    double const delta_z = d_p - (nueva_z - b_min.z);
    if (delta_z > 1e-10) {
      particulas.aceleracion[indice].z +=
          Calculadora::colisiones_limite_eje_z(bloque, delta_z, particulas.velocidad[indice]);
    }
  } else if (bloque == -1) {
    double const delta_z = d_p - (b_max.z - nueva_z);
    if (delta_z > 1e-10) {
      particulas.aceleracion[indice].z +=
          Calculadora::colisiones_limite_eje_z(bloque, delta_z, particulas.velocidad[indice]);
    }
  }
}

// Sección 4.3.4 - Página 10 - Movimiento de las partículas
void Simulacion::movimiento_particulas() {
  for (int i = 0; i < num_particulas; ++i) {
    particulas.posicion[i] = Calculadora::actualizar_posicion(
        particulas.posicion[i], particulas.gradiente[i], particulas.aceleracion[i]);
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
      double const d_x = particulas.posicion[indice].x - b_min.x;
      if (d_x < 0.0) {
        particulas.posicion[indice].x  = Calculadora::interacciones_limite_eje_x(d_x, bloque);
        particulas.velocidad[indice].x = -particulas.velocidad[indice].x;
        particulas.gradiente[indice].x = -particulas.gradiente[indice].x;
      }
    }
  } else if (bloque == -1) {
    for (auto indice : part) {
      double const d_x = b_max.x - particulas.posicion[indice].x;
      if (d_x < 0.0) {
        particulas.posicion[indice].x  = Calculadora::interacciones_limite_eje_x(d_x, bloque);
        particulas.velocidad[indice].x = -particulas.velocidad[indice].x;
        particulas.gradiente[indice].x = -particulas.gradiente[indice].x;
      }
    }
  }
}

void Simulacion::rebote_particula_limite_y(std::vector<int> & part, int bloque) {
  if (bloque == 0) {
    for (auto indice : part) {
      double const d_y = particulas.posicion[indice].y - b_min.y;
      if (d_y < 0.0) {
        particulas.posicion[indice].y  = Calculadora::interacciones_limite_eje_y(d_y, bloque);
        particulas.velocidad[indice].y = -particulas.velocidad[indice].y;
        particulas.gradiente[indice].y = -particulas.gradiente[indice].y;
      }
    }
  } else if (bloque == -1) {
    for (auto indice : part) {
      double const d_y = b_max.y - particulas.posicion[indice].y;
      if (d_y < 0.0) {
        particulas.posicion[indice].y  = Calculadora::interacciones_limite_eje_y(d_y, bloque);
        particulas.velocidad[indice].y = -particulas.velocidad[indice].y;
        particulas.gradiente[indice].y = -particulas.gradiente[indice].y;
      }
    }
  }
}

void Simulacion::rebote_particula_limite_z(std::vector<int> & part, int bloque) {
  if (bloque == 0) {
    for (auto indice : part) {
      double const d_z = particulas.posicion[indice].z - b_min.z;
      if (d_z < 0.0) {
        particulas.posicion[indice].z  = Calculadora::interacciones_limite_eje_z(d_z, bloque);
        particulas.velocidad[indice].z = -particulas.velocidad[indice].z;
        particulas.gradiente[indice].z = -particulas.gradiente[indice].z;
      }
    }
  } else if (bloque == -1) {
    for (auto indice : part) {
      double const d_z = b_max.z - particulas.posicion[indice].z;
      if (d_z < 0.0) {
        particulas.posicion[indice].z  = Calculadora::interacciones_limite_eje_z(d_z, bloque);
        particulas.velocidad[indice].z = -particulas.velocidad[indice].z;
        particulas.gradiente[indice].z = -particulas.gradiente[indice].z;
      }
    }
  }
}

void Simulacion::print_simulation_parameters() const {
  Vector3d<double> const tamanio_bloque = calculadora.tamanio_bloque();
  std::cout << "Number of particles: " << num_particulas << "\n"
            //<< "Particles per meter: " << ppm << "\n"
            << "Smoothing length: " << calculadora.suavizado << "\n"
            << "Particle mass: " << calculadora.masa << "\n"
            << "Grid size: " << malla.n_x << " x " << malla.n_y << " x " << malla.n_z << "\n"
            << "Number of blocks: " << malla.tamano << "\n"
            << "Block size: " << tamanio_bloque.x << " x " << tamanio_bloque.y << " x "
            << tamanio_bloque.z << "\n";
}
