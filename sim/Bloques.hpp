#ifndef AC_LAB1_BLOQUES_H
#define AC_LAB1_BLOQUES_H

#include "vector_3d.hpp"

#include <vector>

struct Bloque {
    int i, j, k;
    std::vector<int> particulas{};
    std::vector<int> bloques_contiguos{};

};

#endif