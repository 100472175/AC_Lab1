//
// Created by adrian on 9/29/23.
//
#include "malla.hpp"

std::vector<Bloque> Malla::get_bloques(){
  return bloques;
}
// el const de esta función se puso por clang
int Malla::get_pos(int i, int j, int k) const {
  int const pos = i + j * n_x + k * n_x * n_y;
  return pos;
}
std::vector<Bloque> Malla::bloques_contiguos(Bloque & bloque){
  // Buscar el bloque dado por parametro en la malla
  // Guardar en un vector todas las combinaciones de i+1,j+1,z+1,i+0,j+0,z+0,i-1,j-1,z-1
    std::vector<Bloque> v;
    v.push_back(bloque);
  return v;
}