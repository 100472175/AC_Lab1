
#include "../sim/progargs.hpp"
#include "tools_trazas.hpp"

#include <algorithm>
#include <gtest/gtest.h>
constexpr double tolerance = 1e-12;

class EtapasTest : public testing::Test {
    void SetUp() override {
      std::vector<std::string> const args = {"1", "../../in/small.fld", "../../out_test.fld"};
      progargs.asignar_valores(args);
      progargs2.asignar_valores(args);
      progargs.read_head(malla, calc);
      progargs2.read_head(malla2, calc2);
      calc.inicializar_calculadora();
      malla.inicializar_malla(calc.num_bloques_por_eje());
    }

  public:
    Progargs progargs  = Progargs{};
    Progargs progargs2 = Progargs{};
    Malla malla{};
    Calculadora calc{};
    Malla malla2{};
    Calculadora calc2{};
};

TEST_F(EtapasTest, Poblar_malla) {
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs2.read_body(simulacion_prueba);
  simulacion.malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) {
    simulacion.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
  }
  simulacion_prueba.malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) {
    simulacion_prueba.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j,
                                              malla.bloques[i].k);
  }
  simulacion.poblar_malla();
  load_trz("../../trz/small/repos-base-1.trz", simulacion_prueba);
  for (int i = 0; i < simulacion.malla.tamano; i++) {
    std::sort(simulacion.malla.bloques[i].particulas.begin(),
              simulacion.malla.bloques[i].particulas.end());
  }
  for (int i = 0; i < simulacion_prueba.malla.tamano; i++) {
    std::sort(simulacion_prueba.malla.bloques[i].particulas.begin(),
              simulacion_prueba.malla.bloques[i].particulas.end());
  }
  EXPECT_EQ(compareSims(simulacion, simulacion_prueba, tolerance), true);
}

TEST_F(EtapasTest, Colisiones_particulas_densidad) {
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs2.read_body(simulacion_prueba);
  simulacion.malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) {
    simulacion.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
  }
  load_trz("../../trz/small/repos-base-1.trz", simulacion);
  load_trz("../../trz/small/denstransf-base-1.trz", simulacion_prueba);
  simulacion.colisiones_particulas_densidad();
  for (int i = 0; i < simulacion.malla.tamano; i++) {
    std::sort(simulacion.malla.bloques[i].particulas.begin(),
              simulacion.malla.bloques[i].particulas.end());
  }
  for (int i = 0; i < simulacion_prueba.malla.tamano; i++) {
    std::sort(simulacion_prueba.malla.bloques[i].particulas.begin(),
              simulacion_prueba.malla.bloques[i].particulas.end());
  }
  EXPECT_EQ(compareSims(simulacion, simulacion_prueba, tolerance), true);
}

TEST_F(EtapasTest, Colisiones_particulas_aceleracion) {
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs2.read_body(simulacion_prueba);
  simulacion.malla.crear_bloques();
  for (int i = 0; i < malla.tamano; i++) {
    simulacion.malla.bloques_contiguos(malla.bloques[i].i, malla.bloques[i].j, malla.bloques[i].k);
  }
  load_trz("../../trz/small/denstransf-base-1.trz", simulacion);
  load_trz("../../trz/small/acctransf-base-1.trz", simulacion_prueba);
  simulacion.colisiones_particulas_aceleracion();
  for (int i = 0; i < simulacion.malla.tamano; i++) {
    std::sort(simulacion.malla.bloques[i].particulas.begin(),
              simulacion.malla.bloques[i].particulas.end());
  }
  for (int i = 0; i < simulacion_prueba.malla.tamano; i++) {
    std::sort(simulacion_prueba.malla.bloques[i].particulas.begin(),
              simulacion_prueba.malla.bloques[i].particulas.end());
  }
  EXPECT_EQ(compareSims(simulacion, simulacion_prueba, tolerance), true);
}

TEST_F(EtapasTest, Colisiones_particulas_limite) {
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs2.read_body(simulacion_prueba);
  load_trz("../../trz/small/acctransf-base-1.trz", simulacion);
  load_trz("../../trz/small/partcol-base-1.trz", simulacion_prueba);
  simulacion.colision_particula_limite();
  for (int i = 0; i < simulacion.malla.tamano; i++) {
    std::sort(simulacion.malla.bloques[i].particulas.begin(),
              simulacion.malla.bloques[i].particulas.end());
  }
  for (int i = 0; i < simulacion_prueba.malla.tamano; i++) {
    std::sort(simulacion_prueba.malla.bloques[i].particulas.begin(),
              simulacion_prueba.malla.bloques[i].particulas.end());
  }
  EXPECT_EQ(compareSims(simulacion, simulacion_prueba, tolerance), true);
}

TEST_F(EtapasTest, Movimiento_particulas) {
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs2.read_body(simulacion_prueba);
  load_trz("../../trz/small/partcol-base-1.trz", simulacion);
  load_trz("../../trz/small/motion-base-1.trz", simulacion_prueba);
  simulacion.movimiento_particulas();
  for (int i = 0; i < simulacion.malla.tamano; i++) {
    std::sort(simulacion.malla.bloques[i].particulas.begin(),
              simulacion.malla.bloques[i].particulas.end());
  }
  for (int i = 0; i < simulacion_prueba.malla.tamano; i++) {
    std::sort(simulacion_prueba.malla.bloques[i].particulas.begin(),
              simulacion_prueba.malla.bloques[i].particulas.end());
  }
  EXPECT_EQ(compareSims(simulacion, simulacion_prueba, tolerance), true);
}

TEST_F(EtapasTest, Rebote_particulas_limite) {
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs2.read_body(simulacion_prueba);
  load_trz("../../trz/small/motion-base-1.trz", simulacion);
  load_trz("../../trz/small/boundint-base-1.trz", simulacion_prueba);
  simulacion.rebote_particula_limite();
  for (int i = 0; i < simulacion.malla.tamano; i++) {
    std::sort(simulacion.malla.bloques[i].particulas.begin(),
              simulacion.malla.bloques[i].particulas.end());
  }
  for (int i = 0; i < simulacion_prueba.malla.tamano; i++) {
    std::sort(simulacion_prueba.malla.bloques[i].particulas.begin(),
              simulacion_prueba.malla.bloques[i].particulas.end());
  }
  EXPECT_EQ(compareSims(simulacion, simulacion_prueba, tolerance), true);
}

TEST_F(EtapasTest, Reposicionamiento) {
  Simulacion simulacion(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  Simulacion simulacion_prueba(progargs.getter_num_iteraciones(), calc.num_particulas, calc, malla);
  simulacion.particulas.reserve_space(calc.num_particulas);
  simulacion_prueba.particulas.reserve_space(calc.num_particulas);
  progargs.read_body(simulacion);
  progargs2.read_body(simulacion_prueba);
  load_trz("../../trz/small/boundint-base-1.trz", simulacion);
  load_trz("../../trz/small/repos-base-2.trz", simulacion_prueba);
  simulacion.reposicionamiento();
  for (int i = 0; i < simulacion.malla.tamano; i++) {
    std::sort(simulacion.malla.bloques[i].particulas.begin(),
              simulacion.malla.bloques[i].particulas.end());
  }
  for (int i = 0; i < simulacion_prueba.malla.tamano; i++) {
    std::sort(simulacion_prueba.malla.bloques[i].particulas.begin(),
              simulacion_prueba.malla.bloques[i].particulas.end());
  }
  EXPECT_EQ(compareSims(simulacion, simulacion_prueba, tolerance), true);
}