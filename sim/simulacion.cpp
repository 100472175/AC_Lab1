//
// Created by adrian on 10/6/23.
//
#include "simulacion.hpp"

/*Simulacion::Simulacion() : num_iteraciones(0), num_particulas(0), ppm(0.0) {
                                             Calculadora inst_calculadora(ppm);
                                             calculadora = inst_calculadora;
                                             Malla inst_malla(calculadora.indice_bloques(), calculadora.indice_bloques(), calculadora.indice_bloques())
                                             malla = inst_malla;
                                           };*/


void Simulacion::iterador() {
  poblar_malla();
  for (int i = 0; i < num_iteraciones; i++){
    iteracion();
  }
}

void Simulacion::iteracion(){
  for (int i = 0; i < num_particulas;i++){
    reposicionamiento();
  }
  for (int i = 0; i < num_particulas;i++){
    colisiones_particulas();
  }
  for (int i = 0; i < num_particulas; i++){
    colision_particula_limite();
  }
  for (int i = 0; i < num_particulas; i++){
    movimiento_particulas();
  }
  for (int i = 0; i < num_particulas; i++){
    rebote_particula_limite();
  }
}

void Simulacion::poblar_malla() {
  std::cout << "XD";
  /*for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d_int bloque_coords = func_fis::indice_bloque(v_particulas[cont]);
    bloque_coords = Progargs::fuera_de_rango(bloque_coords);
    int const ind_real = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    std::vector<Bloque>bloques = malla.get_bloques();
    bloques[ind_real].bloque.push_back(cont);
  }
   */
}
void Simulacion::colision_particula_limite() {
  std::cout << "XD";
}

void Simulacion::reposicionamiento() {
  std::cout << "XD";
}
void Simulacion::colisiones_particulas() {
  std::cout << "XD";
}
void Simulacion::rebote_particula_limite() {
  std::cout << "XD";
}
void Simulacion::movimiento_particulas() {
  std::cout << "XD";
}
