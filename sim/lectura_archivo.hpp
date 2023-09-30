//
// Created by cesar on 27/09/23.
//

#ifndef AC_LAB1_LECTURA_ARCHIVO_H
#define AC_LAB1_LECTURA_ARCHIVO_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "particle.hpp"
#include "vector_3d.hpp"

extern double ppm;
extern int np;

int read_file(const std::string &path, std::vector<Particle> &particles);

#endif // AC_LAB1_LECTURA_ARCHIVO_H
