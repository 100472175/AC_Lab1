//
// Created by paula on 27/09/23.
//
#include "../sim/calculadora.hpp"
#include "../sim/malla.hpp"
#include "../sim/progargs.hpp"
#include "../sim/simulacion.hpp"

#include <cmath>
#include <span>


// Esto es de Debug, para unas pruebas xd
void imprime_datos_particula(Simulacion simulacion, int indice) {
  std::cout << "Posición de la partícula " << indice << "\n";
  std::cout << "particula: " << simulacion.particulas.posicion[indice].x << ", "
            << simulacion.particulas.posicion[indice].y << ", "
            << simulacion.particulas.posicion[indice].z << "\n";
  std::cout << "Velocidad: de la partícula " << indice << "\n";
  std::cout << "particula 53: " << simulacion.particulas.velocidad[indice].x << ", "
            << simulacion.particulas.velocidad[indice].y << ", "
            << simulacion.particulas.velocidad[indice].z << "\n";
  std::cout << "Aceleración: de la partícula " << indice << "\n";
  std::cout << "particula 53: " << simulacion.particulas.aceleracion[indice].x << ", "
            << simulacion.particulas.aceleracion[indice].y << ", "
            << simulacion.particulas.aceleracion[indice].z << "\n";
  std::cout << "Gradiente de la partícula " << indice << "\n";
  std::cout << "particula 53: " << simulacion.particulas.gradiente[indice].x << ", "
            << simulacion.particulas.gradiente[indice].y << ", "
            << simulacion.particulas.gradiente[indice].z << "\n";
  std::cout << "Densidad de la partícula " << indice << "\n";
  std::cout << "particula 53 densidad: " << simulacion.particulas.densidad[indice] << "\n";
  std::cout << "\n\n\n\n\n";
}

int main(int argc, char ** argv) {
  std::span const args_span(argv, static_cast<std::size_t>(argc));
  std::vector<std::string> const argumentos(args_span.begin() + 1, args_span.end());

  Progargs nuestros_args{argumentos};

  Malla malla{};
  Calculadora calc{};

  nuestros_args.read_head(malla, calc);

  calc.inicializar_calculadora();
  malla.inicializar_malla(calc.num_bloques_por_eje());
  Simulacion simulacion;
  simulacion.num_particulas = calc.num_particulas;
  simulacion.ppm            = calc.ppm;
  simulacion.calculadora    = calc;
  simulacion.malla          = malla;

  nuestros_args.read_body(simulacion);
  simulacion.print_simulation_parameters();
  imprime_datos_particula(simulacion, 53);
  simulacion.iterador();
  imprime_datos_particula(simulacion, 53);

  std::cout << "\n\n=====DEBUG====\n";
  nuestros_args.write_file(simulacion);
  std::cout << "particula 53: " << simulacion.particulas.posicion[53].x << ", "
            << simulacion.particulas.posicion[53].y << ", " << simulacion.particulas.posicion[53].z
            << "\n";
  std::cout << "particula 3000.pos: " << simulacion.particulas.posicion[3000].x << ", "
            << simulacion.particulas.posicion[3000].y << ", " << simulacion.particulas.posicion[3000].z
            << "\n";
  std::cout << "particula 3000.grad: " << simulacion.particulas.gradiente[3000].x << ", "
            << simulacion.particulas.gradiente[3000].y << ", " << simulacion.particulas.gradiente[3000].z
            << "\n";
  std::cout << "particula 3000.acel: " << simulacion.particulas.aceleracion[3000].x << ", "
            << simulacion.particulas.aceleracion[3000].y << ", " << simulacion.particulas.aceleracion[3000].z
            << "\n";

  /*
  std::cout << "Ejecutando las partes 4.3.2 -> 4.3.5 \n";
  for (int i = 0; i < simulacion.num_particulas; i++) {
    // simulacion.reposicionamiento();
    simulacion.colisiones_particulas();
    simulacion.colisiones_particulas_densidad();
    simulacion.colisiones_particulas_aceleracion();
    simulacion.colision_particula_limite();
    simulacion.movimiento_particulas();
    simulacion.rebote_particula_limite();
    }
  //simulacion.print_simulation_parameters();
  std::cout << "=====FIN DEBUG====\n";*/



  /*
      //int const argument_validated = Sim::validate_arguments(argc, argv);
      //if (argument_validated != 0) { return argument_validated; }
      std::vector<Particle> particles;
      std::cout << "prev_size: " << particles.size() << "\n";
      int prueba_error = read_file(argv[2], particles);
      int err_escritura = write_file(argv[3], particles, num_particulas, (float)ppm);
      if (prueba_error != 0 || err_escritura != 0) { return prueba_error; }
      // hay que llamar a la funcion de valor antes de que sean usadas, o se usan con valor inf,
     como
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
      // por tener tipo auto en el return hace cosas raras, si se cambia tipo a int deja de dar
     errores, func_fis::delta_densidades(0, 1, particles, particles);
      func_fis::transform_densidad(particles, 0);
      func_fis::trasnfer_accel_particulas(0, 1, particles, particles);
      std::cout << p_s << d_v << viscosidad << gravedad.x << gravedad.y << gravedad.z << masa <<
     "\n";*/

  return 0;
}

