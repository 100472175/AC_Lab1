//
// Created by paula on 27/09/23.
//
#include <cmath>
#include "../sim/lectura_archivo.hpp"
#include "../sim/progargs.hpp"
#include "../sim/particle.hpp"
#include "../sim/funciones_fisicas.hpp"


using namespace std;

double ppm;
int np;

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
double h = func_fis::suavizado();

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
  std::cout << "size: " << particles.size() << "\n";
  std::cout << "np: " << np << "\nppm: " << ppm << "\n";
  //Esto no iría aquí, es para probar ejecucion de cosas:
  func_fis::num_bloques(b_max.x, b_min.x, h);

  return 0;
}