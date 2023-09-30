//
// Created by Eduardo Alarcon on 27/9/23.
//

#include "funciones_fisicas.hpp"


double func_fis::masa() {
  return dens_fluido * pow(ppm, 3);
}

double func_fis::suavizado() {
    return r / ppm;
}

double func_fis::num_bloques(double const& max, double const& min, double const& suavizado) {
    return floor((max - min) / suavizado);
}

double func_fis::tamanio_bloque(double const& max, double const& min, double const& suavizado) {
    return (max - min) / num_bloques(max, min, suavizado);
}

int func_fis::check_index(int index){
    if (index < 0) { return -1; }
    return index;
}

int func_fis::indice_bloque(double const& posicion, double const& min, double const& tamanio_bloque) {
    return check_index(floor((posicion - min) / tamanio_bloque));
}

void func_fis::init_dens_accel(std::vector<Particle> &new_vector, int particula){
    new_vector[particula].densidad = 0.0;
    //new_vector[particula].a = Vector3D(0.0, 0.0, 0.0);
}

double func_fis::delta_densidades(double len_suavizado, Particle const& part1, Particle const& part2){
    double suavizado = len_suavizado * len_suavizado;
    double distancia = pow((part1.p.x - part2.p.x), 2);
    distancia = sqrt(distancia);
    distancia = distancia * distancia;
    if (distancia >= suavizado) { return 0; }
    return pow((suavizado - distancia), 3);
}

double func_fis::transform_densidad(Particle const& particula, double const& suavizado, double const& masa){
    double parte_1 = particula.densidad + pow(suavizado, 6);
    double parte_2 = 315/(64 * std::numbers::pi *pow(suavizado, 9));
    return parte_1 * parte_2 * masa;
}

