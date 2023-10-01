//
// Created by paula on 29/09/23.
//

#ifndef FLUID_PROGARGS_HPP
#define FLUID_PROGARGS_HPP

#include <iostream>
#include "vector_3d.hpp"

namespace Sim {

  int my_is_digit(const std::string&);

  int validate_arguments(int , char**);

  Vector3d_int fuera_de_rango(Vector3d_int);

}
#endif  // FLUID_PROGARGS_HPP
