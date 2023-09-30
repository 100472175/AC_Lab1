#ifndef AC_LAB1_MALLA_H
#define AC_LAB1_MALLA_H

#include <vector>
#include "iostream"
#include "funciones_fisicas.hpp"
#include "Bloques.hpp"
#include "particle.hpp"
using namespace std;

extern const Vector3d b_max;
extern const Vector3d b_min;
extern double h;
extern int np;

class Malla {
  private:
    vector<Bloque> bloques;
    int n_x;
    int n_y;
    int n_z;

  public:
    Malla() {
      n_x     = (int) func_fis::num_bloques(b_max.x, b_min.x);
      n_y     = (int) func_fis::num_bloques(b_max.y, b_min.y);
      n_z     = (int) func_fis::num_bloques(b_max.z, b_min.z);
      bloques = vector<Bloque> (n_x  * n_y * n_z );
    }

    int get_pos(int i, int j, int k) const;
    void poblar_malla(vector<Particle> const&);
};

#endif


