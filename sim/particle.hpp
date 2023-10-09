//
// Created by cesar on 29/09/23.
//

#ifndef AC_LAB1_PARTICLE_H
#define AC_LAB1_PARTICLE_H

#include "vector_3d.hpp"

#include <cmath>
#include <vector>

struct Particulas {
    std::vector<Vector3d<double>> posicion{};     // posicion
    std::vector<Vector3d<double>> gradiente{};    // gradiente
    std::vector<Vector3d<double>> velocidad{};    // velocidad
    std::vector<Vector3d<double>> aceleracion{};  // aceleracion
    std::vector<double> densidad{};               // densidad
};

#endif  // AC_LAB1_PARTICLE_H
