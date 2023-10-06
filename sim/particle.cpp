//
// Created by cesar on 29/09/23.
//

#include "particle.hpp"

Particulas::Particulas() {
    std::vector<Vector3d> v_posicion;
    std::vector<Vector3d> v_suavizado;
    std::vector<Vector3d> v_velocidad;
    std::vector<Vector3d> v_aceleracion;
    std::vector<double> v_densidad;
    posicion = v_posicion;
    suavizado = v_suavizado;
    velocidad = v_velocidad;

}
