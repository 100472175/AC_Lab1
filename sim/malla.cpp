//
// Created by adrian on 9/29/23.
//
#include "malla.hpp"

#include <iostream>

void Malla::crear_bloques() {
  bloques = std::vector<Bloque>(tamano, Bloque(0,0,0,0));
  for (int z = 0; z < n_z; z++) {
      for (int y = 0; y < n_y; y++) {
          for (int x = 0; x < n_x; x++) {
              int pos = get_pos(x, y, z);
              Bloque bloque(x, y, z, pos);
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

void Malla::bloques_contiguos(int pos_bloque) {
  int pos_temp                          = 0;
  int pos_bloq_cont                     = 0;
  int const factor_despl_i              = 1;
  int const factor_despl_j              = n_x;
  int const factor_despl_k              = n_x * n_y;
  // Hacer un vector constante no es buena practica
  std::array const desplazamiento = {-1, 0, 1};
  // Guardar en un vector todas las combinaciones de i+1,j+1,z+1,i+0,j+0,z+0,i-1,j-1,z-1
  for (int const desplaz_i : desplazamiento) {
    for (int const desplaz_j : desplazamiento) {
      for (int const desplaz_k : desplazamiento) {
        pos_temp =
            desplaz_i * factor_despl_i + desplaz_j * factor_despl_j + desplaz_k * factor_despl_k;
        pos_bloq_cont = pos_bloque + pos_temp;
        // Si cualquier combinación se sale de la malla no se guarda el particulas porque no existe
        std::cout << "bloque contiguo: "<< pos_bloq_cont << "\n";
        if (pos_bloq_cont >= 0 && pos_bloq_cont < tamano) {
          // Guardo pos_bloq_contiguos en los bloques contiguos
          // del bloque dado por la posicion pos_bloque
          bloques[pos_bloque].bloques_contiguos.push_back(pos_bloq_cont);
        }
      }
    }
  }
}