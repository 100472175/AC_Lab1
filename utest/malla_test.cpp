//
// Created by Eduardo on 10/11/23.
//

#include "../sim/malla.hpp"

#include <gtest/gtest.h>

TEST(MallaTest, CREACIONEINDEXADOMALLA) {
  // Creando la Malla y comprobando la creación de bloques.
  Malla malla;
  Vector3d<double> const dimensions{3.0, 2.0, 4.0};
  malla.inicializar_malla(dimensions);

  EXPECT_EQ(malla.n_x, 3);
  EXPECT_EQ(malla.n_y, 2);
  EXPECT_EQ(malla.n_z, 4);
  EXPECT_EQ(malla.tamano, 24);
  EXPECT_EQ(malla.bloques.size(), 24);

  // Comprobar si los bloques se han creado en la posición correcta.
  for (int eje_z = 0; eje_z < malla.n_z; eje_z++) {
    for (int eje_y = 0; eje_y < malla.n_y; eje_y++) {
      for (int eje_x = 0; eje_x < malla.n_x; eje_x++) {
        int const pos = malla.get_pos(eje_x, eje_y, eje_z);
        EXPECT_EQ(malla.bloques[pos].i, eje_x);
        EXPECT_EQ(malla.bloques[pos].j, eje_y);
        EXPECT_EQ(malla.bloques[pos].k, eje_z);
      }
    }
  }

  // Comprobar si los rangos que están fuera de bloque son correctos:
  Vector3d<int> outOfRangeIndex{-1, 3, 5};
  Vector3d<int> inRangeIndex{2, 1, 3};

  auto correctedIndex = malla.fuera_de_rango(outOfRangeIndex);
  EXPECT_EQ(correctedIndex.x, 0);
  EXPECT_EQ(correctedIndex.y, 1);
  EXPECT_EQ(correctedIndex.z, 3);

  correctedIndex = malla.fuera_de_rango(inRangeIndex);
  EXPECT_EQ(correctedIndex.x, 2);
  EXPECT_EQ(correctedIndex.y, 1);
  EXPECT_EQ(correctedIndex.z, 3);
}

TEST(MallaTest, VLOQUESVECINOSGENERAL) {
  // Comprobar si los bloques contiguos están correctamente identificados
  Malla malla;
  Vector3d<double> const dimensions{3.0, 3.0, 3.0};
  malla.inicializar_malla(dimensions);

  // Crea los bloques contiguos para el bloque 1, 1, 1
  malla.bloques_contiguos(1, 1, 1);

  // Comprobar si se identifica el número de bloques contiguos correctos
  int const pos = malla.get_pos(1, 1, 1);
  EXPECT_EQ(malla.bloques[pos].bloques_contiguos.size(),
            27);  // Asumiendo una malla de 3x3x3, incluyendo a su mismo bloque.
}

TEST(MallaTest, BLOQUESCONTIGUOSESQUINA) {
  // Comprobar si los bloques de la esquina, que sean contiguos se seleccionan correctamente
  Malla malla;
  Vector3d<double> const dimensions{10.0, 10.0, 10.0};
  malla.inicializar_malla(dimensions);

  // Crea los bloques contiguos para el bloque 1, 1, 1
  malla.bloques_contiguos(0, 0, 0);

  // Comprobar si se identifica el número de bloques contiguos correctos
  int const pos = malla.get_pos(0, 0, 0);
  EXPECT_EQ(malla.bloques[pos].bloques_contiguos.size(),
            8);  // Asumiendo una malla de 3x3x3, incluyendo a su mismo bloque.
}

TEST(MallaTest, BLOQUESCONTIGUOSARISTA) {
  // Comprobar si los bloques de la arista, que sean contiguos se seleccionan correctamente
  Malla malla;
  Vector3d<double> const dimensions{10.0, 10.0, 10.0};
  malla.inicializar_malla(dimensions);

  // Crea los bloques contiguos para el bloque 0, 0, 1
  malla.bloques_contiguos(0, 0, 1);

  // Comprobar si se identifica el número de bloques contiguos correctos
  int const pos = malla.get_pos(0, 0, 1);
  EXPECT_EQ(malla.bloques[pos].bloques_contiguos.size(),
            12);  // Asumiendo una malla de 3x3x3, incluyendo a su mismo bloque.
}

TEST(MallaTest, MALLADIMENSION0) {
  // Comprobar que pasa cuando la dimensión de la malla proporcionada es de dimensión 0
  Malla malla;
  Vector3d<double> const dimensions{0, 0, 0};
  malla.inicializar_malla(dimensions);

  malla.bloques_contiguos(0, 0, 0);

int const pos = malla.get_pos(0,0,0);
EXPECT_EQ(malla.bloques[pos].bloques_contiguos.size(), 0);
}

