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
  malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++){
    malla.bloques_contiguos(malla.bloques[i]);
  }
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
  for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d_int bloque_coords = calculadora.indice_bloque(particulas.posicion[cont]);
    bloque_coords = malla.fuera_de_rango(bloque_coords);
    int const ind_real = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    malla.bloques[ind_real].bloque.push_back(cont);
  }
}
void Simulacion::reposicionamiento() {
  for (int i = 0; i < malla.tamano; i++) {
    // Limpio las partículas de cada bloue
    malla.bloques[i].bloque.erase(malla.bloques[i].bloque.begin(), malla.bloques[i].bloque.end());
  }
  // Y la vuelvo a repoblar
  for (int cont = 0; cont < num_particulas; cont++) {
    Vector3d_int const bloque_coords = calculadora.indice_bloque(particulas.posicion[cont]);
    int const ind_real = malla.get_pos(bloque_coords.x, bloque_coords.y, bloque_coords.z);
    malla.bloques[ind_real].bloque.push_back(cont);
  }
}
  void Simulacion::colisiones_particulas() {
    std::cout << "XD";
  }
  void Simulacion::colision_particula_limite() {
    std::cout << "XD";
  }
  void Simulacion::rebote_particula_limite() {
    std::cout << "XD";
  }
  void Simulacion::movimiento_particulas() {
    std::cout << "XD";
  }

void Simulacion::print_simulation_parameters() {
    Vector3d tamanio_bloque = calculadora.tamanio_bloque();
    std::cout << "Number of particles: " << num_particulas << "\n" <<
    "Particles per meter: " << ppm << "\n" <<
    "Smoothing length: " << calculadora.suavizado << "\n" <<
    "Particle mass: " << calculadora.masa << "\n" <<
    "Grid size: " << malla.n_x << " x " << malla.n_y << " x " << malla.n_z << "\n" <<
    "Number of blocks: " << malla.tamano << "\n" <<
    "Block size: " << tamanio_bloque.x << " x " << tamanio_bloque.y << " x " << tamanio_bloque.z << "\n";
}
