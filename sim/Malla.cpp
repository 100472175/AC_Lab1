//
// Created by adrian on 9/29/23.
//
#include "Malla.hpp"

using namespace std;

vector<Bloque> Malla::get_bloques(){
  return bloques;
}
// el const de esta función se puso por clang
int Malla::get_pos(int i, int j, int k) const {
  int pos = i + j * n_x + k * n_x * n_y;
  return pos;
}

void Malla::poblar_malla(vector<Particle> const & v_particulas) {
  for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d_int bloque_coords = func_fis::indice_bloque(v_particulas[cont]);
    bloque_coords = Sim::Progargs::fuera_de_rango(bloque_coords);
    int ind_real = get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    bloques[ind_real].bloque.push_back(cont);
  }
}

vector<Bloque> Malla::bloques_contiguos(Bloque & bloque){
  // Buscar el bloque dado por parametro en la malla
  // Guardar en un vector todas las combinaciones de i+1,j+1,z+1,i+0,j+0,z+0,i-1,j-1,z-1
}