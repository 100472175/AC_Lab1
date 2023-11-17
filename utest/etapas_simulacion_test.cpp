//
// Created by adrian on 11/10/23.
//

#include "../sim/simulacion.hpp"
#include "../sim/progargs.hpp"
#include "tools_trazas.hpp"
#include <gtest/gtest.h>

  class EtapasTest : public testing::Test {
      void SetUp() override{
       std::vector<std::string> const args = {"0", "../../small.fld", "../../out_test.fld"};
       progargs.asignar_valores(args);
       progargs.read_head(malla,calc);
       calc.inicializar_calculadora();
       malla.inicializar_malla(calc.num_bloques_por_eje());

      }
    public:
      double const tolerance = 1e-4;
      Progargs progargs = Progargs{};
      Malla malla{};
      Calculadora calc{};
  };

  TEST_F(EtapasTest, Poblar_malla) {
    Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
    Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
    simulacion.particulas.reserve_space(calc.num_particulas);
    simulacion_prueba.particulas.reserve_space(calc.num_particulas);
    progargs.read_body(simulacion);
    progargs.read_body(simulacion_prueba);
    simulacion.malla.crear_bloques();
    for (int i = 0; i < malla.tamano; i++) {
      simulacion.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
    }
    simulacion_prueba.malla.crear_bloques();
    for (int i = 0; i < malla.tamano; i++) {
      simulacion_prueba.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
    }
    simulacion.poblar_malla();
    load_trz("../../traza/small/repos-base-1.trz",simulacion_prueba);
    std::cout << "Paso por aquí";
    EXPECT_EQ(compareSims(simulacion,simulacion_prueba,tolerance), true);
  }

  TEST_F(EtapasTest, Colisiones_particulas_densidad){
    std::vector<std::string> const args = {"0", "../../small.fld", "../out_test.fld"};
    progargs.asignar_valores(args);
    progargs.read_head(malla,calc);
    calc.inicializar_calculadora();
    malla.inicializar_malla(calc.num_bloques_por_eje());
    Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
    Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
    simulacion.particulas.reserve_space(calc.num_particulas);
    simulacion_prueba.particulas.reserve_space(calc.num_particulas);
    progargs.read_body(simulacion);
    progargs.read_body(simulacion_prueba);
    simulacion.malla.crear_bloques();
    for (int i = 0; i < malla.tamano; i++) {
      simulacion.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
    }
    load_trz("../../traza/small/repos-base-1.trz",simulacion);
    load_trz("../../traza/small/denstransf-base-1.trz",simulacion_prueba);
    simulacion.colisiones_particulas_densidad();
  EXPECT_EQ(compareSims(simulacion,simulacion_prueba,tolerance), true);
  }
  TEST_F(EtapasTest, Colisiones_particulas_aceleracion){
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs.read_body(simulacion_prueba);
  simulacion.malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) {
      simulacion.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
  }
  load_trz("../../traza/small/denstransf-base-1.trz",simulacion);
  load_trz("../../traza/small/acctransf-base-1.trz",simulacion_prueba);
  simulacion.colisiones_particulas_aceleracion();
  EXPECT_EQ(compareSims(simulacion,simulacion_prueba,tolerance), true);
  }
  TEST_F(EtapasTest, Colisiones_particulas_limite){

  Progargs progargs = Progargs{};
  std::vector<std::string> const args = {"0", "../../small.fld", "../out_test.fld"};
  progargs.asignar_valores(args);
  Malla malla{};
  Calculadora calc{};
  progargs.read_head(malla,calc);
  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  progargs.read_body(simulacion);
  simulacion.malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) {
      simulacion.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
  }
  load_trz("../../traza/small/acctransf-base-1.trz",simulacion);
  simulacion.colision_particula_limite();
  write_trz("salida_colisiones_particulas_limite",simulacion);
  EXPECT_EQ(compareFiles("../../traza/small/partcol-base-1.trz", "salida_colisiones_particulas_limite"), true);
  }
  TEST_F(EtapasTest, Movimiento_particulas){

  }
  TEST_F(EtapasTest, Rebote_particulas_limite){

  }
  TEST_F(EtapasTest, Reposicionamiento){

  }