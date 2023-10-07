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

constexpr double const radio{1.695};              // Radio
constexpr double const dens_fluido{1e3};          // Densidad de fluido
constexpr double p_s{3.0};                        // Presión de rigidez
constexpr double s_c{128.0};                      // Collisión de rigidez
constexpr double const d_v{2e-3};                 // Amortiguamiento
constexpr double const viscosidad{0.4};           // Viscosidad
constexpr double const d_p{2e-4};                 // Tamaño de la partícula
constexpr double const delta_t{1e-3};             // Paso de tiempo
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


    Vector3d num_bloques_por_eje();

    Vector3d tamanio_bloque();

    Vector3d_int indice_bloque(Vector3d const & posicion);

    // 4.3.2
    // Inidiación de densidad y aceleraciones [pg. 8]
    void init_densidad_accel();

    int delta_densidades(int particula1, int particula2, std::vector<double> densidad,
                                      std::vector<Vector3d> posicion) const;


    double transform_densidad(int particula, std::vector<double> densidad) const;

    Vector3d trasnfer_accel_particulas_calculo(std::tuple<int, int> particula,
                                               std::vector<Vector3d> & posicion,
                                               std::vector<double> & densidad,
                                               std::vector<Vector3d> & velocidad);

    static void trasnfer_accel_particulas(int particula1, int particula2,
                                          std::vector<Vector3d> & aceleracion,
                                          Vector3d & delta_aceleracion);

    // 4.3.3
    void collisiones_limite_eje_x(int particula, std::vector<Vector3d> & posicion,
                                  std::vector<Vector3d> & velocidad,
                                  std::vector<Vector3d> & aceleracion);

    void collisiones_limite_eje_y(int particula, std::vector<Vector3d> & posicion,
                                  std::vector<Vector3d> & velocidad,
                                  std::vector<Vector3d> & aceleracion);

    void collisiones_limite_eje_z(int particula, std::vector<Vector3d> & posicion,
                                  std::vector<Vector3d> & velocidad,
                                  std::vector<Vector3d> & aceleracion);

    // 4.3.4
    void actualizar_posicion(int particula, std::vector<Vector3d> & posicion,
                             std::vector<Vector3d> & suavizado_vec,
                             std::vector<Vector3d> & aceleracion);

    void actualizar_velocidad(int particula, std::vector<Vector3d> & velocidad,
                              std::vector<Vector3d> & suavizado_vec,
                              std::vector<Vector3d> & aceleracion);

    void actualizar_gradiente(int particula, std::vector<Vector3d> & suavizado_vec,
                              std::vector<Vector3d> & aceleracion);

    void interacciones_limite_eje_x(int particula, std::vector<Vector3d> & posicion,
                                    std::vector<Vector3d> & velocidad,
                                    std::vector<Vector3d> & suavizado_vec);
    void interacciones_limite_eje_y(int particula, std::vector<Vector3d> & posicion,
                                    std::vector<Vector3d> & velocidad,
                                    std::vector<Vector3d> & suavizado_vec);
    void interacciones_limite_eje_z(int particula, std::vector<Vector3d> & posicion,
                                    std::vector<Vector3d> & velocidad,
                                    std::vector<Vector3d> & suavizado_vec);
};
#endif  // PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
