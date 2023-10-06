//
// Created by cesar on 29/09/23.
//

#ifndef AC_LAB1_PARTICLE_H
#define AC_LAB1_PARTICLE_H

#include "vector_3d.hpp"
#include <vector>
#include <cmath>

struct Particulas {
    std::vector<Vector3d> posicion;   // posicion
    std::vector<Vector3d> suavizado;   // suavizado
    std::vector<Vector3d> velocidad;   // velocidad
    std::vector<Vector3d> aceleracion;   // aceleracion
    std::vector<double> densidad;   // densidad

};

#endif  // AC_LAB1_PARTICLE_H
