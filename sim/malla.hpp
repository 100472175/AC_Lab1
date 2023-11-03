#ifndef AC_LAB1_MALLA_H
#define AC_LAB1_MALLA_H

#include "Bloques.hpp"
#include "vector_3d.hpp"

#include <array>
#include <algorithm>
#include <vector>

class Malla {
  public:
    std::vector<Bloque> bloques;
    int n_x;
    int n_y;
    int n_z;
    int tamano;

    void crear_bloques();
    void inicializar_malla(Vector3d<double> n);
    // No entiendo el [[nodiscard]], culpas a .clang-tidy
    [[nodiscard]] int get_pos(int i, int j, int k) const;
    [[nodiscard]] Vector3d<int> fuera_de_rango(Vector3d<int> & indices) const;
    void bloques_contiguos(int i, int j, int k);
    [[nodiscard]] int existe_bloque(int i, int j, int k) const;
};

#endif
