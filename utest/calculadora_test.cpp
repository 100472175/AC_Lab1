//
// Created by cesar on 20/10/23.
//

#include "gtest/gtest.h"
#include "../sim/calculadora.hpp"

#include <cmath>
#include <numbers>

class CalculadoraTest : public testing::Test {
public:


    void SetUp() override {
        calculadora_init.num_particulas = 2;
        calculadora_init.ppm = 2.0;

        calculadora.num_particulas = 4800;
        calculadora.ppm = 204.0;
        calculadora.inicializar_calculadora();


    }

    Calculadora calculadora_init;
    Calculadora calculadora;
    double tolerance = 0.005;


};

TEST_F(CalculadoraTest, InicializarCalculadora) {
    calculadora_init.inicializar_calculadora();
    EXPECT_EQ(calculadora_init.suavizado, 1.695/(double)2);
    EXPECT_EQ(calculadora_init.masa, 1e3/(double)8);
}

TEST_F(CalculadoraTest, NumBloquesPorEje) {
    Vector3d<double> expect(15.0, 21.0, 15.0);
    Vector3d<double> result = calculadora.num_bloques_por_eje();
    EXPECT_EQ(result.x, expect.x);
    EXPECT_EQ(result.y, expect.y);
    EXPECT_EQ(result.z, expect.z);


}

TEST_F(CalculadoraTest, TamanioBloque) {
    Vector3d<double> expect((0.065 + 0.065)/15.0, (0.1 + 0.08)/21.0, (0.065 + 0.065)/15.0);
    Vector3d<double> result = calculadora.tamanio_bloque();
    EXPECT_EQ(result.x, expect.x);
    EXPECT_EQ(result.y, expect.y);
    EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, IndiceBloque) {
    Vector3d<double> position(-0.0208688, -0.0606383, -0.0484482);
    Vector3d<int> expect(5, 2, 1);
    Vector3d<int> result = calculadora.indice_bloque(position);
    EXPECT_EQ(result.x, expect.x);
    EXPECT_EQ(result.y, expect.y);
    EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, DeltaDensidades) {
    double dist_squere = 6.283185308;
    double temp = calculadora.suavizado*calculadora.suavizado - dist_squere;
    double expect = pow(temp, 3);
    double result = calculadora.delta_densidades(dist_squere);
    if (expect < result) {
        double aux = expect;
        expect = result; 
        result = aux;
    }
    double error = (expect - result)/expect;
    EXPECT_LE(error, tolerance);
}


TEST_F(CalculadoraTest, TransformDensidad) {
    double suavizado6 = calculadora.suavizado, suavizado9 = calculadora.suavizado;
    double dens = 0.01570796327;
    double cte = 315 / (64 * std::numbers::pi);
    suavizado6 = pow(suavizado6, 6);
    suavizado9 = pow(suavizado9, 9);
    double expect = calculadora.masa * ((dens + suavizado9) * cte/suavizado9);
    double result = calculadora.transform_densidad(dens);
    if (expect < result) {
        double aux = expect;
        expect = result; 
        result = aux;
    }
    double error = (expect - result)/expect;
    EXPECT_LE(error, tolerance);
}
/*
TEST(CalculadoraTest, AceleracionPrimeraParte) {

}

TEST(CalculadoraTest, AceleracionSegundaParte) {

}

TEST(CalculadoraTest, AceleracionTerceraParte) {

}*/

TEST_F(CalculadoraTest, TrasferenciaAceleracion) {
    Vector3d<double> parte1(3.5, 4.7, 3.141592);
    Vector3d<double> parte2(2.718, 6.7, 6.2830);
    double denom = 5.0;
    Vector3d<double> expect((parte1.x + parte2.x)/(double)denom, (parte1.y + parte2.y)/(double)denom, (parte1.z + parte2.z)/(double)denom);
    Vector3d<double> result = calculadora.transferencia_aceleracion(parte1, parte2, denom);
    EXPECT_EQ(result.x, expect.x);
    EXPECT_EQ(result.y, expect.y);
    EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeX_bloque0) {
    int bloque = 0;
    double const delta_x = 0.005;
    Vector3d<double> v(0.1, 0.2, 0.3);
    double expect = 3e4 * delta_x - 128.0 * v.x;
    double result = calculadora.colisiones_limite_eje_x(bloque, delta_x, v);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeX_bloque1) {
    int bloque = 1;
    double const delta_x = 0.005;
    Vector3d<double> v(0.1, 0.2, 0.3);
    double expect = 3e4 * delta_x + 128.0 * v.x;
    double result = calculadora.colisiones_limite_eje_x(bloque, delta_x, v);
    EXPECT_EQ(result, -expect);
}


TEST_F(CalculadoraTest, ColisionesLimiteEjeY_bloque0) {
    int bloque = 0;
    double const delta_y = 0.005;
    Vector3d<double> v(0.1, 0.2, 0.3);
    double expect = 3e4 * delta_y - 128.0 * v.y;
    double result = calculadora.colisiones_limite_eje_y(bloque, delta_y, v);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeY_bloque1) {
    int bloque = 1;
    double const delta_y = 0.005;
    Vector3d<double> v(0.1, 0.2, 0.3);
    double expect = 3e4 * delta_y + 128.0 * v.y;
    double result = calculadora.colisiones_limite_eje_y(bloque, delta_y, v);
    EXPECT_EQ(result, -expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeZ_bloque0) {
    int bloque = 0;
    double const delta_z = 0.005;
    Vector3d<double> v(0.1, 0.2, 0.3);
    double expect = 3e4 * delta_z - 128.0 * v.z;
    double result = calculadora.colisiones_limite_eje_z(bloque, delta_z, v);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, ColisionesLimiteEjeZ_bloque1) {
    int bloque = 1;
    double const delta_z = 0.005;
    Vector3d<double> v(0.1, 0.2, 0.3);
    double expect = 3e4 * delta_z + 128.0 * v.z;
    double result = calculadora.colisiones_limite_eje_z(bloque, delta_z, v);
    EXPECT_EQ(result, -expect);
}


TEST_F(CalculadoraTest, ActualizarPosicion) {
    Vector3d<double> gradiente(0.1, 0.2, 0.3);
    Vector3d<double> aceleracion(3.1, -4.0, 1.69);
    Vector3d<double> expect = gradiente * 1e-3 + aceleracion * 1e-3 * 1e-3;
    Vector3d<double> pos(0.0, 0.0, 0.0);
    Vector3d<double> result = calculadora.actualizar_posicion(pos, gradiente, aceleracion);
    EXPECT_EQ(result.x, expect.x);
    EXPECT_EQ(result.y, expect.y);
    EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, ActualizarVelocidad) {
    Vector3d<double> aceleracion(3.1, -4.0, 1.69);
    Vector3d<double> expect =  aceleracion * 5e-4;
    Vector3d<double> grad(0.0, 0.0, 0.0);

    Vector3d<double> result = calculadora.actualizar_velocidad(grad, aceleracion);
    EXPECT_EQ(result.x, expect.x);
    EXPECT_EQ(result.y, expect.y);
    EXPECT_EQ(result.z, expect.z);
}


TEST_F(CalculadoraTest, ActualizarGradiente) {
    Vector3d aceleracion(0.3141592654, 2.718, 1.61803398875);
    Vector3d<double> expect = aceleracion * 1e-3;
    Vector3d<double> grad(0.0, 0.0, 0.0);
    Vector3d<double> result = calculadora.actualizar_gradiente(grad, aceleracion);
    EXPECT_EQ(result.x, expect.x);
    EXPECT_EQ(result.y, expect.y);
    EXPECT_EQ(result.z, expect.z);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeX_bloque0) {
    int bloque = 0;
    double dx = 3.141592654;
    double expect = -0.065 - dx;
    double result = calculadora.interacciones_limite_eje_x(dx, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeX_bloque1) {
    int bloque = -1;
    double dx = 3.141592654;
    double expect = 0.065 + dx;
    double result = calculadora.interacciones_limite_eje_x(dx, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeX_bloque2) {
    int bloque = 2;
    double dx = 3.141592654;
    double expect = 0.0;
    double result = calculadora.interacciones_limite_eje_x(dx, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeY_bloque0) {
    int bloque = 0;
    double dy = 3.141592654;
    double expect = -0.08 - dy;
    double result = calculadora.interacciones_limite_eje_y(dy, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeY_bloque1) {
    int bloque = -1;
    double dy = 3.141592654;
    double expect = 0.1 + dy;
    double result = calculadora.interacciones_limite_eje_y(dy, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeY_bloque2) {
    int bloque = 2;
    double dy = 3.141592654;
    double expect = 0.0;
    double result = calculadora.interacciones_limite_eje_y(dy, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeZ_bloque0) {
    int bloque = 0;
    double dz= 3.141592654;
    double expect = -0.065 - dz;
    double result = calculadora.interacciones_limite_eje_z(dz, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeZ_bloque1) {
    int bloque = -1;
    double dz = 3.141592654;
    double expect = 0.065 + dz;
    double result = calculadora.interacciones_limite_eje_z(dz, bloque);
    EXPECT_EQ(result, expect);
}

TEST_F(CalculadoraTest, InteraccionesLimitesEjeZ_bloque2) {
    int bloque = 2;
    double dz = 3.141592654;
    double expect = 0.0;
    double result = calculadora.interacciones_limite_eje_z(dz, bloque);
    EXPECT_EQ(result, expect);
}