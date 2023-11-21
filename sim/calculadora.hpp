#ifndef PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
#define PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP

#include "particle.hpp"
#include "vector_3d.hpp"

#include <cmath>
#include <iostream>
#include <numbers>
#include <tuple>
#include <vector>

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

/**
 * Clase encargada de la implementación de todas las operaciones matemáticas.
 */
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
      return aux.to_int();
    };

    /**
     * Función que calcula el tamaño de cada bloque.
     *
     * @return Vector con el tamaño de cada bloque en las diferentes coordenadas, x, y, z.
     */
    [[nodiscard]] constexpr Vector3d<double> tamanio_bloque() const {
      return (b_max - b_min) / num_bloques_por_eje().to_double();
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

    /**
     * Función que devuelve la densidad transformada de una partícula.
     *
     * @param densidad Densidad de una partícula
     *
     * @return
     */
    [[nodiscard]] constexpr double transform_densidad(double densidad) const {
      double const parte_1 =
          (densidad + pow(suavizado, 6)) * (operador_densidad / pow(suavizado, 9));
      return parte_1 * masa;
    };

    /**
     * Cálculo de la primera parte de la aceleración en la formula general de la transferencia de
     * aceleración.
     *
     * @param pos_1 Posición de la primera partícula.
     * @param pos_2 Posición de la segunda partícula.
     * @param densidad_1 Densidad de la primera partícula.
     * @param densidad_2 Densidad de la segunda partícula.
     *
     * @return Vector con las componentes de la aceleración de la primera parte.
     */
    [[nodiscard]] constexpr Vector3d<double> acel1(Vector3d<double> const & pos_1,
                                                   Vector3d<double> const & pos_2,
                                                   double const densidad_1,
                                                   double const densidad_2) const {
      double const distancia = sqrt(fmax(Vector3d<double>::sq_distancia(pos_1, pos_2), 1e-12));
      Vector3d<double> const diff_posiciones = pos_1 - pos_2;
      double const acceleration_2            = 15 / (std::numbers::pi * pow(suavizado, 6)) *
                                    (masa * p_s * 1.5) * pow(suavizado - distancia, 2) / distancia;
      double const acceleration_3 = densidad_1 + densidad_2 - (2 * dens_fluido);
      return diff_posiciones * acceleration_2 * acceleration_3;
    };

    /**
     * Cálculo de la segunda parte de la transferencia de la aceleración.
     *
     * @param velocidad_1 Las 3 componentes de la velocidad de la primera partícula.
     * @param velocidad_2 Las 3 componentes de la velocidad de la segunda partícula.
     *
     * @return Vector con las componentes de la segunda parte del cálculo de la transferencia de la
     * aceleración.
     */
    [[nodiscard]] constexpr Vector3d<double> acel2(Vector3d<double> const & velocidad_1,
                                                   Vector3d<double> const & velocidad_2) const {
      Vector3d<double> const resultado =
          (velocidad_2 - velocidad_1) *
          ((45 / (std::numbers::pi * pow(suavizado, 6)) * viscosidad * masa));
      return resultado;
    };

    /**
     * Toma las 3 partes de la aceleración, la primera parte calculada con acel1, la segunda
     * calculada con acel2 y el denominador que es la multiplicación de las densidades de las
     * partículas.
     *
     * @param parte1 Las 3 coordenadas de la primera componente de la transormación de la
     *               aceleración.
     * @param parte2 Las 3 coordenadas de la segunda componente de la transormación de la
     *               aceleración.
     * @param denom Multiplicación de densidades de las particulas que están interaccionando entre
     *              si.
     *
     * @return Las 3 coordenadas de las aceleración que se le tiene que sumar a las dos partículas
     *         que están interactuando entre si.
     */
    constexpr static Vector3d<double> transferencia_aceleracion(Vector3d<double> & parte1,
                                                                Vector3d<double> const & parte2,
                                                                double const & denom) {
      parte1 += parte2;
      parte1 /= denom;
      return parte1;
    };

    /**
     * Función que dada un delta_x, la indicación de si el bloque está en el inicio, también
     * conocido como que la coordenada en x del bloque es 0, o si es la última, en estee caso
     * representada con un -1, calcula la aceleración que se le ha de sumar a las aceleraciones de
     * las particulas que están interactuando.
     *
     * @param bloque Valor 0 o -1 que indica si el bloque está al principio o al final de la malla.
     * @param delta_x Valor de la diferencia de posiciones entre las partículas.
     * @param velocidad Valor de la velocidad de la partícula.
     *
     * @return Cálculo de la diferencia de la aceleración que se le sumará a la aceleración de la
     *         partícula.
     */
    constexpr static double colisiones_limite_eje_x(int bloque, double const & delta_x,
                                                    Vector3d<double> const & velocidad) {
      if (bloque == 0) { return (s_c * delta_x - d_v * velocidad.x); }
      return -(s_c * delta_x + d_v * velocidad.x);
    };

    /**
     * Función que dada un delta_y, la indicación de si el bloque está en el inicio, también
     * conocido como que la coordenada en y del bloque es 0, o si es la última, en estee caso
     * representada con un -1, calcula la aceleración que se le ha de sumar a las aceleraciones de
     * las particulas que están interactuando.
     *
     * @param bloque Valor 0 o -1 que indica si el bloque está al principio o al final de la malla.
     * @param delta_y Valor de la diferencia de posiciones entre las partículas.
     * @param velocidad Valor de la velocidad de la partícula.
     *
     * @return Cálculo de la diferencia de la aceleración que se le sumará a la aceleración de la
     *         partícula.
     */
    constexpr static double colisiones_limite_eje_y(int bloque, double const & delta_y,
                                                    Vector3d<double> const & velocidad) {
      if (bloque == 0) { return (s_c * delta_y - d_v * velocidad.y); }
      return -(s_c * delta_y + d_v * velocidad.y);
    };

    /**
     * Función que dada un delta_z, la indicación de si el bloque está en el inicio, también
     * conocido como que la coordenada en z del bloque es 0, o si es la última, en estee caso
     * representada con un -1, calcula la aceleración que se le ha de sumar a las aceleraciones de
     * las particulas que están interactuando.
     *
     * @param bloque Valor 0 o -1 que indica si el bloque está al principio o al final de la malla.
     * @param delta_z Valor de la diferencia de posiciones entre las partículas.
     * @param velocidad Valor de la velocidad de la partícula.
     *
     * @return Cálculo de la diferencia de la aceleración que se le sumará a la aceleración de la
     *         partícula.
     */
    constexpr static double colisiones_limite_eje_z(int bloque, double const & delta_z,
                                                    Vector3d<double> const & velocidad) {
      if (bloque == 0) { return (s_c * delta_z - d_v * velocidad.z); }
      return -(s_c * delta_z + d_v * velocidad.z);
    };

    /**
     * Función que devuelve la nueva posición de una particula, dada la posición, el gradiente de la
     * velocidad y la aceleración de esa partícula.
     *
     * @param posicion Vector3D con las 3 coordenadas de la posición de la partícula.
     * @param gradiente Vector3D con las 3 coordenadas del gradiente de la partícula.
     * @param aceleracion Vector3D con las 3 coordenadas de la aceleración de la partícula.
     *
     * @return Devuelve el vector3D, con las 3 coordenadas de la posición de la partícula.
     */
    constexpr static Vector3d<double> actualizar_posicion(Vector3d<double> const & posicion,
                                                          Vector3d<double> const & gradiente,
                                                          Vector3d<double> const & aceleracion) {
      return posicion + (gradiente * delta_t) + (aceleracion * delta_t * delta_t);
    };

    /**
     * Función que devuelve la nueva velocidad de una particula, dado el gradiente velocidad y la
     * aceleración de esa partícula.
     *
     * @param gradiente Vector3D con las 3 coordenadas del gradiente.
     * @param aceleracion Vector3D con las 3 coordenadas de la aceleración.
     *
     * @return Devuelve un Vector3d con la nueva aceleración.
     */
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
