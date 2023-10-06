//
// Created by Eduardo Alarcon on 27/9/23.
//
#include "calculadora.hpp"

#include <vector>

// Sección 3.5 - La malla de simulación
double Calculadora::masa_calc() const {
  return dens_fluido / pow(ppm, 3);
}

double Calculadora::suavizado_calc() const {
  return radio / ppm;
}

// Constructor
Calculadora::Calculadora(double const & ppm_)
  : ppm(ppm_), suavizado(suavizado_calc()), masa(masa_calc()) { }

double Calculadora::num_bloques_por_eje(double const & max, double const & min) const {
  return floor((min - max) / suavizado);
}

double Calculadora::tamanio_bloque_por_eje(double const & max, double const & min) const {
  return (max - min) / num_bloques_por_eje(max, min);
}

Vector3d_int Calculadora::indice_bloque(Vector3d const & posicion) {
  int const coord_x =
      floor((posicion.x - b_min.x) / Calculadora::tamanio_bloque_por_eje(b_max.x, b_min.x));
  int const coord_y =
      floor((posicion.y - b_min.y) / Calculadora::tamanio_bloque_por_eje(b_max.y, b_min.y));
  int const coord_z =
      floor((posicion.z - b_min.z) / Calculadora::tamanio_bloque_por_eje(b_max.z, b_min.z));
  Vector3d_int result{coord_x, coord_y, coord_z};
  return result;
}

// Sección 4.3.2 - Cálculo de las aceleraciones
// Inidiación de densidad y aceleraciones [pg. 8]
void Calculadora::init_densidad_accel() {
  // return Vector3d{0.0, 0.0, 0.0}
}

// Incremento de densidades [pg. 8]
int Calculadora::delta_densidades(int particula1, int particula2, std::vector<double> densidad,
                                  std::vector<Vector3d> posicion) const {
  // if ((particula1 > particula2) or (particula1 == particula2)) { return 0.0; }
  double const suavizado_temp = suavizado * suavizado;
  double const distancia = posicion[particula1].x; //distancia(posicion[particula1], posicion[2]);  // TODO: Cesar, la función de distancia
  if (distancia >= suavizado_temp) { return 0.0; }
  double const diff_densidad = pow((suavizado_temp - distancia), 3);
  densidad[particula1]       = densidad[particula1] + diff_densidad;
  densidad[particula2]       = densidad[particula2] + diff_densidad;
  return 1.0;
}

// Transformación de densidad [pg. 8]
double Calculadora::transform_densidad(int particula, std::vector<double> densidad) const {
  double parte_1       = densidad[particula] + pow(suavizado, 6);
  double const parte_2 = 315 / (64 * std::numbers::pi * pow(suavizado, 9));
  return parte_1 * parte_2 * masa;
}

// Transferencia de aceleración [pg. 8]
Vector3d Calculadora::trasnfer_accel_particulas_calculo(std::tuple<int, int> particula,
                                                        std::vector<Vector3d> posicion,
                                                        std::vector<double> densidad,
                                                        std::vector<Vector3d> velocidad) {
  // if ((particula1 > particula2) or (particula1 == particula2)) { return -1.0; }
  // Distancia entre dos partículas 3 dimensionales
  double distancia = 10.0;  // TODO: Cesar, la función de distancia
  if (distancia < pow(suavizado, 2)) {
    // Aceleración entre dos partículas 3 dimensionales
    Vector3d diff_posiciones    = posicion[get<0>(particula)] - posicion[get<1>(particula)];
    double const acceleration_2 = 15 / (std::numbers::pi * pow(suavizado, 6)) * masa *
                                  pow(suavizado - distancia, 2) / distancia;
    double const acceleration_3 =
        densidad[get<0>(particula)] + densidad[get<1>(particula)] - dens_fluido;
    Vector3d acceleration_4     = velocidad[get<1>(particula)] - velocidad[get<0>(particula)];
    double const acceleration_5 = 45 / (std::numbers::pi * pow(suavizado, 6)) * masa;
    double acceleration_div     = densidad[get<0>(particula)] * densidad[get<1>(particula)];
    // Primera parte de la aceleración
    diff_posiciones *= acceleration_2 * acceleration_3;
    acceleration_4  *= acceleration_5;
    diff_posiciones += acceleration_4;
    diff_posiciones /= acceleration_div;
    // Devuelve la aceleración, que se suma en otra función, aqui solo se calcula el delta
    return diff_posiciones;
  }
  return Vector3d{0.0, 0.0, 0.0};
  }


void Calculadora::trasnfer_accel_particulas(int particula1, int particula2,
                                            std::vector<Vector3d> aceleracion,
                                            Vector3d delta_aceleracion) {
  aceleracion[particula1] += delta_aceleracion;
  aceleracion[particula2] -= delta_aceleracion;
  return;
}

// Sección 4.3.3 Colisiones de partículas
// Colisiones con los límites del eje  x [pg. 9]
void Calculadora::collisiones_limite_eje_x(int particula, std::vector<Vector3d> posicion,
                                           std::vector<Vector3d> velocidad,
                                           std::vector<Vector3d> aceleracion) {
  double new_x = posicion[particula].x + velocidad[particula].x * delta_t;
  double delta_x;
  int const c_x = Calculadora::indice_bloque(posicion[particula]).x;
  if (c_x == 0) {
    delta_x = d_p - (new_x - b_min.x);
    if (delta_x > 10e-10) {
      aceleracion[particula].x =
          aceleracion[particula].x + s_c * delta_x - d_v * velocidad[particula].x;
    }
  } else if (c_x == Calculadora::num_bloques_por_eje(b_max.x, b_min.x) - 1) {
    delta_x = d_p - (b_max.x - new_x);
    if (delta_x > 10e-10) {
      aceleracion[particula].x =
          aceleracion[particula].x - s_c * delta_x + d_v * d_v * velocidad[particula].x;
    }
  }
}

// Colisiones con los límites del eje y [pg. 10]
void Calculadora::collisiones_limite_eje_y(int particula, std::vector<Vector3d> posicion,
                                           std::vector<Vector3d> velocidad,
                                           std::vector<Vector3d> aceleracion) {
  double new_x = posicion[particula].y + velocidad[particula].y * delta_t;
  double delta_x;
  int const c_x = Calculadora::indice_bloque(posicion[particula]).y;
  if (c_x == 0) {
    delta_x = d_p - (new_x - b_min.y);
    if (delta_x > 10e-10) {
      aceleracion[particula].y =
          aceleracion[particula].y + s_c * delta_x - d_v * velocidad[particula].y;
    }
  } else if (c_x == Calculadora::num_bloques_por_eje(b_max.y, b_min.y) - 1) {
    delta_x = d_p - (b_max.y - new_x);
    if (delta_x > 10e-10) {
      aceleracion[particula].y =
          aceleracion[particula].y - s_c * delta_x + d_v * d_v * velocidad[particula].y;
    }
  }
}

// Colisiones con los límites del eje z [pg. 10]
void Calculadora::collisiones_limite_eje_z(int particula, std::vector<Vector3d> posicion,
                                           std::vector<Vector3d> velocidad,
                                           std::vector<Vector3d> aceleracion) {
  double new_x = posicion[particula].z + velocidad[particula].z * delta_t;
  double delta_x;
  int const c_x = Calculadora::indice_bloque(posicion[particula]).z;
  if (c_x == 0) {
    delta_x = d_p - (new_x - b_min.z);
    if (delta_x > 10e-10) {
      aceleracion[particula].z =
          aceleracion[particula].z + s_c * delta_x - d_v * velocidad[particula].z;
    }
  } else if (c_x == Calculadora::num_bloques_por_eje(b_max.z, b_min.z) - 1) {
    delta_x = d_p - (b_max.z - new_x);
    if (delta_x > 10e-10) {
      aceleracion[particula].z =
          aceleracion[particula].z - s_c * delta_x + d_v * d_v * velocidad[particula].z;
    }
  }
}

// Movimiento de las partículas 4.3.4
void Calculadora::actualizar_posicion(int particula, std::vector<Vector3d> posicion,
                                      std::vector<Vector3d> suavizado_vec,
                                      std::vector<Vector3d> aceleracion) {
  // Que narices, creo que las fórmulas estan mal en el pg, ágina 10 al final
  posicion[particula].x = posicion[particula].x + suavizado_vec[particula].x * delta_t +
                          aceleracion[particula].x * delta_t * delta_t;
  posicion[particula].y = posicion[particula].y + suavizado_vec[particula].y * delta_t +
                          aceleracion[particula].y * delta_t * delta_t;
  posicion[particula].z = posicion[particula].z + suavizado_vec[particula].z * delta_t +
                          aceleracion[particula].z * delta_t * delta_t;
}

void Calculadora::actualizar_velocidad(int particula, std::vector<Vector3d> velocidad,
                                       std::vector<Vector3d> suavizado_vec,
                                       std::vector<Vector3d> aceleracion) {
  velocidad[particula].x = suavizado_vec[particula].x + (aceleracion[particula].x * delta_t) / 2;
  velocidad[particula].y = suavizado_vec[particula].y + (aceleracion[particula].y * delta_t) / 2;
  velocidad[particula].z = suavizado_vec[particula].z + (aceleracion[particula].z * delta_t) / 2;
}

void Calculadora::actualizar_gradiente(int particula, std::vector<Vector3d> suavizado_vec,
                                       std::vector<Vector3d> aceleracion) {
  suavizado_vec[particula].x = suavizado_vec[particula].x + (aceleracion[particula].x * delta_t);
  suavizado_vec[particula].y = suavizado_vec[particula].y + (aceleracion[particula].y * delta_t);
  suavizado_vec[particula].z = suavizado_vec[particula].z + (aceleracion[particula].z * delta_t);
}

// 4.3.5 Interacciones con los límites del recinto
// Colisiones con los límites en el eje x [pg. 10]
void Calculadora::interacciones_limite_eje_x(int particula, std::vector<Vector3d> posicion,
                                             std::vector<Vector3d> velocidad,
                                             std::vector<Vector3d> suavizado_vec) {
  double new_dx;
  int const c_x = Calculadora::indice_bloque(posicion[particula]).x;
  if (c_x == 0) {
    new_dx = posicion[particula].x - b_min.x;
    if (new_dx < 0.0) {
      posicion[particula].x      = b_min.x - new_dx;
      velocidad[particula].x     = -velocidad[particula].x;
      suavizado_vec[particula].x = -suavizado_vec[particula].x;
    }
  } else if (c_x == Calculadora::num_bloques_por_eje(b_max.x, b_min.x) - 1) {
    new_dx = b_max.x - posicion[particula].x;
    if (new_dx < 0.0) {
      posicion[particula].x      = b_min.x + new_dx;
      velocidad[particula].x     = -velocidad[particula].x;
      suavizado_vec[particula].x = -suavizado_vec[particula].x;
    }
  }
}

// Colisiones con los límites en el eje y [pg. 10]
void Calculadora::interacciones_limite_eje_y(int particula, std::vector<Vector3d> posicion,
                                             std::vector<Vector3d> velocidad,
                                             std::vector<Vector3d> suavizado_vec) {
  double new_dx;
  int const c_x = Calculadora::indice_bloque(posicion[particula]).y;
  if (c_x == 0) {
    new_dx = posicion[particula].y - b_min.y;
    if (new_dx < 0.0) {
      posicion[particula].y      = b_min.y - new_dx;
      velocidad[particula].y     = -velocidad[particula].y;
      suavizado_vec[particula].y = -suavizado_vec[particula].y;
    }
  } else if (c_x == Calculadora::num_bloques_por_eje(b_max.y, b_min.y) - 1) {
    new_dx = b_max.y - posicion[particula].y;
    if (new_dx < 0.0) {
      posicion[particula].y      = b_min.y + new_dx;
      velocidad[particula].y     = -velocidad[particula].y;
      suavizado_vec[particula].y = -suavizado_vec[particula].y;
    }
  }
}

// Colisiones con los límites en el eje z [pg. 10]
void Calculadora::interacciones_limite_eje_z(int particula, std::vector<Vector3d> posicion,
                                             std::vector<Vector3d> velocidad,
                                             std::vector<Vector3d> suavizado_vec) {
  double new_dx;
  int const c_x = Calculadora::indice_bloque(posicion[particula]).z;
  if (c_x == 0) {
    new_dx = posicion[particula].z - b_min.z;
    if (new_dx < 0.0) {
      posicion[particula].z      = b_min.z - new_dx;
      velocidad[particula].z     = -velocidad[particula].z;
      suavizado_vec[particula].z = -suavizado_vec[particula].z;
    }
  } else if (c_x == Calculadora::num_bloques_por_eje(b_max.z, b_min.z) - 1) {
    new_dx = b_max.z - posicion[particula].z;
    if (new_dx < 0.0) {
      posicion[particula].z      = b_min.z + new_dx;
      velocidad[particula].z     = -velocidad[particula].z;
      suavizado_vec[particula].z = -suavizado_vec[particula].z;
    }
  }
}