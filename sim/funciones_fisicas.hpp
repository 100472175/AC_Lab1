//
// Created by Eduardo Alarcón on 27/9/23.
//

#ifndef PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
#define PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP

#include <numbers>
#include <cmath>
#include <vector>
#include <iostream>

#include "vector_3d.hpp"
#include "particle.hpp"


extern double ppm;
extern int np;
extern double const r;
extern const double dens_fluido;
extern double h;
extern const Vector3d b_max;
extern const Vector3d b_min;
extern double ppm;
extern int np;
extern const double delta_t;
extern const double d_p;
extern const double d_v;
extern const double s_c;

namespace func_fis {

    // Generales 3.5
    double masa(); //ppm variable global

    double suavizado(); //ppm y radio variables globales

    double num_bloques(double const& max, double const& min); //

    double tamanio_bloque(double const& max, double const& min);

    int check_index(int index);

    Vector3d_int indice_bloque(Particle const& particula);


    // 4.3.2
    void init_densidad_accel(std::vector<Particle> &new_vector, int particula);

    auto delta_densidades(int particula1, int particula2, std::vector<Particle> &old_vector, std::vector<Particle> &new_vector);

    double transform_densidad(std::vector<Particle> &new_vector, int particula);

    double trasnfer_accel_particulas(int particula1, int particula2, std::vector<Particle> &old_vector, std::vector<Particle> &new_vector);

    // 4.3.3
    void collisiones_limite_eje_x(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    void collisiones_limite_eje_y(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    void collisiones_limite_eje_z(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    // 4.3.4
    void actualizar_posicion(int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    void actualizar_velocidad(int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    void actualizar_gradiente(int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    void actualizar_movimiento(int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);





    void interacciones_limite_eje_x(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    void interacciones_limite_eje_y(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);

    void interacciones_limite_eje_z(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector);



}
#endif //PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
