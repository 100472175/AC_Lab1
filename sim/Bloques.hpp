#ifndef AC_LAB1_BLOQUES_H
#define AC_LAB1_BLOQUES_H

#include "vector_3d.hpp"

#include <vector>

class Bloque {
  public:
    int i, j, k;
    std::vector<int> particulas{};
    std::vector<int> bloques_contiguos{};
    int posicion_bloque;

    Bloque(int i, int j, int k, int pos) : i(i), j(j), k(k), posicion_bloque(pos) {};
};

#endif