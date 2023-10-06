//
// Created by adrian on 10/6/23.
//

#ifndef FLUID_SIMULACION_HPP
#define FLUID_SIMULACION_HPP

#include "progargs.hpp"
#include "calculadora.hpp"
#include "particle.hpp"
#include "Malla.hpp"
class Simulacion {
  public:
    int num_iteraciones;
    int num_particulas;
    double ppm;
    Particulas particulas;
    Particulas iterador();
    Malla malla;
    Calculadora calculadora;
    void iteracion();
    void poblar_malla();
    void reposicionamiento();
    // Son funciones para estructurar el código, cambiad lo que sea necesario
    void colisiones_particulas();
    void colision_particula_limite();
    void rebote_particula_limite();
    void movimiento_particulas();
};




#endif  // FLUID_SIMULACION_HPP
