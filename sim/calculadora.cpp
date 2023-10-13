//
// Created by Eduardo Alarcon on 27/9/23.
//
#include "calculadora.hpp"

// Sección 3.5 - La malla de simulación
// Se puede iniciar la calculadora cuando tengamos ppm y num_particulas
void Calculadora::inicializar_calculadora() {
  suavizado = radio / ppm;
  masa      = dens_fluido / pow(ppm, 3);
}

Vector3d<double> Calculadora::num_bloques_por_eje() {
  Vector3d<double> aux  = b_max - b_min;
  aux                  /= (double) suavizado;
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
double Calculadora::delta_densidades(double const distancia_cuadrado) const {
  double const suavizado_temp = suavizado * suavizado;
  return pow((suavizado_temp - distancia_cuadrado), 3);
}

// Transformación de densidad
double Calculadora::transform_densidad(double densidad) const {
  double parte_1  = densidad + pow(suavizado, 6);
  parte_1        *= 315 / (64 * std::numbers::pi * pow(suavizado, 9));
  return parte_1 * masa;
}

// Transferencia de aceleración
Vector3d<double> Calculadora::aceleracion_primera_parte(Vector3d<double> & posicion_1,
                                                        Vector3d<double> & posicion_2,
                                                        double densidad_1,
                                                        double densidad_2) const {
  double distancia                       = Vector3d<double>::distancia(posicion_1, posicion_2);
  distancia                              = sqrt(fmax(distancia * distancia, 1e-12));
  Vector3d<double> const diff_posiciones = posicion_1 - posicion_2;
  double const acceleration_2            = 15 / (std::numbers::pi * pow(suavizado, 6)) *
                                (3 * masa * p_s * 0.5) * pow(suavizado - distancia, 2) / distancia;
  double const acceleration_3 = densidad_1 + densidad_2 - (2 * dens_fluido);
  return diff_posiciones * acceleration_2 * acceleration_3;
}

Vector3d<double> Calculadora::aceleracion_segunda_parte(Vector3d<double> & velocidad_1,
                                                        Vector3d<double> & velocidad_2) const {
  return (velocidad_2 - velocidad_1) *
         ((45 / (std::numbers::pi * pow(suavizado, 6)) * viscosidad * masa));
}

// Devuelve la aceleación que se tiene que sumar o restar a la original
Vector3d<double> Calculadora::transferencia_aceleracion(Vector3d<double> & parte1,
                                                        Vector3d<double> & parte2,
                                                        double const & denom) {
  parte1 += parte2;
  parte1 /= denom;
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
  return posicion + (gradiente * delta_t) + (aceleracion * (delta_t * delta_t));
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
double Calculadora::interacciones_limite_eje_x(double const d_x, int bloque) {
  if (bloque == 0) { return b_min.x - d_x; }
  if (bloque == -1) { return b_max.x + d_x; }
  return 0.0;
}

double Calculadora::interacciones_limite_eje_y(double const d_y, int bloque) {
  if (bloque == 0) { return b_min.y - d_y; }
  if (bloque == -1) { return b_max.y + d_y; }
  return 0.0;
}

double Calculadora::interacciones_limite_eje_z(double const d_z, int bloque) {
  if (bloque == 0) { return b_min.z - d_z; }
  if (bloque == -1) { return b_max.z + d_z; }
  return 0.0;
}

// Funciones Extras
double Calculadora::cuadrado_distancias(Vector3d<double> posicion_1, Vector3d<double> posicion_2) {
  return pow(Vector3d<double>::distancia(posicion_1, posicion_2), 2);
}
