#ifndef AC_LAB1_MALLA_H
#define AC_LAB1_MALLA_H

#include "Bloques.hpp"
#include "funciones_fisicas.hpp"
#include "iostream"
#include "particle.hpp"
#include "progargs.hpp"

#include <vector>

using namespace std;

extern Vector3d const b_max;
extern Vector3d const b_min;
extern double suavizado;
extern int num_particulas;

class Malla {
  private:
    vector<Bloque> bloques;
    int n_x;
    int n_y;
    int n_z;

  public:
    Malla() {
      n_x     = (int) func_fis::num_bloques_por_eje(b_max.x, b_min.x);
      n_y     = (int) func_fis::num_bloques_por_eje(b_max.y, b_min.y);
      n_z     = (int) func_fis::num_bloques_por_eje(b_max.z, b_min.z);
      bloques = vector<Bloque>(n_x * n_y * n_z);
    }

    int get_pos(int i, int j, int k) const;
    void poblar_malla(vector<Particle> const &);
};

#endif
