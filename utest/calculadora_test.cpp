//
// Created by cesar on 20/10/23.
//

#include "gtest/gtest.h"
#include "../sim/calculadora.hpp"

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

};

TEST_F(CalculadoraTest, InicializarCalculadora) {
    calculadora_init.inicializar_calculadora();
    EXPECT_EQ(calculadora_init.suavizado, 1.695/(double)2);
    EXPECT_EQ(calculadora_init.masa, 1e3/(double)8);
}

TEST_F(CalculadoraTest, NumBloquesPorEje) {
    Vector3d<double> result(15.0, 21.0, 15.0);
    Vector3d<double> v = calculadora.num_bloques_por_eje();
    EXPECT_EQ(v.x, result.x);
    EXPECT_EQ(v.y, result.y);
    EXPECT_EQ(v.z, result.z);


}

TEST_F(CalculadoraTest, TamanioBloques) {

}
/*
TEST(CalculadoraTest, IndiceBloque) {

}

TEST(CalculadoraTest, InitDensidadAcel) {

}

TEST(CalculadoraTest, DeltaDensidades) {

}


TEST(CalculadoraTest, TransformDensidad) {

}

TEST(CalculadoraTest, AceleracionPrimeraParte) {

}

TEST(CalculadoraTest, AceleracionSegundaParte) {

}

TEST(CalculadoraTest, AceleracionTerceraParte) {

}

TEST(CalculadoraTest, ColisionesLimiteEjeX) {

}

TEST(CalculadoraTest, ColisionesLimiteEjeY) {

}

TEST(CalculadoraTest, COlisionesLimiteEjeZ) {

}

TEST(CalculadoraTest, ActualizarPosicion) {

}

TEST(CalculadoraTest, ActualizarVelocidad) {

}

TEST(CalculadoraTest, ActualizarGradiente) {

}

TEST(CalculadoraTest, InteraccionesLimitesEjeX) {

}

TEST(CalculadoraTest, InteraccionesLimitesEjeY) {

}

TEST(CalculadoraTest, InteraccionesLimiteEjeZ) {

}*/