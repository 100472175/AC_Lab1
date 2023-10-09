#ifndef AC_LAB1_BLOQUES_H
#define AC_LAB1_BLOQUES_H

#include <vector>

class Bloque {
  public:
    std::vector<int> bloque;
    std::vector<Bloque> bloques_contiguos;
};

#endif