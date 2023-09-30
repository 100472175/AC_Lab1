//
// Created by paula on 27/09/23.
//

#include "../sim/lectura_archivo.hpp"
#include "../sim/progargs.hpp"
#include "../sim/particle.hpp"
double ppm;
int np;


int main(int argc, char ** argv) {
  const int argument_validated = Sim::validate_arguments(argc, argv);
  if(argument_validated != 0){
    return argument_validated;
  }
  std::vector<Particle> particles;
  read_file(argv[2], particles);
  std::cout << "prev_size: " << particles.size() << std::endl;
  int i = 0;
  for (auto p : particles) {
    std::cout << "particle " << i++ << ":\n" << p.p.x << "\n";
    std::cout << "=========\n";
  }
    std::cout << "size: " << particles.size() << "\n";
  return 0;
}