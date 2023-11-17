//
// Created by cesar on 20/10/23.
//

#include "../sim/calculadora.hpp"

#include "gtest/gtest.h"
#include <cmath>
#include <numbers>

constexpr int num_part     = 4800;
constexpr double ppm       = 204.0;
constexpr double ppm2      = 2.0;
constexpr double tolerance = 0.005;

class CalculadoraTest : public testing::Test {
  public:
    void SetUp() override {
      calculadora_init.num_particulas = 2;
      calculadora_init.ppm            = ppm2;

      calculadora.num_particulas = num_part;
      calculadora.ppm            = ppm;
      calculadora.inicializar_calculadora();
    }

    Calculadora calculadora_init{};
    Calculadora calculadora{};
};

TEST_F(CalculadoraTest, InicializarCalculadora) {
  calculadora_init.inicializar_calculadora();
  EXPECT_EQ(calculadora_init.suavizado, 1.695 / (double) 2);
  EXPECT_EQ(calculadora_init.masa, 1e3 / (double) 8);
}

TEST_F(CalculadoraTest, NumBloquesPorEje) {
  Vector3d<double> const expect(15.0, 21.0, 15.0);
  Vector3d<double> const result = calculadora.num_bloques_por_eje();
  EXPECT_EQ(result.x, expect.x);
  EXPECT_EQ(result.y, expect.y);
  EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, TamanioBloque) {
  Vector3d<double> const expect((0.065 + 0.065) / 15.0, (0.1 + 0.08) / 21.0,
                                (0.065 + 0.065) / 15.0);
  Vector3d<double> const result = calculadora.tamanio_bloque();
  EXPECT_EQ(result.x, expect.x);
  EXPECT_EQ(result.y, expect.y);
  EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, IndiceBloque) {
  Vector3d<double> const position(-0.0208688, -0.0606383, -0.0484482);
  Vector3d<int> const expect(5, 2, 1);
  Vector3d<int> const result = calculadora.indice_bloque(position);
  EXPECT_EQ(result.x, expect.x);
  EXPECT_EQ(result.y, expect.y);
  EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, DeltaDensidades) {
  double const dist_squere = 6.283185308;
  double const temp        = calculadora.suavizado * calculadora.suavizado - dist_squere;
  double expect            = pow(temp, 3);
  double result            = calculadora.delta_densidades(dist_squere);
  if (expect < result) {
    double const aux = expect;
    expect           = result;
    result           = aux;
  }
  double const error = (expect - result) / expect;
  EXPECT_LE(error, tolerance);
}

TEST_F(CalculadoraTest, TransformDensidad) {
  double const suavizado9 = pow(calculadora.suavizado, 9);
  double const dens       = 0.01570796327;
  double const cte        = 315 / (64 * std::numbers::pi);
  double expect           = calculadora.masa * ((dens + suavizado9) * cte / suavizado9);
  double result           = calculadora.transform_densidad(dens);
  if (expect < result) {
    double const aux = expect;
    expect           = result;
    result           = aux;
  }
  double const error = (expect - result) / expect;
  EXPECT_LE(error, tolerance);
}

TEST_F(CalculadoraTest, AceleracionPrimeraParte) {
  Vector3d<double> const posicion1(-0.0208688, -0.0606383, -0.0484482);
  Vector3d<double> const posicion2(-0.0484482, -0.0208688, -0.0606383);
  Vector3d<double> const diff = posicion1 - posicion2;

  double distancia = pow(posicion1.x - posicion2.x, 2) + pow(posicion1.y - posicion2.y, 2) +
                     pow(posicion1.z - posicion2.z, 2);
  distancia = sqrt(distancia);

  double const densidad1 = 0.12345689;
  double const densidad2 = 0.987654321;
  double const operador1 = (15 / (std::numbers::pi * pow(calculadora.suavizado, 6))) * 3 *
                           calculadora.masa * p_s * 0.5 *
                           pow(calculadora.suavizado - distancia, 2) / distancia;
  double const operador2 = densidad1 + densidad2 - (2 * 1e3);

  Vector3d<double> expect = diff * operador1 * operador2;
  Vector3d<double> result = calculadora.acel1(posicion1, posicion2, densidad1, densidad2);
  if (expect.x < result.x) {
    double const aux = expect.x;
    expect.x         = result.x;
    result.x         = aux;
  }
  if (expect.y < result.x) {
    double const aux = expect.y;
    expect.y         = result.y;
    result.y         = aux;
  }
  if (expect.z < result.x) {
    double const aux = expect.z;
    expect.z         = result.z;
    result.z         = aux;
  }
  double const error_x = (expect.x - result.x) / expect.x;
  double const error_y = (expect.y - result.y) / expect.y;
  double const error_z = (expect.z - result.z) / expect.z;

  EXPECT_LE(error_x, tolerance);
  EXPECT_LE(error_y, tolerance);
  EXPECT_LE(error_z, tolerance);
}

TEST_F(CalculadoraTest, AceleracionSegundaParte) {
  Vector3d<double> const vel1(-0.0208688, -0.0606383, -0.0484482);
  Vector3d<double> const vel2(-0.0484482, -0.0208688, -0.0606383);
  double const operador =
      45 / (std::numbers::pi * pow(calculadora.suavizado, 6)) * 0.4 * calculadora.masa;
  Vector3d<double> expect = (vel2 - vel1) * operador;
  Vector3d<double> result = calculadora.acel2(vel1, vel2);

  if (expect.x < result.x) {
    double const aux = expect.x;
    expect.x         = result.x;
    result.x         = aux;
  }
  if (expect.y < result.x) {
    double const aux = expect.y;
    expect.y         = result.y;
    result.y         = aux;
  }
  if (expect.z < result.x) {
    double const aux = expect.z;
    expect.z         = result.z;
    result.z         = aux;
  }
  double const error_x = (expect.x - result.x) / expect.x;
  double const error_y = (expect.y - result.y) / expect.y;
  double const error_z = (expect.z - result.z) / expect.z;

  EXPECT_LE(error_x, tolerance);
  EXPECT_LE(error_y, tolerance);
  EXPECT_LE(error_z, tolerance);
}

TEST_F(CalculadoraTest, TrasferenciaAceleracion) {
  const double primero = 3.5;
  const double segundo = 4.7;
  const double tercero = 3.141592;
  Vector3d<double> parte1(primero, segundo, tercero);
  Vector3d<double> const parte2(2.718, 6.7, 6.2830);
  double const denom = 5.0;
  Vector3d<double> const expect((parte1.x + parte2.x) / (double) denom,
                                (parte1.y + parte2.y) / (double) denom,
                                (parte1.z + parte2.z) / (double) denom);
  Vector3d<double> const result = Calculadora::transferencia_aceleracion(parte1, parte2, denom);
  EXPECT_EQ(result.x, expect.x);
  EXPECT_EQ(result.y, expect.y);
  EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeX_bloque0) {
  int const bloque     = 0;
  double const delta_x = 0.005;
  Vector3d<double> const vel(0.1, 0.2, 0.3);
  double const expect = 3e4 * delta_x - 128.0 * vel.x;
  double const result = Calculadora::colisiones_limite_eje_x(bloque, delta_x, vel);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeX_bloque1) {
  int const bloque     = 1;
  double const delta_x = 0.005;
  Vector3d<double> const vel(0.1, 0.2, 0.3);
  double const expect = 3e4 * delta_x + 128.0 * vel.x;
  double const result = Calculadora::colisiones_limite_eje_x(bloque, delta_x, vel);
  EXPECT_EQ(result, -expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeY_bloque0) {
  int const bloque     = 0;
  double const delta_y = 0.005;
  Vector3d<double> const vel(0.1, 0.2, 0.3);
  double const expect = 3e4 * delta_y - 128.0 * vel.y;
  double const result = Calculadora::colisiones_limite_eje_y(bloque, delta_y, vel);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeY_bloque1) {
  int const bloque     = 1;
  double const delta_y = 0.005;
  Vector3d<double> const vel(0.1, 0.2, 0.3);
  double const expect = 3e4 * delta_y + 128.0 * vel.y;
  double const result = Calculadora::colisiones_limite_eje_y(bloque, delta_y, vel);
  EXPECT_EQ(result, -expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeZ_bloque0) {
  int const bloque     = 0;
  double const delta_z = 0.005;
  Vector3d<double> const vel(0.1, 0.2, 0.3);
  double const expect = 3e4 * delta_z - 128.0 * vel.z;
  double const result = Calculadora::colisiones_limite_eje_z(bloque, delta_z, vel);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeZ_bloque1) {
  int const bloque     = 1;
  double const delta_z = 0.005;
  Vector3d<double> const vel(0.1, 0.2, 0.3);
  double const expect = 3e4 * delta_z + 128.0 * vel.z;
  double const result = Calculadora::colisiones_limite_eje_z(bloque, delta_z, vel);
  EXPECT_EQ(result, -expect);
}

TEST_F(CalculadoraTest, ActualizarPosicion) {
  Vector3d<double> const gradiente(0.1, 0.2, 0.3);
  Vector3d<double> const aceleracion(3.1, -4.0, 1.69);
  Vector3d<double> const expect = gradiente * 1e-3 + aceleracion * 1e-3 * 1e-3;
  Vector3d<double> const pos(0.0, 0.0, 0.0);
  Vector3d<double> const result = Calculadora::actualizar_posicion(pos, gradiente, aceleracion);
  EXPECT_EQ(result.x, expect.x);
  EXPECT_EQ(result.y, expect.y);
  EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, ActualizarVelocidad) {
  Vector3d<double> const aceleracion(3.1, -4.0, 1.69);
  Vector3d<double> const expect = aceleracion * 5e-4;
  Vector3d<double> const grad(0.0, 0.0, 0.0);

  Vector3d<double> const result = Calculadora::actualizar_velocidad(grad, aceleracion);
  EXPECT_EQ(result.x, expect.x);
  EXPECT_EQ(result.y, expect.y);
  EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, ActualizarGradiente) {
  Vector3d<double> const aceleracion(0.3141592654, 2.718, 1.61803398875);
  Vector3d<double> const expect = aceleracion * 1e-3;
  Vector3d<double> const grad(0.0, 0.0, 0.0);
  Vector3d<double> const result = Calculadora::actualizar_gradiente(grad, aceleracion);
  EXPECT_EQ(result.x, expect.x);
  EXPECT_EQ(result.y, expect.y);
  EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeX_bloque0) {
  int const bloque    = 0;
  double const d_x    = 3.141592654;
  double const expect = -0.065 - d_x;
  double const result = Calculadora::interacciones_limite_eje_x(d_x, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeX_bloque1) {
  int const bloque    = -1;
  double const d_x    = 3.141592654;
  double const expect = 0.065 + d_x;
  double const result = Calculadora::interacciones_limite_eje_x(d_x, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeX_bloque2) {
  int const bloque    = 2;
  double const d_x    = 3.141592654;
  double const expect = 0.0;
  double const result = Calculadora::interacciones_limite_eje_x(d_x, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeY_bloque0) {
  int const bloque    = 0;
  double const d_y    = 3.141592654;
  double const expect = -0.08 - d_y;
  double const result = Calculadora::interacciones_limite_eje_y(d_y, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeY_bloque1) {
  int const bloque    = -1;
  double const d_y    = 3.141592654;
  double const expect = 0.1 + d_y;
  double const result = Calculadora::interacciones_limite_eje_y(d_y, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeY_bloque2) {
  int const bloque    = 2;
  double const d_y    = 3.141592654;
  double const expect = 0.0;
  double const result = Calculadora::interacciones_limite_eje_y(d_y, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeZ_bloque0) {
  int const bloque    = 0;
  double const d_z    = 3.141592654;
  double const expect = -0.065 - d_z;
  double const result = Calculadora::interacciones_limite_eje_z(d_z, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeZ_bloque1) {
  int const bloque    = -1;
  double const d_z    = 3.141592654;
  double const expect = 0.065 + d_z;
  double const result = Calculadora::interacciones_limite_eje_z(d_z, bloque);
  EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeZ_bloque2) {
  int const bloque    = 2;
  double const d_z    = 3.141592654;
  double const expect = 0.0;
  double const result = Calculadora::interacciones_limite_eje_z(d_z, bloque);
  EXPECT_EQ(result, expect);
}