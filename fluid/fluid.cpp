//
// Created by paula on 27/09/23.
//
#include "../sim/progargs.hpp"
#include "../sim/simulacion.hpp"
#include "../sim/malla.hpp"
#include "../sim/calculadora.hpp"
#include "../sim/calculadora.hpp"

#include <cmath>
#include <span>

int main(int argc, char ** argv) {
    std::span const args_span(argv, static_cast<std::size_t>(argc));
    std::vector<std::string> const argumentos(args_span.begin() +1, args_span.end());

    Progargs nuestros_args{argumentos};

    Malla malla{};
    Calculadora calc{};

    nuestros_args.read_head(malla, calc);
    Simulacion simulacion;
    simulacion.num_particulas = calc.num_particulas;
    simulacion.ppm = calc.ppm;
    simulacion.calculadora = calc;
    simulacion.malla = malla;
    nuestros_args.read_body(simulacion);
    nuestros_args.write_file(simulacion);
    std::cout << simulacion.ppm << "\n" << simulacion.num_particulas << "\n";
    std::cout << simulacion.particulas.posicion[53].x << ", " << simulacion.particulas.posicion[53].y << ", " << simulacion.particulas.posicion[53].z << "\n";

/*
    //int const argument_validated = Sim::validate_arguments(argc, argv);
    //if (argument_validated != 0) { return argument_validated; }
    std::vector<Particle> particles;
    std::cout << "prev_size: " << particles.size() << "\n";
    int prueba_error = read_file(argv[2], particles);
    int err_escritura = write_file(argv[3], particles, num_particulas, (float)ppm);
    if (prueba_error != 0 || err_escritura != 0) { return prueba_error; }
    // hay que llamar a la funcion de valor antes de que sean usadas, o se usan con valor inf, como
    // dependen de ppm las he puesto debajo de la lectura
    suavizado = func_fis::suavizado_calc();
    masa      = func_fis::masa_calc();
    std::cout << "size: " << particles.size() << "\n";
    // población de una malla con las particulas iniciales
    Malla malla1;
    malla1.poblar_malla(particles);
    std::cout << "num_particulas: " << num_particulas << "\nppm: " << ppm << "\n";
    // esto no hace nada, es para comprobar que no se rompe el programa:
    func_fis::init_densidad_accel(particles, 0);
    // por tener tipo auto en el return hace cosas raras, si se cambia tipo a int deja de dar errores,
    func_fis::delta_densidades(0, 1, particles, particles);
    func_fis::transform_densidad(particles, 0);
    func_fis::trasnfer_accel_particulas(0, 1, particles, particles);
    std::cout << p_s << d_v << viscosidad << gravedad.x << gravedad.y << gravedad.z << masa << "\n";*/



    return 0;
}