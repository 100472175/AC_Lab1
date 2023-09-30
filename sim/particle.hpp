//
// Created by cesar on 29/09/23.
//

#ifndef AC_LAB1_PARTICLE_H
#define AC_LAB1_PARTICLE_H

#include "vector_3d.hpp"


struct Particle {
    Vector3d p; // posicion
    Vector3d hv; // h
    Vector3d v; // velocidad
    Vector3d a; // aceleracion
    double densidad;

    double operator || (Particle const& other) const;

};



#endif //AC_LAB1_PARTICLE_H
