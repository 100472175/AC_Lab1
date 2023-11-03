//
// Created by Eduardo Alarcon on 27/9/23.
//
#include "calculadora.hpp"

// Sección 3.5 - La malla de simulación
// Se puede iniciar la calculadora cuando tengamos ppm y num_particulas
void Calculadora::inicializar_calculadora() {
  suavizado = radio / ppm;
  masa      = dens_fluido / pow(ppm, 3);
}

Vector3d<int> Calculadora::indice_bloque(Vector3d<double> const & posicion) const {
  int const coord_x = floor((posicion.x - b_min.x) / tamanio_bloque().x);
  int const coord_y = floor((posicion.y - b_min.y) / tamanio_bloque().y);
  int const coord_z = floor((posicion.z - b_min.z) / tamanio_bloque().z);
  return Vector3d<int>{coord_x, coord_y, coord_z};
}
