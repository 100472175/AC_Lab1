#ifndef FLUID_SIMULACION_HPP
#define FLUID_SIMULACION_HPP

#include "calculadora.hpp"
#include "malla.hpp"
#include "particle.hpp"

#include <iostream>
#include <vector>

constexpr double const dist_max_a_limite{1e-10};  // Distancia máxima a uno de los ejes

/**
 * Abstracción de la simulación, encargada de realizar todas las etapas descritas en el enunciado.
 */
class Simulacion {
  public:
    int num_iteraciones;    // Número de iteraciones
    int num_particulas;     // Número de particulas
    Particulas particulas;  // Conjunto de todas las partículas
    Malla malla;            // Malla para la ejecución
    Calculadora calc;       // Módulo de cálculos

    /**
     * Constructor de simulación.
     *
     * @param n_i Número de iteraciones.
     * @param n_p Número de partículas.
     * @param calculadora Módulo de cálculos inicializado.
     * @param m Instancia de la malla utilizada en toda la simulación.
     */
    Simulacion(int n_i, int n_p, Calculadora calculadora, Malla m)
      : num_iteraciones(n_i), num_particulas(n_p), malla(std::move(m)), calc(calculadora) { }

    /**
     * Bucle principal de la simulación.
     */
    void iterador();

    /**
     * Una única ejecución de todas las etapas de la simulación.
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
     * Segunda fase de la simulación, procesa la colisión entre partículas.
     */
    void colisiones_particulas();

    /**
     * Subdivisión de la función colisiones_particulas(). Procesa la variación de aceleración
     * derivada de una colisión.
     */
    void colisiones_particulas_aceleracion();

    /**
     * Subdivisión de la función colisiones_particulas(). Procesa la variación de densidad derivada
     * de una colisión.
     */
    void colisiones_particulas_densidad();

    /**
     * Tercera fase de la simulación, procesa la colisión de partículas con los límites.
     */
    void colision_particula_limite();

    /**
     * Subdivisión de la función colision_particulas_limite(). Especificación para el eje x.
     *
     * @param indice Índice de la partícula.
     * @param bloque Indica si el bloque es el primero o el último del eje.
     */
    void colision_particula_limite_x(int indice, int bloque);

    /**
     * Subdivisión de la función colision_particulas_limite(). Especificación para el eje y.
     *
     * @param indice Índice de la partícula.
     * @param bloque Indica si el bloque es el primero o el último del eje.
     */
    void colision_particula_limite_y(int indice, int bloque);

    /**
     * Subdivisión de la función colision_particulas_limite(). Especificación para el eje y.
     *
     * @param indice Índice de la partícula.
     * @param bloque Indica si el bloque es el primero o el último del eje.
     */
    void colision_particula_limite_z(int indice, int bloque);

    /**
     * Cuarta fase de la simulación, encargada de actualizar la posición de cada particula
     * dependiendo de su aceleración y gradiente.
     */
    void movimiento_particulas();

    /**
     * Quinta fase de la simulación, encargada de que las particulas correspondientes modifiquen sus
     * parametros si están posicionadas cerca de los limites.
     */
    void rebote_particula_limite();

    /**
     * Subdivisión de la función rebote_particula_limite(). Especificación para el eje x.
     *
     * @param particulas Vector de particulas de la simulación.
     * @param bloque Indica si el bloque es el primero o el último del eje.
     */
    void rebote_particula_limite_x(std::vector<int> & particulas, int bloque);

    /**
     * Subdivisión de la función rebote_particula_limite(). Especificación para el eje y.
     *
     * @param particulas Vector de particulas de la simulación.
     * @param bloque Indica si el bloque es el primero o el último del eje.
     */
    void rebote_particula_limite_y(std::vector<int> & particulas, int bloque);

    /**
     * Subdivisión de la función rebote_particula_limite(). Especificación para el eje z.
     *
     * @param particulas Vector de particulas de la simulación.
     * @param bloque Indica si el bloque es el primero o el último del eje.
     */
    void rebote_particula_limite_z(std::vector<int> & particulas, int bloque);

    /**
     *  Función que imprime los parametros iniciales de la simulación; numero de particulas,
     * suavizado, masa, y parámetros de la malla.
     */
    void print_simulation_parameters() const;

    /**
     * Añade partículas a la malla con los datos iniciales.
     *
     * @param pos Vector de posicion.
     * @param hv Vector de gradiente.
     * @param v Vector de velocidad.
     */
    void add_particulas(Vector3d<float> & pos, Vector3d<float> & h_v, Vector3d<float> & vel);
};

#endif  // FLUID_SIMULACION_HPP
