#ifndef AC_LAB1_BLOQUES_H
#define AC_LAB1_BLOQUES_H

#include <vector>

class Bloque {
  public:
    std::vector<int> particulas;
    std::vector<int> bloques_contiguos;
    int posicion_bloque;
};

#endif