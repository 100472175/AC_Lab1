
#include "tools_trazas.hpp"

#include <math.h>

#include <algorithm>
#include <array>

int load_trz(const std::string& path, Simulacion & sim) {
  int number_blocks = 0;
  int64_t particulas_block = 0;
  std::ifstream traza(path, std::ios::binary);
  traza.read(reinterpret_cast<char *>(&number_blocks), 4);
  int64_t ident = 0;
  Vector3d<double> pos{};
  Vector3d<double> grad{};
  Vector3d<double> vel{};
  Vector3d<double> acel{};
  double dens = 0.0;
  for (int i = 0; i < number_blocks; ++i) {
    traza.read(reinterpret_cast<char *>(&particulas_block), 8);
    sim.malla.bloques[i].particulas.clear();
    for (int j = 0; j < particulas_block; ++j) {


      traza.read(reinterpret_cast<char *>(&ident), 8);
      traza.read(reinterpret_cast<char *>(&pos), 24);
      traza.read(reinterpret_cast<char *>(&grad), 24);
      traza.read(reinterpret_cast<char *>(&vel), 24);
      traza.read(reinterpret_cast<char *>(&dens), 8);
      traza.read(reinterpret_cast<char *>(&acel), 24);

      sim.malla.bloques[i].particulas.push_back(ident);
      sim.particulas.pos[ident]         = pos;
      sim.particulas.gradiente[ident]   = grad;
      sim.particulas.velocidad[ident]   = vel;
      sim.particulas.dens[ident]        = dens;
      sim.particulas.aceleracion[ident] = acel;
    }
  }
  traza.close();
  return 0;
}

int write_trz(std::string const & path, Simulacion & sim) {
  std::ofstream salida(path, std::ios::binary);
  salida.write(reinterpret_cast<char *>(&sim.malla.tamano), 4);
  for (int i = 0; i < sim.malla.tamano; i++) {
    int64_t particulas = sim.malla.bloques[i].particulas.size();
    salida.write(reinterpret_cast<char *>(&particulas), 8);
    for (int j = 0; j < particulas; j++) {
      auto id_part = (int64_t) sim.malla.bloques[i].particulas[j];
      salida.write(reinterpret_cast<char *>(&id_part), 8);
      salida.write(reinterpret_cast<char *>(&sim.particulas.pos[id_part]), 24);
      salida.write(reinterpret_cast<char *>(&sim.particulas.gradiente[id_part]), 24);
      salida.write(reinterpret_cast<char *>(&sim.particulas.velocidad[id_part]), 24);
      salida.write(reinterpret_cast<char *>(&sim.particulas.dens[id_part]), 8);
      salida.write(reinterpret_cast<char *>(&sim.particulas.aceleracion[id_part]), 24);
    }
  }
  salida.close();
  return 0;
}

bool compareSims(Simulacion const & real, Simulacion const & expect, double const tolerancia) {
  if (real.malla.tamano != expect.malla.tamano) { return false; }
  for (int i = 0; i < real.malla.tamano; i++) {
    if (real.malla.bloques[i].particulas.size() != expect.malla.bloques[i].particulas.size()) {
      return false;
    }
    for (int j = 0; j < (int) real.malla.bloques[i].particulas.size(); j++) {
      if (real.malla.bloques[i].particulas[j] != expect.malla.bloques[i].particulas[j]) {
        return false;
      }
      int const ident = real.malla.bloques[i].particulas[j];
      Vector3d<double> const diff_pos =
          (Vector3d<double>::abs_diff(real.particulas.pos[ident], expect.particulas.pos[ident])) /
          expect.particulas.pos[ident];
      Vector3d<double> const diff_gradiente =
          (Vector3d<double>::abs_diff(real.particulas.gradiente[ident],
                                      expect.particulas.gradiente[ident])) /
          expect.particulas.gradiente[ident];
      Vector3d<double> const diff_velocidad =
          (Vector3d<double>::abs_diff(real.particulas.velocidad[ident],
                                      expect.particulas.velocidad[ident])) /
          expect.particulas.velocidad[ident];
      Vector3d<double> const diff_aceleracion =
          (Vector3d<double>::abs_diff(real.particulas.aceleracion[ident],
                                      expect.particulas.aceleracion[ident])) /
          expect.particulas.aceleracion[ident];
      double const diff_dens =
          std::abs(real.particulas.dens[ident] - expect.particulas.dens[ident]) /
          expect.particulas.dens[ident];
      if ((diff_pos.x > tolerancia) || (diff_pos.y > tolerancia) || (diff_pos.z > tolerancia)) {
        return false;
      }
      if ((diff_gradiente.x > tolerancia) || (diff_gradiente.y > tolerancia) ||
          (diff_gradiente.z > tolerancia)) {
        return false;
      }
      if ((diff_velocidad.x > tolerancia) || (diff_velocidad.y > tolerancia) ||
          (diff_velocidad.z > tolerancia)) {
        return false;
      }
      if ((diff_aceleracion.x > tolerancia) || (diff_aceleracion.y > tolerancia) ||
          (diff_aceleracion.z > tolerancia)) {
        return false;
      }
      if (diff_dens > tolerancia) { return false; }
    }
  }
  return true;
}

bool compareFiles(std::string const & p1, std::string const & p2) {
  std::ifstream fich1(p1, std::ifstream::binary);
  std::ifstream fich2(p2, std::ifstream::binary);

  if (fich1.fail() || fich2.fail()) {
    std::cout << "cannot open files";
    return false;  // file problem
  }
  fich1.seekg(0, std::ifstream::end);
  fich2.seekg(0, std::ifstream::end);
  size_t const lengh1 = fich1.tellg();
  size_t const lengh2 = fich2.tellg();
  std::cout << lengh1 << " " << lengh2 << "\n";
  if (lengh1 != lengh2) {
    std::cout << "size difference\n";
    return false;
  }

  fich1.seekg(0, std::ifstream::beg);
  fich2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(fich1.rdbuf()), std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(fich2.rdbuf()));
}
