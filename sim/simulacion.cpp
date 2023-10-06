//
// Created by adrian on 10/6/23.
//
#include "simulacion.hpp"

Particle Simulacion::iterador() {
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
