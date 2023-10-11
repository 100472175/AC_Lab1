//
// Created by adrian on 10/6/23.
//
#include "simulacion.hpp"

/*Simulacion::Simulacion() : num_iteraciones(0), num_particulas(0), ppm(0.0) {
                                             Calculadora inst_calculadora(ppm);
                                             calculadora = inst_calculadora;
                                             Malla inst_malla(calculadora.indice_bloques(),
   calculadora.indice_bloques(), calculadora.indice_bloques()) malla = inst_malla;
                                           };*/

void Simulacion::iterador() {
  malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) { malla.bloques_contiguos(malla.bloques[i]); }
  poblar_malla();
  for (int i = 0; i < num_iteraciones; i++) { iteracion(); }
}

void Simulacion::iteracion() {
  for (int i = 0; i < num_particulas; i++) { reposicionamiento(); }
  for (int i = 0; i < num_particulas; i++) { colisiones_particulas(); }
  for (int i = 0; i < num_particulas; i++) { colision_particula_limite(); }
  for (int i = 0; i < num_particulas; i++) { movimiento_particulas(); }
  for (int i = 0; i < num_particulas; i++) { rebote_particula_limite(); }
}

void Simulacion::poblar_malla() {
  for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d<int> bloque_coords = calculadora.indice_bloque(particulas.posicion[cont]);
    bloque_coords               = malla.fuera_de_rango(bloque_coords);
    int const ind_real          = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    malla.bloques[ind_real].bloque.push_back(cont);
  }
}

void Simulacion::reposicionamiento() {
  for (int i = 0; i < malla.tamano; i++) {
    // Limpio las partículas de cada bloue
    malla.bloques[i].bloque.clear();
  }
  // Y la vuelvo a repoblar
  for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d<int> const bloque_coords = calculadora.indice_bloque(particulas.posicion[cont]);
    int const ind_real = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    malla.bloques[ind_real].bloque.push_back(cont);
  }
}

void Simulacion::colisiones_particulas() {
  //En cada iteración se reinician los valores de densidad y aceleración para todas las particulas
  for(int i = 0; i < num_particulas; ++i) {
    particulas.densidad[i] = 0.0;
    particulas.aceleracion[i] = gravedad;
  }
  //Función encargada de actualizar las densidades de cada particula
  Simulacion::colisiones_particulas_densidad();
  //función para actualizar la aceleración de todas las particulas, cuyas densidades tienen que estar actualizadas
  Simulacion::colisiones_particulas_aceleracion();
}

void Simulacion::colisiones_particulas_densidad() {
  for (int indice_bloque = 0; indice_bloque < malla.tamano; ++indice_bloque) {
    std::vector<Bloque> const contiguos = malla.bloques[indice_bloque].bloques_contiguos;
    std::vector<int> const particulas_bloque = malla.bloques[indice_bloque].bloque;
    for (const auto & ind_part: particulas_bloque) {
      for (const auto & contiguo : contiguos) {  // bucle que reccore los bloques contiguos
        for (int const & i_p_nueva :
             contiguo.bloque) {                // en cada bucle se buscan todas las particulas
          if (i_p_nueva > ind_part) {  // para que solo se ejecute cada par 1 vez
            double const distancia_cuadrado = Calculadora::cuadrado_distancias(
                particulas.posicion[ind_part], particulas.posicion[i_p_nueva]);
            if (distancia_cuadrado <
                (calculadora.suavizado *
                 calculadora.suavizado)) {  // comprobar que realmente interactuan
              double const cambio_densidad = calculadora.delta_densidades(distancia_cuadrado);
              particulas.densidad[ind_part] += cambio_densidad;
              particulas.densidad[i_p_nueva] += cambio_densidad;  // actualizar ambas densidades
            }
          }
        }
      }
      particulas.densidad[ind_part] =
          calculadora.transform_densidad(particulas.densidad[ind_part]);
    }
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
      for(int  const& i_p_nueva : contiguo.bloque) {//en cada bucle se buscan todas las particulas
        if (i_p_nueva > i){ //para que solo se ejecute cada par 1 vez
          double const distancia_cuadrado = Calculadora::cuadrado_distancias(
              particulas.posicion[i], particulas.posicion[i_p_nueva]);
          if (distancia_cuadrado < (calculadora.suavizado * calculadora.suavizado)) {//comprobar que realmente interactuan
            double const cambio_densidad = calculadora.delta_densidades(distancia_cuadrado);
            particulas.densidad[i], particulas.densidad[i_p_nueva] += cambio_densidad;//actualizar ambas densidades
          }
        } 
      }
    }
    particulas.densidad[i] = calculadora.transform_densidad(particulas.densidad[i]);//transformación final para cada particula
  }
}*/

void Simulacion::colisiones_particulas_aceleracion() {
  for (int indice_bloque = 0; indice_bloque < malla.tamano; ++indice_bloque) {
    std::vector<Bloque> const contiguos = malla.bloques[indice_bloque].bloques_contiguos;
    std::vector<int> const particulas_bloque = malla.bloques[indice_bloque].bloque;
    for (const auto & ind_part: particulas_bloque) {
      for (const auto & contiguo : contiguos) {
        for (int const & i_p_nueva : contiguo.bloque) {
          if (i_p_nueva > ind_part) {
            double const distancia_cuadrado = Calculadora::cuadrado_distancias(
                particulas.posicion[ind_part], particulas.posicion[i_p_nueva]);
            if (distancia_cuadrado < (calculadora.suavizado * calculadora.suavizado)) {
              Vector3d<double> operador_1 = calculadora.aceleracion_primera_parte(
                  particulas.posicion[ind_part], particulas.posicion[i_p_nueva], particulas.densidad[ind_part],
                  particulas.densidad[i_p_nueva]);
              Vector3d<double> operador_2 = calculadora.aceleracion_segunda_parte(
                  particulas.velocidad[ind_part], particulas.velocidad[i_p_nueva]);
              Vector3d<double> const cambio_aceleracion = calculadora.transferencia_aceleracion(
                  operador_1, operador_2, particulas.densidad[ind_part] * particulas.densidad[i_p_nueva]);
              particulas.aceleracion[ind_part] += cambio_aceleracion;  // actualizaciones de aceleración
              particulas.aceleracion[i_p_nueva] -= cambio_aceleracion; }
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
      for(int  const& i_p_nueva : contiguo.bloque){
        if (i_p_nueva > i) {
          double const distancia_cuadrado = Calculadora::cuadrado_distancias(particulas.posicion[i], particulas.posicion[i_p_nueva]);
          if (distancia_cuadrado < (calculadora.suavizado * calculadora.suavizado)) {
            Vector3d<double> operador_1 = calculadora.aceleracion_primera_parte(
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


void Simulacion::colision_particula_limite() {
  for (int i = 0; i < num_particulas; ++i) {
    // Podría ahorrarme una función, pero sería menos legible.
    colision_particula_limite_x(i);
    colision_particula_limite_y(i);
    colision_particula_limite_z(i);
  }
  std::cout << "XDD";
}

void Simulacion::colision_particula_limite_x(int indice) {
  int const c_x = calculadora.indice_bloque(particulas.posicion[indice]).x;
  if (c_x == 0) {
    double const nueva_x = particulas.posicion[indice].x + particulas.gradiente[indice].x * delta_t;
    double const delta_x = d_p - (nueva_x - b_min.x);
    if (delta_x > 10e-10) {
      particulas.aceleracion[indice].x =
          calculadora.colisiones_limite_eje_x(c_x, delta_x, particulas.velocidad[indice]);
    }
  } else if (c_x == malla.n_x - 1) {
    double const nueva_x = particulas.posicion[indice].x + particulas.gradiente[indice].x * delta_t;
    double const delta_x = d_p - (b_max.x - nueva_x);
    if (delta_x > 10e-10) {
      particulas.aceleracion[indice].x =
          calculadora.colisiones_limite_eje_x(c_x, delta_x, particulas.velocidad[indice]);
    }
  }
}

void Simulacion::colision_particula_limite_y(int indice) {
  int const c_y = calculadora.indice_bloque(particulas.posicion[indice]).y;
  if (c_y == 0) {
    double const nueva_y = particulas.posicion[indice].y + particulas.gradiente[indice].y * delta_t;
    double const delta_y = d_p - (nueva_y - b_min.y);
    if (delta_y > 10e-10) {
      particulas.aceleracion[indice].y =
          calculadora.colisiones_limite_eje_y(c_y, delta_y, particulas.velocidad[indice]);
    }
  } else if (c_y == malla.n_y - 1) {
    double const nueva_y = particulas.posicion[indice].y + particulas.gradiente[indice].y * delta_t;
    double const delta_y = d_p - (b_max.y - nueva_y);
    if (delta_y > 10e-10) {
      particulas.aceleracion[indice].y =
          calculadora.colisiones_limite_eje_y(c_y, delta_y, particulas.velocidad[indice]);
    }
  }
}

void Simulacion::colision_particula_limite_z(int indice) {
  int const c_z = calculadora.indice_bloque(particulas.posicion[indice]).z;
  if (c_z == 0) {
    double const nueva_z = particulas.posicion[indice].z + particulas.gradiente[indice].z * delta_t;
    double const delta_z = d_p - (nueva_z - b_min.z);
    if (delta_z > 10e-10) {
      particulas.aceleracion[indice].z =
          calculadora.colisiones_limite_eje_z(c_z, delta_z, particulas.velocidad[indice]);
    }
  } else if (c_z == malla.n_z - 1) {
    double const nueva_z = particulas.posicion[indice].z + particulas.gradiente[indice].z * delta_t;
    double const delta_z = d_p - (b_max.z - nueva_z);
    if (delta_z > 10e-10) {
      particulas.aceleracion[indice].z =
          calculadora.colisiones_limite_eje_z(c_z, delta_z, particulas.velocidad[indice]);
    }
  }
}

void Simulacion::rebote_particula_limite() {
  std::cout << "XD";
}

void Simulacion::movimiento_particulas() {
  for (int i = 0; i < num_particulas; ++i) {
    particulas.posicion[i] = calculadora.actualizar_posicion(
        particulas.posicion[i], particulas.gradiente[i], particulas.aceleracion[i]);
    particulas.gradiente[i] =
        calculadora.actualizar_gradiente(particulas.gradiente[i], particulas.aceleracion[i]);
    particulas.velocidad[i] =
        calculadora.actualizar_velocidad(particulas.gradiente[i], particulas.aceleracion[i]);
  }
}

void Simulacion::print_simulation_parameters() {
  Vector3d<double> tamanio_bloque = calculadora.tamanio_bloque();
  std::cout << "Number of particles: " << num_particulas << "\n"
            << "Particles per meter: " << ppm << "\n"
            << "Smoothing length: " << calculadora.suavizado << "\n"
            << "Particle mass: " << calculadora.masa << "\n"
            << "Grid size: " << malla.n_x << " x " << malla.n_y << " x " << malla.n_z << "\n"
            << "Number of blocks: " << malla.tamano << "\n"
            << "Block size: " << tamanio_bloque.x << " x " << tamanio_bloque.y << " x "
            << tamanio_bloque.z << "\n";
}
