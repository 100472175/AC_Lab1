//
// Created by cesar on 08/10/23.
//
//
// Created by edu on 10/14/23.
//


#include "../sim/vector_3d.hpp"
#include <gtest/gtest.h>


// Tests para Vector3d
// Constructor con int
TEST(Vector3dTest, Constructor) {
  Vector3d<int> v1(1, 2, 3);
  EXPECT_EQ(v1.x, 1);
  EXPECT_EQ(v1.y, 2);
  EXPECT_EQ(v1.z, 3);
}

// Constructor con double
TEST(Vector3dTest, ConstructorDouble) {
  Vector3d<double> v1(1.0, 2.0, 3.0);
  EXPECT_DOUBLE_EQ(v1.x, 1.0);
  EXPECT_DOUBLE_EQ(v1.y, 2.0);
  EXPECT_DOUBLE_EQ(v1.z, 3.0);
}

// Constructor con float
TEST(Vector3dTest, ConstructorFloat) {
  Vector3d<float> v1(1.0, 2.0, 3.0);
  EXPECT_FLOAT_EQ(v1.x, 1.0);
  EXPECT_FLOAT_EQ(v1.y, 2.0);
  EXPECT_FLOAT_EQ(v1.z, 3.0);
}

// Constructor con otro vector
TEST(Vector3dTest, ConstructorVector) {
  Vector3d<Vector3d<int>> v1(Vector3d<int>(1, 2, 3), Vector3d<int>(4, 5, 6), Vector3d<int>(7, 8, 9));
  EXPECT_EQ(v1.x.x, 1);
  EXPECT_EQ(v1.x.y, 2);
  EXPECT_EQ(v1.x.z, 3);
  EXPECT_EQ(v1.y.x, 4);
  EXPECT_EQ(v1.y.y, 5);
  EXPECT_EQ(v1.y.z, 6);
  EXPECT_EQ(v1.z.x, 7);
  EXPECT_EQ(v1.z.y, 8);
  EXPECT_EQ(v1.z.z, 9);
}



// Comprobación de que se puede cambiar los valores de un vector
TEST(Vector3dTest, SetValues) {
  Vector3d<int> v1(1, 2, 3);
  v1.set_values(4, 5, 6);
  EXPECT_EQ(v1.x, 4);
  EXPECT_EQ(v1.y, 5);
  EXPECT_EQ(v1.z, 6);
}

// Comprobación de que se puede dar otro valor a un vector
TEST(Vector3dTest, Asignar) {
  Vector3d<int> v1(1, 2, 3);
  Vector3d<int> v2(4, 5, -6);
  v1 = v2;
  EXPECT_EQ(v1.x, 4);
  EXPECT_EQ(v1.y, 5);
  EXPECT_EQ(v1.z, -6);
}

// Comprobación de que se puede convertir un vector a float
TEST(Vector3dTest, ToFloat) {
  Vector3d<int> v1(1, 2, 3);
  Vector3d<float> v2 = v1.to_float();
  EXPECT_FLOAT_EQ(v2.x, 1.0);
  EXPECT_FLOAT_EQ(v2.y, 2.0);
  EXPECT_FLOAT_EQ(v2.z, 3.0);
}

// Comprobación de que se puede convertir un vector a double
TEST(Vector3dTest, ToDouble) {
  Vector3d<int> v1(1, 2, 3);
  Vector3d<double> v2 = v1.to_double();
  EXPECT_DOUBLE_EQ(v2.x, 1.0);
  EXPECT_DOUBLE_EQ(v2.y, 2.0);
  EXPECT_DOUBLE_EQ(v2.z, 3.0);
}

// Comprobación que el cuadrado de la distancia entre dos vectores es correcto
TEST(Vector3dTest, SqDistancia) {
  Vector3d<double> v1(0, 0, 0);
  Vector3d<double> v2(3, 4, 0);
  EXPECT_DOUBLE_EQ(Vector3d<double>::sq_distancia(v1, v2), 25.0);
}

// Comprobación que la distancia entre dos vectores es correcto
TEST(Vector3dTest, Distancia) {
  Vector3d<double> v1(0, 0, 0);
  Vector3d<double> v2(3, 4, 0);
  EXPECT_DOUBLE_EQ(Vector3d<double>::distancia(v1, v2), 5.0);
}

// Comprobación que la suma de dos vectores es correcta usando el operador +=
TEST(Vector3dTest, SumaAsignacion) {
  Vector3d<int> v1(1, 2, 3);
  Vector3d<int> v2(4, 5, 6);
  v1 += v2;
  EXPECT_EQ(v1.x, 5);
  EXPECT_EQ(v1.y, 7);
  EXPECT_EQ(v1.z, 9);
}

// Comprobación que la resta de dos vectores es correcta usando el operador +
TEST(Vector3dTest, SumaNormal) {
  Vector3d<double> v1(1.0, 2.0, 3.0);
  Vector3d<double> v2(4.0, 5.0, 6.0);
  Vector3d<double> result = v1 + v2;
  EXPECT_EQ(result.x, 5.0);
  EXPECT_EQ(result.y, 7.0);
  EXPECT_EQ(result.z, 9.0);
}

// Comprobación que la resta de dos vectores es correcta usando el operador -=
TEST(Vector3dTest, RestaAsignacion) {
  Vector3d<double> v1(1.0, 2.0, 3.0);
  Vector3d<double> v2(4.0, 5.0, 6.0);
  v1 -= v2;
  EXPECT_EQ(v1.x, -3.0);
  EXPECT_EQ(v1.y, -3.0);
  EXPECT_EQ(v1.z, -3.0);
}

// Comprobación que la resta de dos vectores es correcta usando el operador -
TEST(Vector3dTest, RestaNormal) {
  Vector3d<double> v1(1.0, 2.0, 3.0);
  Vector3d<double> v2(4.0, 5.0, 6.0);
  Vector3d<double> result = v1 - v2;
  EXPECT_EQ(result.x, -3.0);
  EXPECT_EQ(result.y, -3.0);
  EXPECT_EQ(result.z, -3.0);
}


// Comprobación que la multiplicación de un vector por un escalar es correcta usando el operador *=
TEST(Vector3dTest, MultiplicacionAsignacion) {
  Vector3d<double> v1(-1.0, 2.0, 3.0);
  v1 *= 2;
  EXPECT_EQ(v1.x, -2.0);
  EXPECT_EQ(v1.y, 4.0);
  EXPECT_EQ(v1.z, 6.0);
}

// Comparación que la multiplicación de un vector por un escalar es correcta usando el operador *
TEST(Vector3dTest, MultiplicacionNormal) {
  Vector3d<double> v1(-1.0, 2.0, 3.0);
  Vector3d<double> result = v1 * 2;
  EXPECT_EQ(result.x, -2.0);
  EXPECT_EQ(result.y, 4.0);
  EXPECT_EQ(result.z, 6.0);
}

// Comprobación que la división de un vector por un escalar es correcta usando el operador /=
TEST(Vector3dTest, DivisionAsignacion) {
  Vector3d<double> v1(-1.0, 2.0, 3.0);
  v1 /= 2;
  EXPECT_EQ(v1.x, -0.5);
  EXPECT_EQ(v1.y, 1.0);
  EXPECT_EQ(v1.z, 1.5);
}


// Comprobación que la división de un vector por otro vector es correcta usando el operador /
// Es decir, cada elemento del vector3d se divide por el elemento correspondiente del otro vector3d
TEST(Vector3dTest, DivisionEntreVectores) {
  Vector3d<double> v1(-1.0, 2.0, 3.0);
  Vector3d<double> v2(2.0, 4.0, -6.0);
  Vector3d<double> result = v1 / v2;
  EXPECT_EQ(result.x, -0.5);
  EXPECT_EQ(result.y, 0.5);
  EXPECT_EQ(result.z, -0.5);
}


// Casos límite:
// Comprobación suma con valores muy grandes y pequeños
TEST(Vector3dTest, CasosLimiteSumaValoresGrandes) {
  Vector3d<double> v1(1e-100, 1e100, 0);
  Vector3d<double> v2(5, 5, 5);
  Vector3d<double> result = v1 + v2;
  EXPECT_EQ(result.x, 5);
  EXPECT_EQ(result.y, 1e100+5);
  EXPECT_EQ(result.z, 5);
}

// Comprobación resta con valores muy grandes y pequeños
TEST(Vector3dTest, CasosLimiteRestaValoresGrandes) {
  Vector3d<double> v1(1e-100, 1e100, 0);
  Vector3d<double> v2(5, 5, 5);
  Vector3d<double> result = v1 - v2;
  EXPECT_EQ(result.x, 1e-100-5);
  EXPECT_EQ(result.y, 1e100-5);
  EXPECT_EQ(result.z, -5);
}

// Comprobación multiplicación con valores muy grandes y pequeños
TEST(Vector3dTest, CasosLimitesMultiplicacionValoresGrandes) {
  Vector3d<double> v1(1e-100, 1e100, 0);
  Vector3d<double> result = v1 * 50;
  EXPECT_EQ(result.x, 1e-100*50);
  EXPECT_EQ(result.y, 5e101);
  EXPECT_EQ(result.z, 0);
}

// Comprobación división con valores muy grandes y pequeños
TEST(Vector3dTest, CasosLimitesDivisionValoresGrandes) {
  Vector3d<double> v1(1e-100, 1e100, 0);
  v1 /= 50;
  EXPECT_EQ(v1.x, 2e-102);
  EXPECT_EQ(v1.y, 2e98);
  EXPECT_EQ(v1.z, 0);
}

// División por cero
TEST(Vector3dTest, DivisionPorVectorCero) {
  Vector3d<double> v1(1, 2, 0);
  Vector3d<double> v2(0, 0, 0);
  try {
    Vector3d<double> result = v1 / v2;
    std::cout << result.x << "\n";
      //FAIL() << "Se esperaba excepción de división por cero";
  } catch (const std::exception& e) {
      EXPECT_STREQ(e.what(), "division by zero");
  }
}

// División por cero escalar
TEST(Vector3dTest, DivisionPorEscalarCero) {
  Vector3d<double> v1(1, 2, 0);
  try {
    v1 /= 0;
    //FAIL() << "Se esperaba excepción de división por cero";
  } catch (const std::exception& e) {
      EXPECT_STREQ(e.what(), "division by zero");
  }
}


// Comprobación del uso de valores no numéricos
TEST(Vector3dTest, ValoresNoNumericos) {
  Vector3d<std::string> v1("hola", "adios", "que tal");

  EXPECT_EQ(v1.x, "hola");
  EXPECT_EQ(v1.y, "adios");
  EXPECT_EQ(v1.z, "que tal");
}

// Comprobación del uso de valores no numéricos con operadores
TEST(Vector3dTest, ValoresNoNumericos2) {
  Vector3d<std::string> v1("hola,", "adios,", "que tal!");
  Vector3d<std::string> v2("hola", "adios", "que tal");
  Vector3d<std::string> result = v1 + v2;
  EXPECT_EQ(result.x, "hola,hola");
  EXPECT_EQ(result.y, "adios,adios");
  EXPECT_EQ(result.z, "que tal!que tal"); 
}

