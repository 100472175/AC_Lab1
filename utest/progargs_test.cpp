//
// Created by cesar on 08/10/23.
//
//
// Created by edu on 10/14/23.
//
//
// Created by adrian on 54/02/23
//

#include "../sim/vector_3d.hpp"
#include "../sim/progargs.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

class ProgargsTest: public testing::Test {
  public:
    void SetUp() override{
      preparar_ficheros_tests();
    }
    std::string entrada_np1_particulas_1 = "fichero_entrada_np1_particulas_1";
    std::string entrada_np0 = "fichero_entrada_np0";
    std::string entrada_np_negativo = "fichero_entrada_np_negativo";
    std::string entrada_np_2_particulas_1 = "fichero_entrada_np_2_particulas_1";
    std::string entrada_np_1_particulas_2 = "fichero_entrada_np_1_particulas_2";
    std::string salida                    = "salida";
    std::string salida_no_valida = "fichero_salida_no_valida";

    Particulas crear_particulas(int numero_particulas){
      Vector3d<double> p {0.0230779, -0.0804886, -0.0516096};
      Vector3d<double> hv {-0.124551, 0.0130596, 0.0567288};
      Vector3d<double> v {-0.129624,0.172922,0.0516096};
      Particulas particulas;
      particulas.posicion.push_back(p.to_double());
      particulas.gradiente.push_back(hv.to_double());
      particulas.velocidad.push_back(v.to_double());
      particulas.densidad.push_back(0.0);
      particulas.aceleracion.push_back(Vector3d<double>(0.0, -9.8, 0.0));
      if (numero_particulas > 1){
        Vector3d<float> p2 {0.0412315, -0.0667779, -0.0500864};
        Vector3d<float> hv2 {-0.132673, 0.00470201, 0.123793};
        Vector3d<float> v2 {-0.131581, 0.0102759, 0.12292};
        particulas.posicion.push_back(p2.to_double());
        particulas.gradiente.push_back(hv2.to_double());
        particulas.velocidad.push_back(v2.to_double());
        particulas.densidad.push_back(0.0);
        particulas.aceleracion.push_back(Vector3d<double>(0.0, -9.8, 0.0));
      }
      return particulas;
    }
    void crear_fichero(const std::string& archivo,int n_p, float ppm, int numero_particulas) {
      std::ofstream file(archivo, std::ios::binary);
      file.write(reinterpret_cast<char *>(&ppm), 4);
      file.write(reinterpret_cast<char *>(&n_p), 4);
      Particulas particulas = crear_particulas(numero_particulas);
      for (int i = 0; i < (int)particulas.densidad.size();i++) {
        Vector3d<float> pos = particulas.posicion[i].to_float();
        Vector3d<float> h_v = particulas.gradiente[i].to_float();
        Vector3d<float> vel = particulas.velocidad[i].to_float();
        file.write(reinterpret_cast<char *>(&pos), 12);
        file.write(reinterpret_cast<char *>(&h_v), 12);
        file.write(reinterpret_cast<char *>(&vel), 12);
      }
    }
    void preparar_ficheros_tests(){
      crear_fichero(entrada_np1_particulas_1,1,1,1);
      crear_fichero(entrada_np0,0,1,1);
      crear_fichero(entrada_np_negativo,-1,1,1);
      crear_fichero(entrada_np_2_particulas_1,2,1,1);
      crear_fichero(entrada_np_1_particulas_2,1,1,2);
      crear_fichero(salida_no_valida,2,1,2);
    }
};

Particulas crear_particulas(int numero_particulas){
  Vector3d<double> p {0.0230779, -0.0804886, -0.0516096};
  Vector3d<double> hv {-0.124551, 0.0130596, 0.0567288};
  Vector3d<double> v {-0.129624,0.172922,0.0516096};
  Particulas particulas;
  particulas.posicion.push_back(p.to_double());
  particulas.gradiente.push_back(hv.to_double());
  particulas.velocidad.push_back(v.to_double());
  particulas.densidad.push_back(0.0);
  particulas.aceleracion.push_back(Vector3d<double>(0.0, -9.8, 0.0));
  if (numero_particulas > 1){
    Vector3d<float> p2 {0.0412315, -0.0667779, -0.0500864};
    Vector3d<float> hv2 {-0.132673, 0.00470201, 0.123793};
    Vector3d<float> v2 {-0.131581, 0.0102759, 0.12292};
    particulas.posicion.push_back(p2.to_double());
    particulas.gradiente.push_back(hv2.to_double());
    particulas.velocidad.push_back(v2.to_double());
    particulas.densidad.push_back(0.0);
    particulas.aceleracion.push_back(Vector3d<double>(0.0, -9.8, 0.0));
  }
  return particulas;
}
void crear_fichero(const std::string& archivo,int n_p, float ppm, int numero_particulas) {
  std::ofstream file(archivo, std::ios::binary);
  file.write(reinterpret_cast<char *>(&ppm), 4);
  file.write(reinterpret_cast<char *>(&n_p), 4);
  Particulas particulas = crear_particulas(numero_particulas);
  for (int i = 0; i < (int)particulas.densidad.size();i++) {
    Vector3d<float> pos = particulas.posicion[i].to_float();
    Vector3d<float> h_v = particulas.gradiente[i].to_float();
    Vector3d<float> vel = particulas.velocidad[i].to_float();
    file.write(reinterpret_cast<char *>(&pos), 12);
    file.write(reinterpret_cast<char *>(&h_v), 12);
    file.write(reinterpret_cast<char *>(&vel), 12);
  }
}


bool compareFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1, std::ifstream::binary);
  std::ifstream f2(p2, std::ifstream::binary);

  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }
  f1.seekg(0, f1.end);
  f2.seekg(0, f2.end);
  size_t lengh1 = f1.tellg();
  size_t lengh2 = f2.tellg();
  std::cout << lengh1 << " " << lengh2 << "\n";
  if (lengh1 != lengh2) {
    std::cout << "size difference\n";
    return false;
  }

  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

bool diffArchivos(const std::string& archivo1, const std::string& archivo2) {
  std::ifstream file1(archivo1);
  std::ifstream file2(archivo2);

  if (!file1.is_open() || !file2.is_open()) {
    std::cerr << "No se pueden abrir los archivos." << std::endl;
    return false;
  }

  std::string linea1, linea2;
  std::vector<std::string> diferencias;

  int numeroLinea = 1;
  while (std::getline(file1, linea1) && std::getline(file2, linea2)) {
    if (linea1 != linea2) {
      diferencias.push_back("Línea " + std::to_string(numeroLinea) + ":");
      diferencias.push_back("Archivo 1: " + linea1);
      diferencias.push_back("Archivo 2: " + linea2);
    }
    numeroLinea++;
  }

  if (diferencias.empty()) {
    std::cout << "Los archivos son idénticos." << std::endl;
    return true;
  } else {
    std::cerr << "Diferencias encontradas:" << std::endl;
    for (const std::string& diferencia : diferencias) {
      std::cerr << diferencia << std::endl;
    }
    return false;
  }
}


bool comparar_archivos(const std::string& archivo1, const std::string& archivo2) {
  std::ifstream file1(archivo1);
  std::ifstream file2(archivo2);

  if (!file1.is_open() || !file2.is_open()) {
    std::cerr << "No se pueden abrir los archivos." << '\n';
    return false;
  }
  int num1 = file1.gcount();
  int num2 = file2.gcount();
  if (num1 != num2) {
    return false;
  }
  std::string linea1;
  std::string linea2;
  for(int i = 0; i < file1.gcount(); i++){
    std::getline(file1, linea1);
    std::getline(file2, linea2);
    if (linea1 != linea2) {
      return false;
    }
  }
  return true;
}



// Tests para Constructor de Progargs *********************************************

TEST_F(ProgargsTest, Constructor_Valido) {
  std::vector <std::string> const argumentos_test = {"1",entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld"};
  crear_fichero(argumentos_test[1],1,1.0,1);
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  EXPECT_EQ(progargs_test.getter_num_iteraciones(), 1);
  // Borrar ficheros de entrada y salida
  // std::remove
}

TEST_F(ProgargsTest, Constructor_mas_argumentos) {
  std::vector <std::string> const argumentos_test = {"1",entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld","4 argumentos"};
  Progargs progargs_test{};

  EXPECT_EQ(progargs_test.asignar_valores(argumentos_test),-1);

}

TEST_F(ProgargsTest, Constructor_n_it_negativo) {
  std::vector <std::string> const argumentos_test = {"-1",entrada_np1_particulas_1,""
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};


  EXPECT_EQ(progargs_test.asignar_valores(argumentos_test), -2);

}

TEST_F(ProgargsTest, Constructor_Valido_n_it_100) {
  std::vector <std::string> const argumentos_test = {"100",entrada_np1_particulas_1, "fichero_salida_1.fld"};
  crear_fichero(argumentos_test[1],1,1.0,1);
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  EXPECT_EQ(progargs_test.getter_num_iteraciones(), 100);
}

TEST_F(ProgargsTest, Constructor_n_it_caracter) {
  std::vector <std::string> const argumentos_test = {"a",entrada_np1_particulas_1, "fichero_salida_1.fld"};
  Progargs progargs_test{};
  EXPECT_EQ(progargs_test.asignar_valores(argumentos_test), -1);

}

// Tests para read_head de Progargs ****************************************

TEST_F(ProgargsTest, read_head_Valido) {
  std::vector <std::string> const argumentos_test = {"1",entrada_np1_particulas_1,
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};
  progargs_test.read_head(malla_test,calculadora_test);
  EXPECT_EQ(calculadora_test.ppm, 1);
  EXPECT_EQ(calculadora_test.num_particulas, 1);
}

TEST_F(ProgargsTest, read_head_np_0) {
  std::vector <std::string> const argumentos_test = {"1",entrada_np0,
                                                    "fichero_salida_1.fld"};
  Progargs progargs_test{};
  progargs_test.asignar_valores(argumentos_test);
  Calculadora calculadora_test{};
  Malla malla_test{};


  EXPECT_EQ(progargs_test.read_head(malla_test,calculadora_test), -5);
  }

TEST_F(ProgargsTest, read_head_np_negativo) {
std::vector <std::string> const argumentos_test = {"1",entrada_np_negativo,
                                                  "fichero_salida_1.fld"};
Progargs progargs_test{};
progargs_test.asignar_valores(argumentos_test);
Calculadora calculadora_test{};
Malla malla_test{};

EXPECT_EQ(progargs_test.read_head(malla_test,calculadora_test), -5);
}

// Test para read_body de Progargs ************************************

TEST_F(ProgargsTest, read_body_valido) {
std::vector <std::string> const argumentos_test = {"1",entrada_np1_particulas_1,
                                                  "fichero_salida_1.fld"};
Vector3d<float> const posicion{0.0230779, -0.0804886, -0.0516096};
Vector3d<float> const gradiente{-0.124551, 0.0130596, 0.0567288};
Vector3d<float> const velocidad{-0.129624,0.172922,0.0516096};
Vector3d<float> const aceleracion{0, -9.8, 0};
double const densidad  = 0;

Progargs progargs_test{};
progargs_test.asignar_valores(argumentos_test);
Calculadora calculadora_test{};
Malla malla_test{};
progargs_test.read_head(malla_test,calculadora_test);
Simulacion simulacion_test(1,1,calculadora_test,malla_test);
progargs_test.read_body(simulacion_test);

EXPECT_EQ((float)simulacion_test.num_iteraciones,1);
EXPECT_EQ((float)simulacion_test.particulas.posicion[0].x,posicion.x);
EXPECT_EQ((float)simulacion_test.particulas.posicion[0].y,posicion.y);
EXPECT_EQ((float)simulacion_test.particulas.posicion[0].z,posicion.z);
EXPECT_EQ((float)simulacion_test.particulas.gradiente[0].x,gradiente.x);
EXPECT_EQ((float)simulacion_test.particulas.gradiente[0].y,gradiente.y);
EXPECT_EQ((float)simulacion_test.particulas.gradiente[0].z,gradiente.z);
EXPECT_EQ((float)simulacion_test.particulas.velocidad[0].x,velocidad.x);
EXPECT_EQ((float)simulacion_test.particulas.velocidad[0].y,velocidad.y);
EXPECT_EQ((float)simulacion_test.particulas.velocidad[0].z,velocidad.z);
EXPECT_EQ((float)simulacion_test.particulas.aceleracion[0].x,aceleracion.x);
EXPECT_EQ((float)simulacion_test.particulas.aceleracion[0].y,aceleracion.y);
EXPECT_EQ((float)simulacion_test.particulas.aceleracion[0].z,aceleracion.z);
EXPECT_EQ((float)simulacion_test.particulas.densidad[0],densidad);
}

TEST_F(ProgargsTest, read_body_np_mayor_particulas) {
std::vector <std::string> const argumentos_test = {"1",entrada_np_2_particulas_1,
                                                  "fichero_salida_1.fld"};
Progargs progargs_test{};
progargs_test.asignar_valores(argumentos_test);
Calculadora calculadora_test{};
Malla malla_test{};
progargs_test.read_head(malla_test,calculadora_test);
Simulacion simulacion_test(1,2,calculadora_test,malla_test);



EXPECT_EQ(progargs_test.read_body(simulacion_test), -5);
}

TEST_F(ProgargsTest, read_body_np_menor_particulas) {
std::vector <std::string> const argumentos_test = {"1",entrada_np_1_particulas_2,
                                                  "fichero_salida_1.fld"};
Progargs progargs_test{};
progargs_test.asignar_valores(argumentos_test);
Calculadora calculadora_test{};
Malla malla_test{};
progargs_test.read_head(malla_test,calculadora_test);
Simulacion simulacion_test{1,1,calculadora_test,malla_test};


EXPECT_EQ(progargs_test.read_body(simulacion_test), -5);
}

// Test para write_file de Progargs


TEST_F(ProgargsTest,Write_file_ficheros_iguales){
std::vector <std::string> const argumentos_test = {"0",entrada_np1_particulas_1, salida};

Progargs progargs_test{};
progargs_test.asignar_valores(argumentos_test);
Calculadora calculadora_test{};
Malla malla_test{};
Simulacion simulacion_test{progargs_test.getter_num_iteraciones(),1,calculadora_test,malla_test};
Particulas const particulas = crear_particulas(1);
simulacion_test.particulas = particulas;
progargs_test.write_file(1,simulacion_test);

EXPECT_EQ(compareFiles(entrada_np1_particulas_1, salida),true);
}
TEST_F(ProgargsTest,Write_file_ficheros_distintos){
std::vector <std::string> const argumentos_test = {"1",entrada_np1_particulas_1, salida};
Progargs progargs_test{};
progargs_test.asignar_valores(argumentos_test);
Calculadora calc{};
Malla malla{};
Simulacion simulacion_test(progargs_test.getter_num_iteraciones(), 1, calc, malla);
Particulas const particulas = crear_particulas(1);
simulacion_test.particulas = particulas;
progargs_test.write_file(1,simulacion_test);
EXPECT_EQ(compareFiles(salida,salida_no_valida),false);
}
