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
      int i = func_fis::indice_bloque(particula.p.x,b_min[0],func_fis::tamanio_bloque(b_max[0],b_min[0],h));
      int j = func_fis::indice_bloque(particula.p.y,b_min[1],func_fis::tamanio_bloque(b_max[1],b_min[1],h));
      int k = func_fis::indice_bloque(particula.p.z,b_min[2],func_fis::tamanio_bloque(b_max[2],b_min[2],h));
      int ind_real = get_pos(i,j,k);
      bloques[ind_real].bloque.push_back(particula.id);
    }
}