
#include "../sim/progargs.hpp"
#include "../utest/tools_trazas.hpp"

#include <gtest/gtest.h>
#include <iostream>
#include <span>

bool compareFiles(std::string const & p1, std::string const & p2) {
  std::ifstream f_1(p1, std::ifstream::binary);
  std::ifstream f_2(p2, std::ifstream::binary);

  if (f_1.fail() || f_2.fail()) {
    return false;  // file problem
  }
  f_1.seekg(0, std::ifstream::end);
  f_2.seekg(0, std::ifstream::end);
  size_t const lengh1 = f_1.tellg();
  size_t const lengh2 = f_2.tellg();
  std::cout << lengh1 << " " << lengh2 << "\n";
  if (lengh1 != lengh2) {
    std::cout << "size difference\n";
    return false;
  }

  f_1.seekg(0, std::ifstream::beg);
  f_2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f_1.rdbuf()), std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f_2.rdbuf()));
}

TEST(FunctionalTest, primera_iteracion) {
  std::vector<std::string> const argumentos = {"1", "../../small.fld", "../../final.fld"};
  Progargs nuestros_args{};
  nuestros_args.asignar_valores(argumentos);

  Malla malla{};
  Calculadora calc{};
  nuestros_args.read_head(malla, calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(nuestros_args.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  nuestros_args.read_body(simulacion);

  simulacion.iterador();

  nuestros_args.write_file(calc.ppm, simulacion);
  ASSERT_EQ(compareFiles("../../final.fld", "../../out/small-1.fld"), true);
}

TEST(FunctionalTest, segunda_iteracion) {
  std::vector<std::string> const argumentos = {"2", "../../small.fld", "../../final.fld"};
  Progargs nuestros_args{};
  nuestros_args.asignar_valores(argumentos);

  Malla malla{};
  Calculadora calc{};
  nuestros_args.read_head(malla, calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(nuestros_args.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  nuestros_args.read_body(simulacion);

  simulacion.iterador();

  nuestros_args.write_file(calc.ppm, simulacion);
  ASSERT_EQ(compareFiles("../../final.fld", "../../out/small-2.fld"), true);
}

TEST(FunctionalTest, tercera_iteracion) {
  std::vector<std::string> const argumentos = {"3", "../../small.fld", "../../final.fld"};
  Progargs nuestros_args{};
  nuestros_args.asignar_valores(argumentos);

  Malla malla{};
  Calculadora calc{};
  nuestros_args.read_head(malla, calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(nuestros_args.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  nuestros_args.read_body(simulacion);

  simulacion.iterador();

  nuestros_args.write_file(calc.ppm, simulacion);
  ASSERT_EQ(compareFiles("../../final.fld", "../../out/small-3.fld"), true);
}

TEST(FunctionalTest, cuarta_iteracion) {
  std::vector<std::string> const argumentos = {"4", "../../small.fld", "../../final.fld"};
  Progargs nuestros_args{};
  nuestros_args.asignar_valores(argumentos);

  Malla malla{};
  Calculadora calc{};
  nuestros_args.read_head(malla, calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(nuestros_args.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  nuestros_args.read_body(simulacion);

  simulacion.iterador();

  nuestros_args.write_file(calc.ppm, simulacion);
  ASSERT_EQ(compareFiles("../../final.fld", "../../out/small-4.fld"), true);
}

TEST(FunctionalTest, quinta_iteracion) {
  std::vector<std::string> const argumentos = {"5", "../../small.fld", "../../final.fld"};
  Progargs nuestros_args{};
  nuestros_args.asignar_valores(argumentos);

  Malla malla{};
  Calculadora calc{};
  nuestros_args.read_head(malla, calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(nuestros_args.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  nuestros_args.read_body(simulacion);

  simulacion.iterador();

  nuestros_args.write_file(calc.ppm, simulacion);
  ASSERT_EQ(compareFiles("../../final.fld", "../../out/small-5.fld"), true);
}

TEST(FunctionalTest, no_iteracion) {
  std::vector<std::string> const argumentos = {"0", "../../small.fld", "../../final.fld"};
  Progargs nuestros_args{};
  nuestros_args.asignar_valores(argumentos);

  Malla malla{};
  Calculadora calc{};
  nuestros_args.read_head(malla, calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(nuestros_args.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  nuestros_args.read_body(simulacion);

  simulacion.iterador();

  nuestros_args.write_file(calc.ppm, simulacion);
  ASSERT_EQ(compareFiles("../../final.fld", "../../small.fld"), true);
}