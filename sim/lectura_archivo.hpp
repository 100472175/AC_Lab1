//
// Created by cesar on 27/09/23.
//

#ifndef AC_LAB1_LECTURA_ARCHIVO_H
#define AC_LAB1_LECTURA_ARCHIVO_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

typedef struct particle {
    double px, py, pz;
    double hx, hy, hz;
    double vx, vy, vz;
    double density;
    int id;
} particle;

int read_file(const std::string &path, std::vector<particle> &particles);

#endif //AC_LAB1_LECTURA_ARCHIVO_H
