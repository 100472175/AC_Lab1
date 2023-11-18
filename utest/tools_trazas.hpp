#ifndef FLUID_TOOLS_TRAZAS_HPP
#define FLUID_TOOLS_TRAZAS_HPP

#include "../sim/simulacion.hpp"
#include "../sim/vector_3d.hpp"

#include <fstream>
#include <string>

int load_trz(std::string const & path, Simulacion & sim);

int write_trz(std::string const & path, Simulacion & sim);

bool compareFiles(std::string const & p1, std::string const & p2);
bool compareSims(Simulacion const & real, Simulacion const & expect, double tolerancia);

#endif  // FLUID_TOOLS_TRAZAS_HPP
