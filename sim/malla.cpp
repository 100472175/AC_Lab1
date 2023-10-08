//
// Created by adrian on 9/29/23.
//
#include "malla.hpp"

void Malla::crear_bloques() {
  bloques = std::vector<Bloque>(tamano);
  for (int i = 0; i < tamano;i++){
    bloques[i] = Bloque();
  }
}

void Malla::inicializar_malla(Vector3d<double> n) {
  n_x = int(n.x);
  n_y = int(n.y);
  tamano = n_x * n_y * int(n.z);
  crear_bloques();
}

int Malla::get_pos(int i, int j, int k) const {
  int const pos = i + j * n_x + k * n_x * n_y;
  return pos;
}

Vector3d<int> Malla::fuera_de_rango(Vector3d<int> & indices) const {
  if (indices.x < 0) {
    indices.x = 0;
  } else if (indices.x > n_x-1) {
    indices.x = n_x;
  }
  if (indices.y < 0) {
    indices.y = 0;
  } else if (indices.y > n_y-1) {
    indices.y = n_y;
  }
  if (indices.z < 0) {
    indices.z = 0;
  } else if (indices.z > n_z) {
    indices.z = n_z;
  }
  return indices;
}

bool CompararVectores(std::vector<int> vec1,std::vector<int> vec2,int tamano){
  for (int i = 0; i < tamano; i++){
    if (vec1[i] != vec2[i]){
      return false;
    }
  }
  return true;
}

void Malla::bloques_contiguos(Bloque & bloque_ref){
  int pos_bloque = 0;
  int pos_temp = 0;
  int const factor_despl_i = 1;
  int const factor_despl_j = n_x;
  int const factor_despl_k = n_x*n_y;
  std::vector<int> const desplazamiento = {-1,0,1};
  // Buscar el bloque dado por parametro en la malla
  while(not (CompararVectores(bloques[pos_bloque].bloque,bloque_ref.bloque,tamano))){
      pos_bloque++;
  }
  // Guardar en un vector todas las combinaciones de i+1,j+1,z+1,i+0,j+0,z+0,i-1,j-1,z-1
  for(int const desplaz_i : desplazamiento){
    for (int const desplaz_j : desplazamiento){
      for(int const desplaz_k : desplazamiento){
        pos_temp = desplaz_i * factor_despl_i + desplaz_j * factor_despl_j + desplaz_k * factor_despl_k;
        // Si cualquier combinación se sale de la malla no se guarda el bloque porque no existe
        if (pos_temp >= 0 && pos_temp < tamano){
          bloque_ref.bloques_contiguos.push_back(bloques[pos_temp]);
        }
      }
    }
  }
}