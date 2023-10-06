//
// Created by cesar on 27/09/23.
//

#include "lectura_archivo.hpp"

int read_head(std::ifstream & file) {
  std::cout << "cabecera\n";
  float float_ppm;
  file.read(reinterpret_cast<char *>(&float_ppm), 4);
  file.read(reinterpret_cast<char *>(&num_particulas), 4);
  ppm = (double) float_ppm;
  return 0;
}

int read_body(std::ifstream & file, std::vector<Particle> & particles) {
  // body
  std::cout << "body\n";
  for (int i = 0; i < num_particulas; i++) {
    Vector3d_float p(0.0, 0.0, 0.0), hv(0.0, 0.0, 0.0), v(0.0, 0.0, 0.0);
    Particle particle;
    particle.densidad = 0.0;
    particle.a.set_values(0.0, 9.8, 0.0);
    file.read(reinterpret_cast<char *>(&p), 12);  // lectura posicion particula i
    if (file.gcount() < 12) {
      std::cerr << "ERROR: MENOS PARTÍCULAS DE LAS ESPERADAS " << num_particulas << " > " << i
                << "\n";
      return -5;
    }
    file.read(reinterpret_cast<char *>(&hv), 12);  // lectura h particula i
    file.read(reinterpret_cast<char *>(&v), 12);   // lectura velocidad particula i
    particle.p.set_values((double) p.x, (double) p.y, (double) p.z);
    particle.hv.set_values((double) hv.x, (double) hv.y, (double) hv.z);
    particle.v.set_values((double) v.x, (double) v.y, (double) v.z);
    particles.push_back(particle);
  }
  return 0;
}

int read_file(std::string const & path, std::vector<Particle> & particles) {
  // head
  std::cout << "reading file...\n";
  std::ifstream file(path, std::ios::binary);
  if (file.fail()) {
    std::cerr << "Error: Cannot open " << path << " for reading\n";
    return -3;
  }
  read_head(file);
  int exit_code = read_body(file, particles);
  if (exit_code == -5) { return -5; }

  file.close();
  return 0;
}

int write_file(const std::string &path, std::vector<Particle> &particles, int number_of_particles, float particles_per_meter) {
    std::cout << "writing file...\n";
    std::ofstream file(path, std::ios::binary);
    if (file.fail()) {
        std::cerr << "Error: Cannot open " << path << "file\n";
        return -4;
    }
    file.write(reinterpret_cast<char*>(&particles_per_meter), 4);
    file.write(reinterpret_cast<char*>(&number_of_particles), 4);

    for (int i = 0; i < number_of_particles; ++i) {
        Vector3d_float p = particles[i].p.to_float();
        Vector3d_float hv = particles[i].hv.to_float();
        Vector3d_float v = particles[i].v.to_float();

        file.write(reinterpret_cast<char*>(&p), 12);
        file.write(reinterpret_cast<char*>(&hv), 12);
        file.write(reinterpret_cast<char*>(&v), 12);
    }

    return 0;
}
