//
// Created by adrian on 10/6/23.
//

#ifndef FLUID_SIMULACION_HPP
#define FLUID_SIMULACION_HPP

#include "calculadora.hpp"
#include "malla.hpp"
#include "particle.hpp"

#include <iostream>
#include <vector>

class Simulacion {
  public:
    int num_iteraciones;
    int num_particulas;
    double ppm;
    Particulas particulas;
    Malla malla;
    Calculadora calculadora;

    void iterador();
    void iteracion();
    void poblar_malla();
    void reposicionamiento();
    // Son funciones para estructurar el código, cambiad lo que sea necesario
    void colisiones_particulas();
    void colision_particula_limite_x(int indice);
    void colision_particula_limite_y(int indice);
    void colision_particula_limite_z(int indice);
    void colision_particula_limite();
    void rebote_particula_limite();
    void movimiento_particulas();
    void print_simulation_parameters();
};

#endif  // FLUID_SIMULACION_HPP
