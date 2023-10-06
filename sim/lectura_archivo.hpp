//
// Created by cesar on 27/09/23.
//

#ifndef AC_LAB1_LECTURA_ARCHIVO_H
#define AC_LAB1_LECTURA_ARCHIVO_H

#include "particle.hpp"
#include "vector_3d.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

extern double ppm;
extern int num_particulas;

int read_file(std::string const & path, std::vector<Particle> & particles);

int write_file(const std::string &path, std::vector<Particle> &particles, int number_of_particles, float particles_per_meter);

#endif  // AC_LAB1_LECTURA_ARCHIVO_H
