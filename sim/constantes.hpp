//
// Created by Eduardo Alarcon on 3/10/23.
//

#ifndef FLUID_CONSTANTES_HPP
#define FLUID_CONSTANTES_HPP
#include "vector_3d.hpp"

constexpr double radio{1.695};                   // radio
constexpr double dens_fluido{1e3};               // densidad de fluido
constexpr double p_s{3.0};                       // presion regidez
constexpr double s_c{3e4};                       // colision rigidez
constexpr double d_v{128.0};                     // amortiguamiento
constexpr double viscosidad{0.4};                // viscosidad
constexpr double d_p{2e-4};                      // tamaño particula
constexpr double delta_t{1e-3};                  // paso de tiempo
constexpr Vector3d gravedad{0.0, 9.8, 0.0};      // vector de aceleraciones iniciales
constexpr Vector3d b_min{0.065, 0.1, 0.065};     // vector con la posición del punto b_min
constexpr Vector3d b_max{-0.065, -0.08, -0.065}; // vector con la posición dle punto b_max

#endif  // FLUID_CONSTANTES_HPP
