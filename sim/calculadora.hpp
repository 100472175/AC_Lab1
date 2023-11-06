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
constexpr double const p_s{3.0};                      // Presión de rigidez
constexpr double const s_c{3e4};                      // Collisión de rigidez
constexpr double const d_v{128};                      // Amortiguamiento
constexpr double const viscosidad{0.4};               // Viscosidad
constexpr double const d_p{2e-4};                     // Tamaño de la partícula
constexpr double const delta_t{1e-3};                 // Paso de tiempo
Vector3d<double> const b_max(0.065, 0.1, 0.065);      // Límites de la caja máximos
Vector3d<double> const b_min(-0.065, -0.08, -0.065);  // Límites de la caja mínimos
Vector3d<double> const gravedad(0.0, -9.8, 0.0);      // Gravedad
constexpr double const operador_densidad{315 / (64 * std::numbers::pi)};

class Calculadora {
  public:
    double ppm;
    double suavizado;
    double masa;
    int num_particulas;

    void inicializar_calculadora();

    [[nodiscard]] constexpr Vector3d<double> num_bloques_por_eje() const {
      Vector3d<double> aux  = b_max - b_min;
      aux                  /= (double) suavizado;
      aux.x                 = floor(aux.x);
      aux.y                 = floor(aux.y);
      aux.z                 = floor(aux.z);
      return aux;
    };

    [[nodiscard]] constexpr Vector3d<double> tamanio_bloque() const {
      return (b_max - b_min) / num_bloques_por_eje();
    };

    [[nodiscard]] Vector3d<int> indice_bloque(Vector3d<double> const & posicion) const;

    // 4.3.2
    // Inidiación de densidad y aceleraciones [pg. 8]

    [[nodiscard]] constexpr double delta_densidades(double distancia_cuadrado) const {
      double const suavizado_temp = suavizado * suavizado;
      return pow((suavizado_temp - distancia_cuadrado), 3);
    };

    [[nodiscard]] constexpr double transform_densidad(double densidad) const {
      double const parte_1 =
          (densidad + pow(suavizado, 6)) * (operador_densidad / pow(suavizado, 9));
      return parte_1 * masa;
    };

    constexpr Vector3d<double> acel_p1(Vector3d<double> & posicion_1,
                                                         Vector3d<double> & posicion_2,
                                                         double densidad_1,
                                                         double densidad_2) const {
      double const distancia =
          sqrt(fmax(Vector3d<double>::sq_distancia(posicion_1, posicion_2), 1e-12));
      Vector3d<double> const diff_posiciones = posicion_1 - posicion_2;
      double const acceleration_2            = 15 / (std::numbers::pi * pow(suavizado, 6)) *
                                    (3 * masa * p_s * 0.5) * pow(suavizado - distancia, 2) /
                                    distancia;
      double const acceleration_3 = densidad_1 + densidad_2 - (2 * dens_fluido);
      return diff_posiciones * acceleration_2 * acceleration_3;
    };

    constexpr Vector3d<double> acel_p2(Vector3d<double> & velocidad_1,
                                                         Vector3d<double> & velocidad_2) const {
      Vector3d<double> const resultado =
          (velocidad_2 - velocidad_1) *
          ((45 / (std::numbers::pi * pow(suavizado, 6)) * viscosidad * masa));
      return resultado;
    };

    // Devuelve la aceleación que se tiene que sumar o restar a la original
    constexpr static Vector3d<double> transferencia_aceleracion(Vector3d<double> & parte1,
                                                                Vector3d<double> const & parte2,
                                                                double const & denom) {
      parte1 += parte2;
      parte1 /= denom;
      return parte1;
    };

    // 4.3.3
    constexpr static double colisiones_limite_eje_x(int bloque, double const & delta_x,
                                                    Vector3d<double> & velocidad) {
      if (bloque == 0) { return (s_c * delta_x - d_v * velocidad.x); }
      return -(s_c * delta_x + d_v * velocidad.x);
    };

    constexpr static double colisiones_limite_eje_y(int bloque, double const & delta_y,
                                                    Vector3d<double> & velocidad) {
      if (bloque == 0) { return (s_c * delta_y - d_v * velocidad.y); }
      return -(s_c * delta_y + d_v * velocidad.y);
    };

    constexpr static double colisiones_limite_eje_z(int bloque, double const & delta_z,
                                                    Vector3d<double> const & velocidad) {
      if (bloque == 0) { return (s_c * delta_z - d_v * velocidad.z); }
      return -(s_c * delta_z + d_v * velocidad.z);
    };

    // 4.3.4

    constexpr static Vector3d<double> actualizar_posicion(Vector3d<double> const & posicion,
                                                          Vector3d<double> const & gradiente,
                                                          Vector3d<double> const & aceleracion) {
      return posicion + (gradiente * delta_t) + (aceleracion * delta_t * delta_t);
    };

    constexpr static Vector3d<double> actualizar_velocidad(Vector3d<double> & gradiente,
                                                           Vector3d<double> & aceleracion) {
      return gradiente + (aceleracion * (delta_t / (double) 2));
    };

    constexpr static Vector3d<double> actualizar_gradiente(Vector3d<double> & gradiente,
                                                           Vector3d<double> & aceleracion) {
      return gradiente + aceleracion * delta_t;
    };

    constexpr static double interacciones_limite_eje_x(double const d_x, int bloque) {
      if (bloque == 0) { return b_min.x - d_x; }
      if (bloque == -1) { return b_max.x + d_x; }
      return 0.0;
    };

    constexpr static double interacciones_limite_eje_y(double const d_y, int bloque) {
      if (bloque == 0) { return b_min.y - d_y; }
      if (bloque == -1) { return b_max.y + d_y; }
      return 0.0;
    };

    constexpr static double interacciones_limite_eje_z(double const d_z, int bloque) {
      if (bloque == 0) { return b_min.z - d_z; }
      if (bloque == -1) { return b_max.z + d_z; }
      return 0.0;
    };
};
#endif  // PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
