//
// Created by paula on 29/09/23.
//

#ifndef FLUID_PROGARGS_HPP
#define FLUID_PROGARGS_HPP

#include "vector_3d.hpp"
#include "calculadora.hpp"
#include "malla.hpp"
#include "simulacion.hpp"

#include <iostream>
#include <vector>
#include <fstream>


  class Progargs {
    private:
      int numero_iteraciones;
      std::ifstream archivo_entrada;
      std::ofstream  archivo_salida;
      //std::ifstream input_file;

    public:
      Progargs(std::vector<std::string> const & args);

      int read_head(Malla & malla, Calculadora & calculadora);

      int read_body(Simulacion & simulacion);

      int write_file(Simulacion & simulacion);

      static int my_is_digit(std::string const &);

      //int validate_arguments(int, char **);

      static Vector3d<int> fuera_de_rango(Vector3d<int>);
      std::ifstream valida_entrada(std::string const & argumento_entrada);
      std::ifstream valida_fichero(std::string const & fichero_a_probar, bool tipo);
      std::ofstream valida_salida(std::string const & argumento_salida);
  };


 // namespace Sim
#endif  // FLUID_PROGARGS_HPP
