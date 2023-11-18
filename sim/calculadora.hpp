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

    /**
     * Función de utilidad para calcular e inicializar el suavizado que se utilizará durante la
     * simulación y la masa de cada partícula.
     */
    void inicializar_calculadora();

    /**
     * Función de utilidad para calcular el bloque en el que se encuentra una partícula.
     *
     * @param posicion Vector que tiene las coordenadas de la partícula.
     *
     * @return Vector que tiene las coordenadas del bloque en el que se encuentra la partícula.
     */
    [[nodiscard]] Vector3d<int> indice_bloque(Vector3d<double> const & posicion) const;

    /**
     * Función que revuelve el número de bloques que hay en a malla para esta simulación concreta.
     *
     * @return Vector con el número de bloques por eje.
     */
    [[nodiscard]] constexpr Vector3d<int> num_bloques_por_eje() const {
      Vector3d<double> aux  = b_max - b_min;
      aux                  /= (double) suavizado;
      aux.x                 = floor(aux.x);
      aux.y                 = floor(aux.y);
      aux.z                 = floor(aux.z);
      return aux;
    };

    /**
     * Función que calcula el tamaño de cada bloque.
     *
     * @return Vector con el tamaño de cada bloque en las diferentes coordenadas, x, y, z.
     */
    [[nodiscard]] constexpr Vector3d<double> tamanio_bloque() const {
      return (b_max - b_min) / num_bloques_por_eje();
    };

    /**
     * Función que devuelve la diferencia entre el suavizado al cuadrado y la distancia al cuadrado
     * al cubo.
     *
     * @param distancia_cuadrado Cuadrado de la distancia entre dos partículas
     *
     * @return Diferencia entre el suavizado al cuadrado y la distancia al cuadrado al cubo.
     */
    [[nodiscard]] constexpr double delta_densidades(double distancia_cuadrado) const {
      double const suavizado_temp = suavizado * suavizado;
      return pow((suavizado_temp - distancia_cuadrado), 3);
    };

    [[nodiscard]] constexpr double transform_densidad(double densidad) const {
      double const parte_1 =
          (densidad + pow(suavizado, 6)) * (operador_densidad / pow(suavizado, 9));
      return parte_1 * masa;
    };

    [[nodiscard]] constexpr Vector3d<double> acel1(Vector3d<double> const & pos_1,
                                                   Vector3d<double> const & pos_2,
                                                   double const densidad_1,
                                                   double const densidad_2) const {
      double const distancia = sqrt(fmax(Vector3d<double>::sq_distancia(pos_1, pos_2), 1e-12));
      Vector3d<double> const diff_posiciones = pos_1 - pos_2;
      double const acceleration_2            = 15 / (std::numbers::pi * pow(suavizado, 6)) *
                                    (3 * masa * p_s * 0.5) * pow(suavizado - distancia, 2) /
                                    distancia;
      double const acceleration_3 = densidad_1 + densidad_2 - (2 * dens_fluido);
      return diff_posiciones * acceleration_2 * acceleration_3;
    };

    [[nodiscard]] constexpr Vector3d<double> acel2(Vector3d<double> const & velocidad_1,
                                                   Vector3d<double> const & velocidad_2) const {
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
                                                    Vector3d<double> const & velocidad) {
      if (bloque == 0) { return (s_c * delta_x - d_v * velocidad.x); }
      return -(s_c * delta_x + d_v * velocidad.x);
    };

    constexpr static double colisiones_limite_eje_y(int bloque, double const & delta_y,
                                                    Vector3d<double> const & velocidad) {
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

    constexpr static Vector3d<double> actualizar_velocidad(Vector3d<double> const & gradiente,
                                                           Vector3d<double> const & aceleracion) {
      return gradiente + (aceleracion * (delta_t / (double) 2));
    };

    /**
     * Función que devuelve el nuevo gradiente de una particula, dado el gradiente velocidad y la
     * aceleración de esa partícula
     *
     * @param gradiente Vector3D con las 3 coordenadas del gradiente.
     * @param aceleracion Vector3D con las 3 coordenadas de la aceleración.
     *
     * @return Devuelve un Vector3d de tipo double con las calculos realizados
     */
    constexpr static Vector3d<double> actualizar_gradiente(Vector3d<double> const & gradiente,
                                                           Vector3d<double> const & aceleracion) {
      return gradiente + aceleracion * delta_t;
    };

    /**
     * Función que devuelve la nueva posición x de la partícula.
     *
     * @param d_x Diferencia entre el borde de la malla y la posición x de la partícula.
     * @param bloque Indica si es el primer bloque o el último.
     *
     * @return Devuelve un double con el valor calculado
     */
    constexpr static double interacciones_limite_eje_x(double const d_x, int bloque) {
      if (bloque == 0) { return b_min.x - d_x; }
      if (bloque == -1) { return b_max.x + d_x; }
      return 0.0;
    };

    /**
     * Función que devuelve la nueva posición y de la partícula
     *
     * @param d_y Diferencia entre el borde de la malla y la posición y de la particula
     * @param bloque Indica si es el primer bloque o el último
     *
     * @return Devuelve un double con el valor calculado
     */
    constexpr static double interacciones_limite_eje_y(double const d_y, int bloque) {
      if (bloque == 0) { return b_min.y - d_y; }
      if (bloque == -1) { return b_max.y + d_y; }
      return 0.0;
    };

    /**
     * Función que devuelve la nueva posición z de la partícula
     *
     * @param d_z Diferencia entre el borde de la malla y la posición z de la partícula
     * @param bloque Indica si es el primer bloque o el último
     *
     * @return Devuelve un double con el valor calculado
     */
    constexpr static double interacciones_limite_eje_z(double const d_z, int bloque) {
      if (bloque == 0) { return b_min.z - d_z; }
      if (bloque == -1) { return b_max.z + d_z; }
      return 0.0;
    };
};
#endif  // PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
