//
// Created by Eduardo Alarcon on 2/10/23.
//

#ifndef FLUID_CONSTANTES_HPP
#define FLUID_CONSTANTES_HPP

#include "funciones_fisicas.hpp"
#include "vector_3d.hpp"

double const radio       = 1.695;
double const dens_fluido = pow(10, 3);
double const p_s         = 3.0;              // presion regidez
double const s_c         = 3 * pow(10, 4);   // colision rigidez
double const d_v         = 128.0;            // amortiguamiento
double const muu         = 0.4;              // viscosidad
double const d_p         = 2 * pow(10, -4);  // tamaño particula
double const delta_t     = pow(10, -3);      // paso de tiempo
Vector3d const gravedad  = {0.0, 9.8, 0.0};  // vector de aceleraciones iniciales
Vector3d const b_min     = {0.065, 0.1, 0.065};
Vector3d const b_max     = {-0.065, -0.08, -0.065};




#endif  // FLUID_CONSTANTES_HPP
