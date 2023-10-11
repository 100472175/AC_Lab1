//
// Created by Eduardo Alarcon on 27/9/23.
//
#include "calculadora.hpp"

#include <math.h>
#include <vector>

// Sección 3.5 - La malla de simulación
// Se puede iniciar la calculadora cuando tengamos ppm y num_particulas
void Calculadora::inicializar_calculadora() {
  suavizado = radio / ppm;
  masa      = dens_fluido / pow(ppm, 3);
}

Vector3d<double> Calculadora::num_bloques_por_eje() {
  Vector3d<double> aux  = b_max - b_min;
  aux                  /= (double)suavizado;
  aux.x                 = floor(aux.x);
  aux.y                 = floor(aux.y);
  aux.z                 = floor(aux.z);
  return aux;
}

Vector3d<double> Calculadora::tamanio_bloque() {
  return (b_max - b_min) / num_bloques_por_eje();
}

Vector3d<int> Calculadora::indice_bloque(Vector3d<double> const & posicion) {
  int const coord_x = floor((posicion.x - b_min.x) / tamanio_bloque().x);
  int const coord_y = floor((posicion.y - b_min.y) / tamanio_bloque().y);
  int const coord_z = floor((posicion.z - b_min.z) / tamanio_bloque().z);
  return Vector3d<int>{coord_x, coord_y, coord_z};
}

// Sección 4.3.2 - Cálculo de las aceleraciones
// Inidiación de densidad y aceleraciones [pg. 8]
void Calculadora::init_densidad_accel() {
  // return Vector3d<double>{0.0, 0.0, 0.0}
}

// Incremento de densidades [pg. 8]
double Calculadora::delta_densidades(Vector3d<double> pos_1, Vector3d<double> pos_2) const {
  double const suavizado_temp = suavizado * suavizado;
  double distancia            = pos_1.distancia(pos_1, pos_2);
  distancia                   = distancia * distancia;
  if (distancia >= suavizado_temp) { return 0.0; }
  return pow((suavizado_temp - distancia), 3);
}

// Transformación de densidad [pg. 8]
double Calculadora::transform_densidad(double densidad) const {
  double parte_1       = densidad + pow(suavizado, 6);
  double const parte_2 = 315 / (64 * std::numbers::pi * pow(suavizado, 9));
  return parte_1 * parte_2 * masa;
}

// Transferencia de aceleración [pg. 8]

Vector3d<double> Calculadora::aceleracion_primera_parte(Vector3d<double> & posicion_1,
                                                        Vector3d<double> & posicion_2,
                                                        double densidad_1,
                                                        double densidad_2) const {
  double distancia = posicion_1.distancia(posicion_1, posicion_2);
  distancia        = distancia * distancia;
  if (distancia < pow(suavizado, 2)) {
    Vector3d<double> const diff_posiciones = posicion_1 - posicion_2;
    double const acceleration_2            = 15 / (std::numbers::pi * pow(suavizado, 6)) * masa *
                                  pow(suavizado - distancia, 2) / distancia;
    double const acceleration_3 = densidad_1 + densidad_2 - 2 * dens_fluido;
    return diff_posiciones * acceleration_2 * acceleration_3;
  }
  return Vector3d<double>{0.0, 0.0, 0.0};
}

Vector3d<double> Calculadora::aceleracion_segunda_parte(Vector3d<double> & velocidad_1,
                                                        Vector3d<double> & velocidad_2) const {
  return velocidad_2 -
         velocidad_1 * (45 / (std::numbers::pi * pow(pow(suavizado, 3), 2) * viscosidad * masa));
}

// Devuelve la aceleación que se tiene que sumar o restar a la original
Vector3d<double> Calculadora::transferencia_aceleracion(Vector3d<double> & parte1,
                                                        Vector3d<double> & parte2,
                                                        double const denominador) {
  parte1 += parte2;
  parte1 /= denominador;
  return parte1;
}

// Sección 4.3.3 Colisiones de partículas
// Colisiones con los límites del eje x [pg. 9]
/// Hay que sumarle el rsultado a la aceleración, no se hace dentro de la función por límite de
/// parámetros
double Calculadora::colisiones_limite_eje_x(int bloque, double const & delta_x,
                                            Vector3d<double> & velocidad) {
  if (bloque == 0) { return s_c * delta_x - d_v * velocidad.x; }
  return -s_c * delta_x + d_v * d_v * velocidad.x;
}

double Calculadora::colisiones_limite_eje_y(int bloque, double const & delta_y,
                                            Vector3d<double> & velocidad) {
  if (bloque == 0) { return s_c * delta_y - d_v * velocidad.y; }
  return -s_c * delta_y + d_v * d_v * velocidad.y;
}

double Calculadora::colisiones_limite_eje_z(int bloque, double const & delta_z,
                                            Vector3d<double> & velocidad) {
  if (bloque == 0) { return s_c * delta_z - d_v * velocidad.z; }
  return -s_c * delta_z + d_v * d_v * velocidad.z;
}

// Movimiento de las partículas 4.3.4
Vector3d<double> Calculadora::actualizar_posicion(Vector3d<double> & posicion,
                                                  Vector3d<double> & gradiente,
                                                  Vector3d<double> & aceleracion) {
  return posicion + gradiente * delta_t + aceleracion * delta_t * delta_t;
}

Vector3d<double> Calculadora::actualizar_velocidad(Vector3d<double> & gradiente,
                                                   Vector3d<double> & aceleracion) {
  Vector3d<double> velocidad = gradiente + aceleracion * (delta_t / (double) 2);
  return velocidad;
}

Vector3d<double> Calculadora::actualizar_gradiente(Vector3d<double> & gradiente,
                                                   Vector3d<double> & aceleracion) {
  return gradiente + aceleracion * delta_t;
}

// 4.3.5 Interacciones con los límites del recinto
// Cuando se llame a la función, hay que comprobar si el rsultado es negativo, y si lo es, invertir
// la velocidad y el gradiente
// Colisiones con los límites en el eje x [pg. 10]
double Calculadora::interacciones_limite_eje_x(Vector3d<double> posicion) {
  double new_dx = 0.0;
  int const c_x = Calculadora::indice_bloque(posicion).x;
  if (c_x == 0) {
    new_dx = posicion.x - b_min.x;
    if (new_dx < 0.0) {
      posicion.x = b_min.x - new_dx;
      return new_dx;
    }
  } else if (c_x == Calculadora::num_bloques_por_eje().x - 1) {
    new_dx = b_max.x - posicion.x;
    if (new_dx < 0.0) { posicion.x = b_min.x + new_dx; }
  }
  return new_dx;
}

// Colisiones con los límites en el eje y [pg. 10]
double Calculadora::interacciones_limite_eje_y(Vector3d<double> posicion) {
  double new_dy = 0.0;
  int const c_y = Calculadora::indice_bloque(posicion).y;
  if (c_y == 0) {
    new_dy = posicion.y - b_min.y;
    if (new_dy < 0.0) {
      posicion.y = b_min.y - new_dy;
      return new_dy;
    }
  } else if (c_y == Calculadora::num_bloques_por_eje().y - 1) {
    new_dy = b_max.y - posicion.y;
    if (new_dy < 0.0) { posicion.y = b_min.y + new_dy; }
  }
  return new_dy;
}

// Colisiones con los límites en el eje z [pg. 10]
double Calculadora::interacciones_limite_eje_z(Vector3d<double> posicion) {
  double new_dz = 0.0;
  int const c_z = Calculadora::indice_bloque(posicion).z;
  if (c_z == 0) {
    new_dz = posicion.z - b_min.z;
    if (new_dz < 0.0) {
      posicion.z = b_min.z - new_dz;
      return new_dz;
    }
  } else if (c_z == Calculadora::num_bloques_por_eje().z - 1) {
    new_dz = b_max.z - posicion.z;
    if (new_dz < 0.0) { posicion.z = b_min.z + new_dz; }
  }
  return new_dz;
}

// Funciones Extras
double Calculadora::cuadradodistancias(Vector3d<double> posicion_1, Vector3d<double> posicion_2) {
  return pow(Vector3d<double>::distancia(posicion_1, posicion_2), 2);
}
