//
// Created by Eduardo Alarcon on 27/9/23.
//

#include "funciones_fisicas.hpp"
#include "vector_3d.hpp"

namespace func_fis {
  double masa_part = masa();
  double len_suavizado = suavizado();
}


double func_fis::masa() {
  return dens_fluido * pow(ppm, 3);
}

double func_fis::suavizado() {
    return r / ppm;
}

double func_fis::num_bloques(double const& max, double const& min) {
    return floor((max - min) / len_suavizado);
}

double func_fis::tamanio_bloque(double const& max, double const& min) {
    return (max - min) / num_bloques(max, min);
}

int func_fis::check_index(int index){
    if (index < 0) { return -1; }
    return index;
}

Vector3d func_fis::indice_bloque(double const& min, double const& tamanio_bloque, Particle const& particula) {
    int coord_x = floor((particula.p.x - min) / tamanio_bloque);
    int coord_y = floor((particula.p.y - min) / tamanio_bloque);
    int coord_z = floor((particula.p.z - min) / tamanio_bloque);
    Vector3d result{};
    result.set_values(coord_x, coord_y, coord_z);
    return result;
}

void func_fis::init_densidad_accel(std::vector<Particle> &new_vector, int particula){
    new_vector[particula].densidad = 0.0;
    //new_vector[particula].a = Vector3D(0.0, 0.0, 0.0);
}

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

double func_fis::transform_densidad(std::vector<Particle> &new_vector, int particula){
    double parte_1 = new_vector[particula].densidad + pow(len_suavizado, 6);
    double parte_2 = 315/(64 * std::numbers::pi *pow(len_suavizado, 9));
    return parte_1 * parte_2 * masa_part;
}


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


