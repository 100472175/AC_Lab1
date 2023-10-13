//
// Created by Eduardo Alarcón on 27/9/23.
//

#ifndef PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
#define PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP

#include "particle.hpp"
#include "vector_3d.hpp"

#include <cmath>
#include <iostream>
#include <numbers>
#include <tuple>
#include <vector>

// PPM y Num_particulas son variables que se calculan en el constructor
// Suavizado se calcula dentro de la clase

constexpr double const radio{1.695};                  // Radio
constexpr double const dens_fluido{1e3};              // Densidad de fluido
constexpr double p_s{3.0};                            // Presión de rigidez
constexpr double s_c{128.0};                          // Collisión de rigidez
constexpr double const d_v{2e-3};                     // Amortiguamiento
constexpr double const viscosidad{0.4};               // Viscosidad
constexpr double const d_p{2e-4};                     // Tamaño de la partícula
constexpr double const delta_t{1e-3};                 // Paso de tiempo
Vector3d<double> const b_max(0.065, 0.1, 0.065);      // Límites de la caja máximos
Vector3d<double> const b_min(-0.065, -0.08, -0.065);  // Límites de la caja mínimos
Vector3d<double> const gravedad(0.0, -9.8, 0.0);      // Gravedad
constexpr double const densidad_inicial{0.0};

class Calculadora {
  public:
    double ppm;
    double suavizado;
    double masa;
    int num_particulas;

    void inicializar_calculadora();

    Vector3d<double> num_bloques_por_eje();

    Vector3d<double> tamanio_bloque();

    Vector3d<int> indice_bloque(Vector3d<double> const & posicion);

    // 4.3.2
    // Inidiación de densidad y aceleraciones [pg. 8]
    void init_densidad_accel();

    double delta_densidades(double distancia_cuadrado) const;

    double transform_densidad(double densidad) const;

    Vector3d<double> aceleracion_primera_parte(Vector3d<double> & posicion_1,
                                               Vector3d<double> & posicion_2, double densidad_1,
                                               double densidad_2) const;

    Vector3d<double> aceleracion_segunda_parte(Vector3d<double> & velocidad_1,
                                               Vector3d<double> & velocidad_2) const;

    Vector3d<double> transferencia_aceleracion(Vector3d<double> & parte1, Vector3d<double> & parte2,
                                               double const & denom);

    // 4.3.3
    double colisiones_limite_eje_x(int bloque, double const & delta_x,
                                   Vector3d<double> & velocidad);
    double colisiones_limite_eje_y(int bloque, double const & delta_y,
                                   Vector3d<double> & velocidad);
    double colisiones_limite_eje_z(int bloque, double const & delta_z,
                                   Vector3d<double> & velocidad);

    // 4.3.4

    Vector3d<double> actualizar_posicion(Vector3d<double> & posicion, Vector3d<double> & gradiente,
                                         Vector3d<double> & aceleracion);
    Vector3d<double> actualizar_velocidad(Vector3d<double> & gradiente,
                                          Vector3d<double> & aceleracion);
    Vector3d<double> actualizar_gradiente(Vector3d<double> & gradiente,
                                          Vector3d<double> & aceleracion);

    double interacciones_limite_eje_x(double const d_x, int bloque);
    double interacciones_limite_eje_y(double const d_y, int bloque);
    double interacciones_limite_eje_z(double const d_y, int bloque);

    // Funciones Extras
    static double cuadrado_distancias(Vector3d<double> posicion_1, Vector3d<double> posicion_2);
};
#endif  // PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
