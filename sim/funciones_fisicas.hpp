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
extern double masa_part;
extern double len_suavizado;

namespace func_fis {


    double masa(); //ppm variable global

    //double masa_part = masa();

    double suavizado(); //ppm y radio variables globales

    double num_bloques(double const& max, double const& min); //

    //double len_suavizado = suavizado();

    double tamanio_bloque(double const& max, double const& min);

    int check_index(int index);

    Vector3d indice_bloque(double const& min, double const& tamanio_bloque, Particle const& particula);

    void init_densidad_accel(std::vector<Particle> &new_vector, int particula);

    auto delta_densidades(int particula1, int particula2, std::vector<Particle> &old_vector, std::vector<Particle> &new_vector);

    double transform_densidad(std::vector<Particle> &new_vector, int particula);

    double trasnfer_accel_particulas(int particula1, int particula2, std::vector<Particle> &old_vector, std::vector<Particle> &new_vector);

}
#endif //PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
