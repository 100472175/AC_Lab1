//
// Created by Eduardo Alarcon on 2/10/23.
//
#include <cmath>
#include "vector_3d.hpp"


radio       = 1.695;
dens_fluido = pow(10, 3);
p_s         = 3.0;              // presion regidez
s_c         = 3 * pow(10, 4);   // colision rigidez
d_v         = 128.0;            // amortiguamiento
muu         = 0.4;              // viscosidad
d_p         = 2 * pow(10, -4);  // tamaño particula
delta_t     = pow(10, -3);      // paso de tiempo
gravedad  = {0.0, 9.8, 0.0};  // vector de aceleraciones iniciales
b_min     = {0.065, 0.1, 0.065};
b_max     = {-0.065, -0.08, -0.065};