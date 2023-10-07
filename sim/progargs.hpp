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

namespace Sim {

  class Progargs {
    private:
      int numero_iteraciones;
      std::string archivo_entrada;
      std::string archivo_salida;
      std::ifstream input_file;

    public:
      Progargs(std::vector<std::string> const & args);

      int read_head(Malla & malla, Calculadora & calculadora);

      int read_body(Simulacion & simulacion);

      int write_file(Simulacion & simulacion);

      static int my_is_digit(std::string const &);

      //int validate_arguments(int, char **);

      static Vector3d_int fuera_de_rango(Vector3d_int);
  };


}  // namespace Sim
#endif  // FLUID_PROGARGS_HPP
