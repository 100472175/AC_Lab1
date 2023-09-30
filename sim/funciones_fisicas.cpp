//
// Created by Eduardo Alarcon on 27/9/23.
//
#include <iostream>
#include "funciones_fisicas.hpp"
#include "vector_3d.hpp"

namespace func_fis {
  double masa_part = masa();
  double len_suavizado = suavizado();
}

// Sección 3.5 - La malla de simulación
double func_fis::masa() {
  return dens_fluido / pow(ppm, 3);
}

double func_fis::suavizado() {
    h = r/ppm;
    return r / ppm;
}

double func_fis::num_bloques(double const& max, double const& min) {
    return floor((min - max) / h);
}

double func_fis::tamanio_bloque(double const& max, double const& min) {
    return (max - min) / num_bloques(max, min);
}

int func_fis::check_index(int index){
    if (index < 0) { return -1; }
    return index;
}

Vector3d_int func_fis::indice_bloque(Particle const& particula) {
    int coord_x = floor((particula.p.x - b_min.x) / func_fis::tamanio_bloque(b_max.x, b_min.x));
    int coord_y = floor((particula.p.y - b_min.y) / func_fis::tamanio_bloque(b_max.y, b_min.y));
    int coord_z = floor((particula.p.z - b_min.z) / func_fis::tamanio_bloque(b_max.z, b_min.z));
    Vector3d_int result{coord_x, coord_y, coord_z};
    return result;
}

// Sección 4.3.1 - Cálculo de las aceleraciones

// Inidiación de densidad y aceleraciones [pg. 8]
void func_fis::init_densidad_accel(std::vector<Particle> &new_vector, int particula){
    new_vector[particula].densidad = 0.0;
    //new_vector[particula].a = Vector3D(0.0, 0.0, 0.0);
}

// Incremento de densidades [pg. 8]
auto func_fis::delta_densidades(int particula1, int particula2, std::vector<Particle> &old_vector, std::vector<Particle> &new_vector){
    if ((particula1 > particula2) or (particula1 == particula2)) { return 0.0; }

    double suavizado = len_suavizado * len_suavizado;
    double distancia = old_vector[particula1] || old_vector[particula2];
    if (distancia >= suavizado) { return 0.0; }
    double diff_densidad =  pow((suavizado - distancia), 3);
    new_vector[particula1].densidad += diff_densidad;
    new_vector[particula2].densidad += diff_densidad;
    return 1.0;
}

// Transformación de densidad [pg. 8]
double func_fis::transform_densidad(std::vector<Particle> &new_vector, int particula){
    double parte_1 = new_vector[particula].densidad + pow(len_suavizado, 6);
    double parte_2 = 315/(64 * std::numbers::pi *pow(len_suavizado, 9));
    return parte_1 * parte_2 * masa_part;
}

// Transferencia de aceleración [pg. 8]
double func_fis::trasnfer_accel_particulas(int particula1, int particula2, std::vector<Particle> &old_vector, std::vector<Particle> &new_vector){
    if ((particula1 > particula2) or (particula1 == particula2)) { return -1.0; }
    //Distancia entre dos partículas 3 dimensionales
    double distancia = old_vector[particula1] || old_vector[particula2];
    if (distancia >= pow(len_suavizado, 2)) { return 0.0; }

    //Aceleración entre dos partículas 3 dimensionales
    Vector3d diff_posiciones = old_vector[particula1].p - old_vector[particula2].p;

    double acceleration_2 = 15 / (std::numbers::pi * pow(len_suavizado, 6)) * masa_part *
                            pow(len_suavizado - distancia, 2) / distancia;
    double acceleration_3 = old_vector[particula1].densidad + old_vector[particula2].densidad - dens_fluido;
    Vector3d acceleration_4 = old_vector[particula2].v - old_vector[particula1].v;
    double acceleration_5 = 45 / (std::numbers::pi * pow(len_suavizado, 6)) * masa_part;
    double acceleration_div = old_vector[particula1].densidad * old_vector[particula2].densidad;

    // Primera parte de la aceleración
    diff_posiciones *= acceleration_2 * acceleration_3;
    // Segunda parte de la aceleración
    acceleration_4 *= acceleration_5;
    // Suma de las dos partes de la aceleración
    diff_posiciones += acceleration_4;
    // División de la aceleración
    diff_posiciones /= acceleration_div;
    // Suma de la aceleración a la partícula 1
    new_vector[particula1].a += diff_posiciones;
    new_vector[particula2].a -= diff_posiciones;
    return 1.0;
}

// Sección 4.3.3 Colisiones de partículas
// Colisiones con los límites del eje  x [pg. 9]
void func_fis::collisiones_limite_eje_x(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector){
    double new_x = old_vector[particula].p.x + old_vector[particula].v.x * delta_t;
    double delta_x;
    if (c_x == 0){
        delta_x = d_p - (new_x - b_min.x);
        if (delta_x > pow(10, -10)) {
          new_vector[particula].a.x = old_vector[particula].a.x + s_c * delta_x - d_v * old_vector[particula].v.x;
        }
    } else if (c_x == func_fis::num_bloques(b_max.x, b_min.x) - 1) {
        delta_x = d_p - (b_max.x - new_x);
        if (delta_x > pow(10, -10)) {
          new_vector[particula].a.x = old_vector[particula].a.x - s_c * delta_x + d_v * old_vector[particula].v.x;
        }
    }
}

// Colisiones con los límites del eje y [pg. 10]
void func_fis::collisiones_limite_eje_y(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector){
    double new_y = old_vector[particula].p.y + old_vector[particula].v.y * delta_t;
    double delta_y;
    if (c_x == 0){
        delta_y = d_p - (new_y - b_min.y);
        if (delta_y > pow(10, -10)) {
          new_vector[particula].a.y = old_vector[particula].a.y + s_c * delta_y - d_v * old_vector[particula].v.y;
        }
    } else if (c_x == func_fis::num_bloques(b_max.y, b_min.y) - 1) {
        delta_y = d_p - (b_max.y - new_y);
        if (delta_y > pow(10, -10)) {
          new_vector[particula].a.y = old_vector[particula].a.y - s_c * delta_y + d_v * old_vector[particula].v.y;
        }
    }
}

// Colisiones con los límites del eje z [pg. 10]
void func_fis::collisiones_limite_eje_z(int c_z, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector){
    double new_z = old_vector[particula].p.z + old_vector[particula].v.z * delta_t;
    double delta_z;
    if (c_z == 0){
        delta_z = d_p - (new_z - b_min.z);
        if (delta_z > pow(10, -10)) {
          new_vector[particula].a.z = old_vector[particula].a.z + s_c * delta_z - d_v * old_vector[particula].v.z;
        }
    } else if (c_z == func_fis::num_bloques(b_max.z, b_min.z) - 1) {
        delta_z = d_p - (b_max.z - new_z);
        if (delta_z > pow(10, -10)) {
          new_vector[particula].a.z = old_vector[particula].a.z - s_c * delta_z + d_v * old_vector[particula].v.z;
        }
    }
}
/*
// 4.3.5 Interacciones con los límites del recinto
// Colisiones con los límites en el eje x [pg. 10]
void func_fis::colisiones_limite_eje_x(int c_x, int particula, std::vector<Particle> const& old_vector, std::vector<Particle> &new_vector){
    double new_dx;
    if (c_x == 0){
        new_dx = old_vector[particula].p.x - b_min.x;
    }
}
*/















