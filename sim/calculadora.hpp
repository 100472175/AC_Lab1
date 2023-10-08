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

constexpr double const radio{1.695};          // Radio
constexpr double const dens_fluido{1e3};      // Densidad de fluido
constexpr double p_s{3.0};                    // Presión de rigidez
constexpr double s_c{128.0};                  // Collisión de rigidez
constexpr double const d_v{2e-3};             // Amortiguamiento
constexpr double const viscosidad{0.4};       // Viscosidad
constexpr double const d_p{2e-4};             // Tamaño de la partícula
constexpr double const delta_t{1e-3};         // Paso de tiempo
Vector3d const b_max(0.065, 0.1, 0.065);      // Límites de la caja máximos
Vector3d const b_min(-0.065, -0.08, -0.065);  // Límites de la caja mínimos
Vector3d const gravedad(0.0, -9.8, 0.0);      // Gravedad

class Calculadora {
  public:
    // Generales 3.5
    double masa_calc() const;  // ppm variable global

    double suavizado_calc() const;  // ppm y radio variables globales

    double ppm;
    double suavizado;
    double masa;
    int num_particulas;

    void inicializar_calculadora();

    Vector3d num_bloques_por_eje();

    Vector3d tamanio_bloque();

    Vector3d_int indice_bloque(Vector3d const & posicion);

    // 4.3.2
    // Inidiación de densidad y aceleraciones [pg. 8]
    void init_densidad_accel();

    double delta_densidades(Vector3d pos_1, Vector3d pos_2) const;

    double transform_densidad(double densidad) const;

    /*
        Vector3d trasnfer_accel_particulas_calculo(std::tuple<int, int> particula,
                                                   std::vector<Vector3d> & posicion,
                                                   std::vector<double> & densidad,
                                                   std::vector<Vector3d> & velocidad);

        static void trasnfer_accel_particulas(int particula1, int particula2,
                                              std::vector<Vector3d> & aceleracion,
                                              Vector3d & delta_aceleracion);
    */
    Vector3d aceleracion_primera_parte(Vector3d & posicion_1, Vector3d & posicion_2,
                                                 double densidad_1, double densidad_2) const;

    Vector3d aceleracion_segunda_parte(Vector3d & velocidad_1,
                                                 Vector3d & velocidad_2) const;

    Vector3d transferencia_aceleracion(Vector3d & parte1, Vector3d & parte2,
                                                        double const denominador);

    // 4.3.3
    double collisiones_limite_eje_x(Vector3d & posicion, Vector3d & velocidad,
                                    Vector3d & gradiente);
    double collisiones_limite_eje_y(Vector3d & posicion, Vector3d & velocidad,
                                    Vector3d & gradiente);
    double collisiones_limite_eje_z(Vector3d & posicion, Vector3d & velocidad,
                                    Vector3d & gradiente);

    // 4.3.4
    static std::tuple<Vector3d, Vector3d, Vector3d> actualizar_movimiento(Vector3d & posicion,
                                                                          Vector3d & velocidad,
                                                                          Vector3d & gradiente,
                                                                          Vector3d & aceleracion);

    Vector3d actualizar_posicion(Vector3d & posicion, Vector3d & gradiente, Vector3d & aceleracion);
    Vector3d actualizar_velocidad(Vector3d & gradiente, Vector3d & aceleracion);
    Vector3d actualizar_gradiente(Vector3d & gradiente, Vector3d & aceleracion);

    double interacciones_limite_eje_x(Vector3d posicion);
    double interacciones_limite_eje_y(Vector3d posicion);
    double interacciones_limite_eje_z(Vector3d posicion);
};
#endif  // PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
