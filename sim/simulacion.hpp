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
    Particulas particulas;
    Malla malla;
    Calculadora calculadora;
    Simulacion(int n_i, int n_p, Calculadora calc, Malla m) : num_iteraciones(n_i), num_particulas(n_p) ,malla(m), calculadora(calc){}
    void iterador();
    void iteracion();
    void poblar_malla();
    void reposicionamiento();
    // Son funciones para estructurar el código, cambiad lo que sea necesario
    void colisiones_particulas();
    void colision_particula_limite();
    void colision_particula_limite_x(int indice, int bloque);
    void colision_particula_limite_y(int indice, int bloque);
    void colision_particula_limite_z(int indice, int bloque);
    void rebote_particula_limite();
    void rebote_particula_limite_x(std::vector<int> & particulas, int bloque);
    void rebote_particula_limite_y(std::vector<int> & particulas, int bloque);
    void rebote_particula_limite_z(std::vector<int> & particulas, int bloque);
    void movimiento_particulas();
    void print_simulation_parameters();
    void colisiones_particulas_aceleracion();
    void colisiones_particulas_densidad();
};

#endif  // FLUID_SIMULACION_HPP
