//
// Created by Eduardo Alarcon on 27/9/23.
//

#ifndef PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
#define PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP

namespace func_fis {
    double masa(double densidad, double particula_por_metro);

    double suavizado(double radio, double part_por_metro);

    double num_bloques(double max, double min, double suavizado);

    double tamanio_bloque(double max, double min, double suavizado);

    double check_index(double index);

    double indice_bloque(double posicion, double min, double tamano_bloque);

    double delta_densidades(double len_suavizado, struct pos_part_1, struct pos_part_2);

    double transform_densidad(double densidad, double suavizado, double masa);
}
#endif //PRUEBAS_FLUIDOS_FUNCIONES_FISICAS_HPP
