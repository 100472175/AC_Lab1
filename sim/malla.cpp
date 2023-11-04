//
// Created by adrian on 9/29/23.
//
#include "malla.hpp"

#include <iostream>

void Malla::crear_bloques() {
  bloques = std::vector<Bloque>(tamano, Bloque(0,0,0));
  for (int eje_z = 0; eje_z < n_z; eje_z++) {
      for (int eje_y = 0; eje_y < n_y; eje_y++) {
          for (int eje_x = 0; eje_x < n_x; eje_x++) {
              int const pos = get_pos(eje_x, eje_y, eje_z);
              Bloque const bloque(eje_x, eje_y, eje_z);
              bloques[pos] = bloque;
          }
      }
  }
}

void Malla::inicializar_malla(Vector3d<double> n) {
  n_x    = int(n.x);
  n_y    = int(n.y);
  n_z    = int(n.z);
  tamano = n_x * n_y * n_z;
  crear_bloques();
}

int Malla::get_pos(int i, int j, int k) const {
  int const pos = i + j * n_x + k * n_x * n_y;
  return pos;
}

Vector3d<int> Malla::fuera_de_rango(Vector3d<int> & indices) const {
  if (indices.x < 0) {
    indices.x = 0;
  } else if (indices.x > n_x - 1) {
    indices.x = n_x - 1;
  }
  if (indices.y < 0) {
    indices.y = 0;
  } else if (indices.y > n_y - 1) {
    indices.y = n_y - 1;
  }
  if (indices.z < 0) {
    indices.z = 0;
  } else if (indices.z > n_z - 1) {
    indices.z = n_z - 1;
  }
  return indices;
}
int Malla::existe_bloque(int i, int j , int k) const {
  if (i < 0|| i > n_x -1|| j < 0|| j > n_y -1|| k < 0|| k > n_z -1) {
    return -1;
  }
  return 0;
}


void Malla::bloques_contiguos(int i, int j, int k) {
  int const indice_bloque = get_pos(i,j,k);
  for( int x_pos= i-1; x_pos <= i +1; x_pos++){
    for( int y_pos= j-1; y_pos <= j +1; y_pos++){
        for( int z_pos = k-1; z_pos <= k +1; z_pos++){
              if(existe_bloque(x_pos, y_pos, z_pos) == 0){
                int const indice_contiguo = get_pos(x_pos, y_pos, z_pos);
                bloques[indice_bloque].bloques_contiguos.push_back(indice_contiguo);
              }
        }
    }
  }
}