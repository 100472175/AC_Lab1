//
// Created by paula on 27/09/23.
//
#include "../sim/funciones_fisicas.hpp"
#include "../sim/lectura_archivo.hpp"
#include "../sim/Malla.hpp"
#include "../sim/particle.hpp"
#include "../sim/progargs.hpp"

#include <cmath>
#include <span>

#include "../sim/constantes.hpp"



double ppm;
int num_particulas;
double suavizado;
double masa;

int main(int argc, char ** argv) {
  std::span const args_span(argv, static_cast<std::size_t>(argc));
  std::vector<std::string> const argumentos(args_span.begin() +1, args_span.end());

  Sim::Progargs const nuestros_args{argumentos};

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
  std::cout << p_s << d_v << viscosidad << gravedad.x << gravedad.y << gravedad.z << masa << "\n";



  return 0;
}