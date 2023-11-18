//
// Created by adrian on 11/11/23.
//

#ifndef FLUID_TOOLS_TRAZAS_HPP
#define FLUID_TOOLS_TRAZAS_HPP

#include "../sim/simulacion.hpp"
#include "../sim/vector_3d.hpp"

#include <fstream>
#include <string>


int load_trz(const std::string& path, Simulacion & sim);

int write_trz(const std::string& path, Simulacion & sim);

bool compareFiles(const std::string& p1, const std::string& p2);
bool compareSims(const Simulacion& real, const Simulacion& expect, double tolerancia);

#endif  // FLUID_TOOLS_TRAZAS_HPP

