//
// Created by cesar on 29/09/23.
//

#include "particle.hpp"


double Particle::operator||(Particle const& other) const {
    double distancia = pow((this->p.x - other.p.x), 2) + pow((this->p.y - other.p.y), 2) + pow((this->p.z - other.p.z), 2);
    distancia = sqrt(distancia);
    return pow(distancia, 2);
}



