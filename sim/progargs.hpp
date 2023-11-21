#ifndef FLUID_PROGARGS_HPP
#define FLUID_PROGARGS_HPP

#include "calculadora.hpp"
#include "malla.hpp"
#include "simulacion.hpp"
#include "vector_3d.hpp"

#include <fstream>
#include <iostream>
#include <vector>

/**
 * Clase encargada de la lectura, escritura y validación de parámetros de entrada.
 */
class Progargs {
  private:
    int numero_iteraciones{};       // Numero de iteraciones de la simulacion
    std::ifstream archivo_entrada;  // Fichero de entrada con los datos de las particulas
    std::ofstream archivo_salida;   // Fichero de salida con los nuevos valores de particulas

  public:
    /**
     *
     * Función encargada de devolver el número de iteraciones.
     */
    int getter_num_iteraciones() const;

    /**
     * Asignar valores comprueba que el número y valor de los argumentos del programa son correctos,
     * y de ser así inicializa los valores de la clase progargs.
     *
     * @param args Vector que incluye los argumentos del programa excluyendo el path al propio
     *             programa. Debería tener longitud 3.
     *
     * @return La función devuelve 0 en caso de que los argumentos sean correctos, y códigos de
     *         error dependiendo del fallo en el resto de los casos.
     */
    int asignar_valores(std::vector<std::string> const & args);

    /**
     * Función encargada de leer la cabecera del fichero de entrada y guardar los datos obtenidos,
     * el número de particulas y particulas por metro, en la calculadora. Además, con estos datos le
     * asigna a la malla su tamaño.
     *
     * @param malla La instancia de la malla de la simulación.
     * @param calculadora La instancia de la calculadora utilizada en la simulación.
     *
     * @return Devuelve un código de error en caso de que el valor del número de particulas sea 0
     *         menos.
     */
    int read_head(Malla & malla, Calculadora & calculadora);

    /**
     * Lee el resto del fichero de entrada, guarda los datos de posición, velocidad y gradiente en
     * cada particula, y comprueba que el número especificado en la cabecera es el mismo que las
     * particulas que hay en el fichero. En caso de ser menor se detecta en la función, para el
     * resto de casos se llama a la función read_till_end.
     *
     * @param simulacion Instancia de la simulación
     *
     * @return Devuelve un codigo de error si el número de particulas es menor al especificado, en
     *         otro caso devuelve el valor de retorno de la funcion read_till_end.
     */
    int read_body(Simulacion & simulacion);

    /**
     * Función encargada de comprobar que el archivo de entrada no tiene más de las particulas
     * especificadas en la cabecera. Recibe el fichero con todas las particulas especificadas leidas
     * y comprueba si existen datos sin leer dentro del fichero. Cuenta estas particulas extra para
     * los datos de salida de error.
     *
     * @param num_particulas Numero de particulas de la simulación especificadas por la cabecera
     * @param leidas Contador de particulas que han sido hasta el momento.
     *
     * @return Devuelve un código de error que incluye el número correcto de particulas y el número
     *         leido en caso de error.
     */
    int read_till_end(int num_particulas, int leidas);

    /**
     * Escribe en el fichero de salida todos los datos de particulas después de la simulación.
     *
     * @param ppm Particulas por metro necesarias en la cabecera.
     * @param simulacion Instancia de la simulación que contiene los datos a escribir.
     */
    void write_file(double ppm, Simulacion & simulacion);

    /**
     * Función que comprueba que el parametro de numero de iteraciones es un numero entero positivo.
     *
     * @param string_to_try String que se va a comprobar si es un número entero.
     *
     * @return Devuelve el número en caso de ser correcto, y distintos errores dependiendo del
     *         problema encontrado, ya sea no ser un número o ser negativo.
     */
    static int my_is_digit(std::string const & string_to_try);

    /**
     * Función que comprueba que se pueda abrir bien el archivo de entrada y crea el objeto
     * instream.
     *
     * @param argumento_entrada Argumento de entrada del programa correspondiente con el fichero de
     *                          entrada.
     *
     * @return En caso de error, devuelve un código y mensaje especificando el problema.
     */
    int valida_entrada(std::string const & argumento_entrada);

    /**
     * Función que comprueba que el archivo de salida se pueda abrir correctamente, y crea el objeto
     * ofstream
     *
     * @param argumento_salida Argumento del programa con el path al nuevo archivo de salida.
     *
     * @return Devuelve un código de error en caso de haber un problema.
     */
    int valida_salida(std::string const & argumento_salida);
};

#endif  // FLUID_PROGARGS_HPP
