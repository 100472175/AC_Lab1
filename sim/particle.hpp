//
// Created by cesar on 29/09/23.
//

#ifndef AC_LAB1_PARTICLE_H
#define AC_LAB1_PARTICLE_H

#include "vector_3d.hpp"

#include <cmath>
#include <vector>

struct Particulas {
    std::vector<Vector3d<double>> pos{};     // posicion
    std::vector<Vector3d<double>> gradiente{};    // gradiente
    std::vector<Vector3d<double>> velocidad{};    // velocidad
    std::vector<Vector3d<double>> aceleracion{};  // aceleracion
    std::vector<double> dens{};               // densidad

    void reserve_space(int size){
        pos.reserve(size);
        gradiente.reserve(size);
        velocidad.reserve(size);
        aceleracion.reserve(size);
        dens.reserve(size);
    }
};

#endif  // AC_LAB1_PARTICLE_H
