//
// Created by Eduardo Alarcon on 27/9/23.
//
/*
#include "funciones_fisicas.hpp"
#include "lectura_archivo.hpp"
#include <numbers>

namespace func_fis {
    double masa(double densidad, double particula_por_metro) {
        return densidad * particula_por_metro;
    }
    double suavizado(double radio, double part_por_metro) {
        return radio / part_por_metro;
    }
    double num_bloques(double max, double min, double suavizado) {
        return floor((max - min) / suavizado);
    }
    double tamanio_bloque(double max, double min, double suavizado) {
        return (max - min) / num_bloques(max, min, suavizado);
    }
    double check_index(double index){
        if (index < 0) {
            return -1;
        }else{
            return index;
        }
    }
    double indice_bloque(double posicion, double min, double tamano_bloque) {
        return check_index(floor((posicion - min) / tamano_bloque));
    }

    double delta_densidades(double len_suavizado, particle const& part1, particle const& part2){
        double suavizado = len_suavizado * len_suavizado;
        double distancia = pow((part1.px - part2.px), 2) + pow((part1.py - part2.py), 2) + pow((part1.pz - part2.pz), 2);
        distancia = sqrt(distancia);
        distancia = distancia * distancia;
        if (distancia >= suavizado){
            return 0;
        }else{
            return pow((suavizado - distancia), 3);
        }
    }

    double transform_densidad(particle const& particula, double suavizado, double masa){
        double parte_1 = particula.density + pow(suavizado, 6);
        double parte_2 = 315/(64* std::numbers::pi *pow(suavizado, 9));
        //double parte_3 = masa;
        return parte_1 * parte_2 * masa;
    }

    double transfer_accel(particle const& part_1, particle const& part_2){


    }
    // Para acceder a la partícula p.px, p.py, p.pz
}
*/