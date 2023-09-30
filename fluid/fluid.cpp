//
// Created by paula on 27/09/23.
//

#include "../sim/lectura_archivo.hpp"
#include "../sim/progargs.hpp"
#include "../sim/particle.hpp"
#include <cmath>

using namespace std;
const double r = 1.695;
const double rho = pow(10,3);
const double p_s = 3.0;
const double s_c = 3 * pow(10,4);
const double d_v = 128.0;
const double mu = 0.4;
const double d_p = 2 * pow(10,-4);
const double delta_t = pow(10,-3);
const vector<double> g = {0.0, 9.8, 0.0};
const vector<double> b_min = {0.065, 0.1, 0.065};
const vector<double> b_max = {-0.065, -0.08, -0.065};
extern int ppm;
extern int np;
extern double m;
extern double h;

int main(int argc, char ** argv) {
  const int argument_validated = Sim::validate_arguments(argc, argv);
  if(argument_validated != 0){
    return argument_validated;
  }
  std::vector<Particle> particles;
  read_file(argv[2], particles);
  std::cout << "prev_size: " << particles.size() << std::endl;
  std::cout << "size: " << particles.size() << "\n";
  return 0;
}