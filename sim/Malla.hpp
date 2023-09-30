#ifndef AC_LAB1_MALLA_H
#define AC_LAB1_MALLA_H

#include <vector>
#include "funciones_fisicas.hpp"
#include "Bloques.hpp"
#include "../fluid/fluid.cpp"
#include "particle.hpp"
using namespace std;

class Malla {
  private:
    vector<Bloque> bloques;
    int n_x;
    int n_y;
    int n_z;

  public:
    Malla() {
      n_x     = (int) func_fis::num_bloques(b_max[0], b_min[0], h);
      n_y     = (int) func_fis::num_bloques(b_max[1], b_min[1], h);
      n_z     = (int) func_fis::num_bloques(b_max[2], b_min[2], h);
      bloques = vector<Bloque>(n_x * n_y * n_z);
    }

    int get_pos(int i, int j, int k) const;
    void poblar_malla(vector<Particle> const&);
};

#endif


