//
// Created by paula on 27/09/23.
//
#include <cmath>
#include "../sim/lectura_archivo.hpp"
#include "../sim/progargs.hpp"
#include "../sim/particle.hpp"
#include "../sim/funciones_fisicas.hpp"
#include "../sim/Malla.hpp"

using namespace std;

double ppm;
int np;

double h;
const double r = 1.695;
const double dens_fluido = pow(10,3);
const double p_s = 3.0; //presion regidez
const double s_c = 3 * pow(10,4); //colision rigidez
const double d_v = 128.0; //amortiguamiento
const double mu = 0.4; //viscosidad
const double d_p = 2 * pow(10,-4); //tamaño particula
const double delta_t = pow(10,-3); //paso de tiempo
const Vector3d g = {0.0, 9.8, 0.0}; //vector de aceleraciones iniciales
const Vector3d b_min = {0.065, 0.1, 0.065};
const Vector3d b_max = {-0.065, -0.08, -0.065};
double m = func_fis::masa();

int main(int argc, char ** argv) {
  const int argument_validated = Sim::validate_arguments(argc, argv);
  if(argument_validated != 0){
    return argument_validated;
  }
  std::vector<Particle> particles;
  std::cout << "prev_size: " << particles.size() << std::endl;
  int prueba_error = read_file(argv[2], particles);
  if(prueba_error != 0){
    return prueba_error;
  }
  //hay que llamar a la funcion de valor antes de que sean usadas, o se usan con valor inf, como dependen de ppm las he puesto debajo de la lectura
  h = func_fis::suavizado();
  m = func_fis::masa();
  std::cout << "size: " << particles.size() << "\n";
  //población de una malla con las particulas iniciales
  Malla malla1;
  malla1.poblar_malla(particles);
  std::cout << "np: " << np << "\nppm: " << ppm << "\n";
  //Para que no toque el warning de unused variable
  //esto no hace nada, es para comprobar que no se rompe el programa:
  func_fis::init_densidad_accel(particles, 0);
  //por tener tipo auto en el return hace cosas raras, si se cambia tipo a int deja de dar errores, pero no se que tiene que devolver esto en el futuro?
  //func_fis::delta_densidades(0, 1,particles, particles);
  func_fis::transform_densidad(particles, 0);
  func_fis::trasnfer_accel_particulas(0, 1, particles, particles);
  std::cout << p_s << d_v << mu << g.x << g.y << g.z << m <<"\n";

  return 0;
}