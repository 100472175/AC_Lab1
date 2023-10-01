//
// Created by paula on 29/09/23.
//

#ifndef FLUID_PROGARGS_HPP
#define FLUID_PROGARGS_HPP

#include "vector_3d.hpp"

#include <iostream>

namespace Sim {

  int my_is_digit(std::string const &);

  int validate_arguments(int, char **);

  Vector3d_int fuera_de_rango(Vector3d_int);

}  // namespace Sim
#endif  // FLUID_PROGARGS_HPP
