#ifndef AC_LAB1_MALLA_H
#define AC_LAB1_MALLA_H

#include "Bloques.hpp"
#include "vector_3d.hpp"

#include <algorithm>
#include <array>
#include <vector>

/**
 * Abtrascción de la malla como conjunto de bloques.
 */
class Malla {
  public:
    std::vector<Bloque> bloques;  // conjunto de bloques
    int n_x{};                    // tamaño del eje x en número de bloques
    int n_y{};                    // tamaño del eje y en número de bloques
    int n_z{};                    // tamaño del eje z en número de bloques
    int tamano{};                 // número de bloques de la malla

    /**
     * inicialización del vector de bloques.
     */
    void crear_bloques();

    /**
     * Inicialización de la malla, da valores a todos sus atributos.
     *
     * @param n tamaño de la malla.
     */
    void inicializar_malla(Vector3d<int> n);

    /**
     * Dadas tres coordenadas, devuelve el índice de bloques en el array bloques de la malla.
     *
     * @param i coordenada del eje x.
     * @param j coordenada del eje y.
     * @param k coordenada del eje z.
     *
     * @return índice del bloque para el array malla.bloques.
     */
    [[nodiscard]] int get_pos(int i, int j, int k) const;
    [[nodiscard]] Vector3d<int> fuera_de_rango(Vector3d<int> & indices) const;
    void bloques_contiguos(int i, int j, int k);
    [[nodiscard]] int existe_bloque(int i, int j, int k) const;
};

#endif
