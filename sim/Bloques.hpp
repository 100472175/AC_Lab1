#ifndef AC_LAB1_BLOQUES_H
#define AC_LAB1_BLOQUES_H

#include <vector>

using namespace std;

class Bloque {
  public:
    vector<int> bloque;
    vector<Bloque> bloques_contiguos;
};

#endif