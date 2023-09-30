//
// Created by cesar on 29/09/23.
//

#include "particle.hpp"
#include <cmath>


double Particle::operator||(Particle const& p) {
    double distancia = pow((this->p.x - p.p.x), 2) + pow((this->p.y - p.p.y), 2) + pow((this->p.z - p.p.z), 2);
    distancia = sqrt(distancia);
    return pow(distancia, 2);
}

