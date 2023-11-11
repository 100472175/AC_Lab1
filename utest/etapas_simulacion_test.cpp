//
// Created by adrian on 11/10/23.
//

#include "../sim/simulacion.hpp"
#include "../sim/progargs.hpp"
#include "tools_trazas.hpp"
#include <gtest/gtest.h>

  class EtapasTest : public testing::Test {
    public:
      void SetUp() override { x = 1; }

      int x;
  };

  TEST_F(EtapasTest, Poblar_malla) {
    Progargs progargs             = Progargs{};
    std::vector<std::string> args = {"0", "../../small.fld", "../out_test.fld"};
    int const validar_progargs = progargs.asignar_valores(args);
    EXPECT_EQ(validar_progargs,0);
    Malla malla{};
    Calculadora calc{};
    progargs.read_head(malla, calc);
    calc.inicializar_calculadora();
    malla.inicializar_malla(calc.num_bloques_por_eje());
    Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
    progargs.read_body(simulacion);

    simulacion.poblar_malla();
    write_trz("salida_poblar_malla", simulacion);
    EXPECT_EQ(compareFiles("../../traza/small/repos-base-1.trz", "salida_poblar_malla"), true);
  }

  TEST_F(EtapasTest, Colisiones_particulas_densidad){
  Progargs progargs = Progargs{};
  std::vector<std::string> args = {"0", "../../small.fld", "../out_test.fld"};
  progargs.asignar_valores(args);
  Malla malla{};
  Calculadora calc{};
  progargs.read_head(malla,calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  progargs.read_body(simulacion);
  load_trz("../../traza/small/repos-base-1.trz",simulacion);
  simulacion.colisiones_particulas_densidad();
  write_trz("salida_colisiones_particulas_densidad",simulacion);
  EXPECT_EQ(compareFiles("../../traza/small/denstransf-base-1.trz", "salida_colisiones_particulas_densidad"), true);

  }
  TEST_F(EtapasTest, Colisiones_particulas_aceleracion){

  }
  TEST_F(EtapasTest, Colisiones_particulas_limite){

  }
  TEST_F(EtapasTest, Movimiento_particulas){

  }
  TEST_F(EtapasTest, Rebote_particulas_limite){

  }
  TEST_F(EtapasTest, Reposicionamiento){

  }