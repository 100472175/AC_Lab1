#ifndef AC_LAB1_MALLA_H
#define AC_LAB1_MALLA_H

#include "Bloques.hpp"
#include "funciones_fisicas.hpp"
#include "particle.hpp"
#include "progargs.hpp"

#include <vector>


class malla {
  private:
    std::vector<Bloque> bloques;
    int n_x;
    int n_y;
    int n_z;
    int  tamano;

  public:
    malla(int num_x,int num_y,int num_z) : n_x(num_x), n_y(num_y), n_z(num_z), tamano(num_x * num_y * num_z) {
      bloques = std::vector<Bloque>(tamano);
    }
    // No entiendo el [[nodiscard]], culpas a .clang-tidy
    [[nodiscard]] int get_pos(int i, int j, int k) const ;
    std::vector<Bloque> get_bloques();
    std::vector<Bloque> bloques_contiguos(Bloque & bloque);
};

#endif
