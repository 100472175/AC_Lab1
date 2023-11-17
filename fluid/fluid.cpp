//
// Created by paula on 27/09/23.
//
#include "../sim/calculadora.hpp"
#include "../sim/malla.hpp"
#include "../sim/progargs.hpp"
#include "../sim/simulacion.hpp"

#include <cmath>
#include <span>

int main(int argc, char ** argv) {
  std::span const args_span(argv, static_cast<std::size_t>(argc));
  std::vector<std::string> const argumentos(args_span.begin() + 1, args_span.end());

  Progargs nuestros_args{};
  int const validar_progargs = nuestros_args.asignar_valores(argumentos);
  if (validar_progargs != 0 ){return validar_progargs;}

  Malla malla{};
  Calculadora calc{};
  nuestros_args.read_head(malla, calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(nuestros_args.getter_num_iteraciones(),calc.num_particulas,calc,malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  nuestros_args.read_body(simulacion);
  simulacion.print_simulation_parameters();

  simulacion.iterador();
  nuestros_args.write_file(calc.ppm,simulacion);
  return 0;
}
