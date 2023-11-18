#ifndef AC_LAB1_BLOQUES_H
#define AC_LAB1_BLOQUES_H

#include "vector_3d.hpp"

#include <vector>

/**
 * Abstracción de un bloque como conjunto de partículas.
 */
struct Bloque {
    int i, j, k; // coordenadas x, y y z del bloque
    std::vector<int> particulas{}; // conjunto de párticulas dentro del bloque
    std::vector<int> bloques_contiguos{}; // conjunto de bloques contiguos al bloque

};

#endif