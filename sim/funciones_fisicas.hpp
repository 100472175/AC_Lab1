//
// Created by Eduardo Alarcon on 27/9/23.
//

#ifndef PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
#define PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP

#include "particle.hpp"
#include "vector_3d.hpp"
#include <numbers>
#include <cmath>
#include <vector>

extern double ppm;
extern int np;
extern double const r;
extern const double dens_fluido;

namespace func_fis {
    double masa(); //ppm variable global

    double suavizado(); //ppm y radio variables globales

    double num_bloques(double const& max, double const& min, double const& suavizado); //

    double tamanio_bloque(double const& max, double const& min, double const& suavizado);

    int check_index(int index);

    int indice_bloque(double const& posicion, double const& min, double const& tamanio_bloque);

    void init_dens_accel(std::vector<Particle> &new_vector, int particula);

    double delta_densidades(double len_suavizado, Particle const& part1, Particle const& part2);

    double transform_densidad(Particle const& particula, double const& suavizado, double const& masa);
}
#endif //PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
