//
// Created by adrian on 9/29/23.
//
#include "Malla.hpp"
using namespace std;
// el const de esta función se puso por clang
int Malla::get_pos(int i,int j,int k) const{
  /*if (0 > i >= n_x){
    throw i_no_valida;
  }
  if (0 > j >= n_y){
    throw j_no_valida;
  }
  if (0 > k >= n_x){
    throw k_no_valida;
  }
   */
  int pos = i + j * n_x + k * n_x * n_y;
  return pos;
}
void Malla::poblar_malla(vector<Particle> const &v_particulas){
    for (Particle particula: v_particulas){
      Vector3d bloque_coords = func_fis::indice_bloque(b_min.x,func_fis::tamanio_bloque(b_max.x,b_min.x), particula);
      int ind_real = get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
      bloques[ind_real].bloque.push_back(particula.id);
    }
}