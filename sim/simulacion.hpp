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

constexpr double const dist_max_a_limite{1e-10}; // distancia máxima a uno de los ejes

/**
 * Abstracción de la simulación, encargada de realizar todas las etapas descritas en el enunciado.
 */
class Simulacion {
  public:
    int num_iteraciones; // número de iteraciones
    int num_particulas; // número de particulas
    Particulas particulas; // conjunto de todas las partículas
    Malla malla; // malla para la ejecución
    Calculadora calc; // módulo de cálculos
    /**
     * Constructor de simulación
     *
     * @param n_i número de iteraciones
     * @param n_p número de partículas
     * @param calculadora módulo de cálculos inicializado
     * @param m malla
     */
    Simulacion(int n_i, int n_p, Calculadora calculadora, Malla m) : num_iteraciones(n_i), num_particulas(n_p) ,malla(std::move(m)), calc(calculadora){}

    /**
     * bucle principal de la simulación
     */
    void iterador();

    /**
     * Una única ejecución de todas las etapas de la simulación
     */
    void iteracion();

    /**
     * Llena la malla de partículas, cada una en su bloque correspondiente. Sólo se ejecuta una vez.
     */
    void poblar_malla();

    /**
     * Primera fase de la simulación, coloca todas las partículas en el bloque apropiado.
     */
    void reposicionamiento();

    /**
     * Segunda fase de la siulación, procesa la colisión entre partículas.
     */
    void colisiones_particulas();

    /**
     * Tercera fase de la simulación, procesa la colisión de partículas con los límites.
     */
    void colision_particula_limite();

    /**
     * Subdivisión de la función colision_particulas_limite(). Especificación para el eje x.
     * @param indice ínidce de la partícula
     * @param bloque indica si el bloque es el primero o el último del eje
     */
    void colision_particula_limite_x(int indice, int bloque);

    /**
     * Subdivisión de la función colision_particulas_limite(). Especificación para el eje y.
     * @param indice ínidce de la partícula
     * @param bloque indica si el bloque es el primero o el último del eje
     */
    void colision_particula_limite_y(int indice, int bloque);

    /**
     * Subdivisión de la función colision_particulas_limite(). Especificación para el eje y.
     * @param indice ínidce de la partícula
     * @param bloque indica si el bloque es el primero o el último del eje
     */
    void colision_particula_limite_z(int indice, int bloque);

    /**
     * Procesa el rebote de las partículas con los límites.
     */
    void rebote_particula_limite();

    /**
     * Subdivisión de la función rebote_particula_limite(). Especificación para el eje x.
     * @param particulas
     * @param bloque
     */
    void rebote_particula_limite_x(std::vector<int> & particulas, int bloque);

    /**
     * Subdivisión de la función rebote_particula_limite(). Especificación para el eje y.
     * @param particulas
     * @param bloque
     */
    void rebote_particula_limite_y(std::vector<int> & particulas, int bloque);

    /**
     * Subdivisión de la función rebote_particula_limite(). Especificación para el eje z.
     * @param particulas
     * @param bloque
     */
    void rebote_particula_limite_z(std::vector<int> & particulas, int bloque);
    void movimiento_particulas();
    void print_simulation_parameters() const;

    /**
     * subdivisión de la función colisiones_particulas(). Procesa la variación de aceleración derivada de una colisión.
     */
    void colisiones_particulas_aceleracion();

    /**
     * subdivisión de la función colisiones_particulas(). Procesa la variación de densidad derivada de una colisión.
     */
    void colisiones_particulas_densidad();

    /**
     * Añade partículas a la malla con los datos iniciales.
     *
     * @param index id de la partícula
     * @param pos vector de posicion
     * @param hv vector de gradiente
     * @param v vector de velocidad
     */
    void add_particulas(int index, Vector3d<float> & pos, Vector3d<float> & hv,
                        Vector3d<float> & v);
};

#endif  // FLUID_SIMULACION_HPP
