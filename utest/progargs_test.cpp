
#include "../sim/progargs.hpp"
#include "../sim/vector_3d.hpp"
#include "tools_trazas.hpp"

#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <iterator>
#include <string>

class ProgargsTest : public testing::Test {
  public:
    void SetUp() override { preparar_ficheros_tests(); }

    std::string entrada_np1_particulas_1 =
        "trz/archivos_utest/fichero_entrada_np1_particulas_1.fld";
    std::string entrada_np0         = "trz/archivos_utest/fichero_entrada_np0.fld";
    std::string entrada_np_negativo = ".trz/archivos_utest/fichero_entrada_np_negativo.fld";
    std::string entrada_no_valida   = "trz/archivos_utest/fichero_entrada_no_valida";
    std::string entrada_np_2_particulas_1 =
        "trz/archivos_utest/fichero_entrada_np_2_particulas_1.fld";
    std::string entrada_np_1_particulas_2 =
        "trz/archivos_utest/fichero_entrada_np_1_particulas_2.fld";
    std::string salida           = "trz/archivos_utest/salida.fld";
    std::string salida_no_valida = "trz/archivos_utest/fichero_salida_no_valida.fld";

    static Particulas crear_particulas(u_int numero_particulas) {
      Vector3d<double> const pos{0.0230779, -0.0804886, -0.0516096};
      Vector3d<double> const h_v{-0.124551, 0.0130596, 0.0567288};
      Vector3d<double> const vel{-0.129624, 0.172922, 0.0516096};
      Vector3d<double> const acel_init{0.0, -9.8, 0.0};
      Particulas particulas;
      particulas.pos.push_back(pos);
      particulas.gradiente.push_back(h_v);
      particulas.velocidad.push_back(vel);
      particulas.dens.push_back(0.0);
      particulas.aceleracion.push_back(acel_init);
      if (numero_particulas > 1) {
        Vector3d<double> const p_2{0.0412315, -0.0667779, -0.0500864};
        Vector3d<double> const hv2{-0.132673, 0.00470201, 0.123793};
        Vector3d<double> const v_2{-0.131581, 0.0102759, 0.12292};
        particulas.pos.push_back(p_2 /*.to_double()*/);
        particulas.gradiente.push_back(hv2 /*.to_double()*/);
        particulas.velocidad.push_back(v_2 /*.to_double()*/);
        particulas.dens.push_back(0.0);
        particulas.aceleracion.push_back(acel_init);
      }
      return particulas;
    }

    static void crear_fichero(int n_p, std::string const & archivo, float ppm,
                              u_int numero_particulas) {
      int const doce = 12;
      std::ofstream file(archivo, std::ios::binary);
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      file.write(reinterpret_cast<char *>(&ppm), 4);
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      file.write(reinterpret_cast<char *>(&n_p), 4);
      Particulas particulas = crear_particulas(numero_particulas);
      for (int i = 0; i < (int) particulas.dens.size(); i++) {
        Vector3d<float> pos = particulas.pos[i].to_float();
        Vector3d<float> h_v = particulas.gradiente[i].to_float();
        Vector3d<float> vel = particulas.velocidad[i].to_float();
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        file.write(reinterpret_cast<char *>(&pos), doce);
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        file.write(reinterpret_cast<char *>(&h_v), doce);
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        file.write(reinterpret_cast<char *>(&vel), doce);
      }
      file.close();
    }

    void preparar_ficheros_tests() const {
      crear_fichero(1, entrada_np1_particulas_1, 1, 1);
      crear_fichero(0, entrada_np0, 1, 1);
      crear_fichero(-1, entrada_np_negativo, 1, 1);
      crear_fichero(2, entrada_np_2_particulas_1, 1, 1);
      crear_fichero(1, entrada_np_1_particulas_2, 1, 2);
      crear_fichero(2, salida_no_valida, 1, 2);
    }
};

// Tests para Constructor de Progargs *********************************************

TEST_F(ProgargsTest, Constructor_Valido) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld"};
  crear_fichero(1, argumentos_test[1], 1.0, 1);
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  EXPECT_EQ(progargs_test.getter_num_iteraciones(), 1);
  // Borrar ficheros de entrada y salida
  // std::remove
}

TEST_F(ProgargsTest, Constructor_mas_argumentos) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld", "4 argumentos"};
  Progargs progargs_test{};

  EXPECT_EQ(progargs_test.asignar_valores(argumentos_test), -1);
}

TEST_F(ProgargsTest, Constructor_n_it_negativo) {
  std::vector<std::string> const argumentos_test = {"-1", entrada_np1_particulas_1,
                                                    ""
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};

  EXPECT_EQ(progargs_test.asignar_valores(argumentos_test), -2);
}

TEST_F(ProgargsTest, Constructor_Valido_n_it_100) {
  std::vector<std::string> const argumentos_test = {"100", entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld"};
  crear_fichero(1, argumentos_test[1], 1.0, 1);
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  EXPECT_EQ(progargs_test.getter_num_iteraciones(), 100);
}

TEST_F(ProgargsTest, Constructor_n_it_caracter) {
  std::vector<std::string> const argumentos_test = {"a", entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};
  EXPECT_EQ(progargs_test.asignar_valores(argumentos_test), -1);
}

TEST_F(ProgargsTest, Constructor_entrada_no_valida) {
  std::vector<std::string> const argumentos_test = {"0", entrada_no_valida, "fichero_salida_1.fld"};
  Progargs progargs_test{};
  EXPECT_EQ(progargs_test.asignar_valores(argumentos_test), -3);
}

// Tests para read_head de Progargs ****************************************

TEST_F(ProgargsTest, read_head_Valido) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};
  progargs_test.read_head(malla_test, calculadora_test);
  EXPECT_EQ(calculadora_test.ppm, 1);
  EXPECT_EQ(calculadora_test.num_particulas, 1);
}

TEST_F(ProgargsTest, read_head_np_0) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np0, "fichero_salida_1.fld"};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};

  EXPECT_EQ(progargs_test.read_head(malla_test, calculadora_test), -5);
}

TEST_F(ProgargsTest, read_head_np_negativo) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np_negativo,
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};

  EXPECT_EQ(progargs_test.read_head(malla_test, calculadora_test), -5);
}

// Test para read_body de Progargs ************************************

TEST_F(ProgargsTest, read_body_valido) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld"};
  Vector3d<float> const posicion{0.0230779, -0.0804886, -0.0516096};
  Vector3d<float> const gradiente{-0.124551, 0.0130596, 0.0567288};
  Vector3d<float> const velocidad{-0.129624, 0.172922, 0.0516096};
  Vector3d<float> const aceleracion{0, 0, 0};
  double const densidad = 0;

  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};
  progargs_test.read_head(malla_test, calculadora_test);
  Simulacion simulacion_test(1, 1, calculadora_test, malla_test);
  simulacion_test.particulas.reserve_space(calculadora_test.num_particulas);
  progargs_test.read_body(simulacion_test);

  EXPECT_EQ((float) simulacion_test.num_iteraciones, 1);
  EXPECT_EQ((float) simulacion_test.particulas.pos[0].x, posicion.x);
  EXPECT_EQ((float) simulacion_test.particulas.pos[0].y, posicion.y);
  EXPECT_EQ((float) simulacion_test.particulas.pos[0].z, posicion.z);
  EXPECT_EQ((float) simulacion_test.particulas.gradiente[0].x, gradiente.x);
  EXPECT_EQ((float) simulacion_test.particulas.gradiente[0].y, gradiente.y);
  EXPECT_EQ((float) simulacion_test.particulas.gradiente[0].z, gradiente.z);
  EXPECT_EQ((float) simulacion_test.particulas.velocidad[0].x, velocidad.x);
  EXPECT_EQ((float) simulacion_test.particulas.velocidad[0].y, velocidad.y);
  EXPECT_EQ((float) simulacion_test.particulas.velocidad[0].z, velocidad.z);
  EXPECT_EQ((float) simulacion_test.particulas.aceleracion[0].x, aceleracion.x);
  EXPECT_EQ((float) simulacion_test.particulas.aceleracion[0].y, aceleracion.y);
  EXPECT_EQ((float) simulacion_test.particulas.aceleracion[0].z, aceleracion.z);
  EXPECT_EQ((float) simulacion_test.particulas.dens[0], densidad);
}

TEST_F(ProgargsTest, read_body_np_mayor_particulas) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np_2_particulas_1,
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};
  progargs_test.read_head(malla_test, calculadora_test);
  Simulacion simulacion_test(1, 2, calculadora_test, malla_test);
  simulacion_test.particulas.reserve_space(calculadora_test.num_particulas);

  EXPECT_EQ(progargs_test.read_body(simulacion_test), -5);
}

TEST_F(ProgargsTest, read_body_np_menor_particulas) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np_1_particulas_2,
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};
  progargs_test.read_head(malla_test, calculadora_test);
  Simulacion simulacion_test{1, 1, calculadora_test, malla_test};
  simulacion_test.particulas.reserve_space(calculadora_test.num_particulas);

  EXPECT_EQ(progargs_test.read_body(simulacion_test), -5);
}

// Test para write_file de Progargs

TEST_F(ProgargsTest, Write_file_ficheros_iguales) {
  std::vector<std::string> const argumentos_test = {"0", entrada_np1_particulas_1, salida};

  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora const calculadora_test{};
  Malla const malla_test{};
  Simulacion simulacion_test{progargs_test.getter_num_iteraciones(), 1, calculadora_test,
                             malla_test};
  simulacion_test.particulas.reserve_space(calculadora_test.num_particulas);
  Particulas const particulas = crear_particulas(1);
  simulacion_test.particulas  = particulas;
  progargs_test.write_file(1, simulacion_test);

  EXPECT_EQ(compareFiles(entrada_np1_particulas_1, salida), true);
}

TEST_F(ProgargsTest, Write_file_ficheros_distintos) {
  std::vector<std::string> const argumentos_test = {"1", entrada_np1_particulas_1, salida};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora const calc{};
  Malla const malla{};
  Simulacion simulacion_test(progargs_test.getter_num_iteraciones(), 1, calc, malla);
  simulacion_test.particulas.reserve_space(calc.num_particulas);
  Particulas const particulas = crear_particulas(1);
  simulacion_test.particulas  = particulas;
  progargs_test.write_file(1, simulacion_test);
  EXPECT_EQ(compareFiles(salida, salida_no_valida), false);
}
