

#include "progargs.hpp"

// Created by paula on 29/09/23.

void add_particulas(Simulacion & simulacion, Vector3d<double> p, Vector3d<double> hv,
                    Vector3d<double> v) {
  simulacion.particulas.pos.push_back(p.to_double());
  simulacion.particulas.gradiente.push_back(hv.to_double());
  simulacion.particulas.velocidad.push_back(v.to_double());
  simulacion.particulas.dens.push_back(0.0);
  simulacion.particulas.aceleracion.push_back(gravedad);
}

int Progargs::read_till_end(int num_particulas, int leidas) {
  int const tamanio_lectura_part           = 36;
  int const error_number_particle_mismatch = -5;
  while (archivo_entrada.gcount() > 0) {
    Vector3d<Vector3d<float>> dummy(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(0.0, 0.0, 0.0),
                                    Vector3d<float>(0.0, 0.0, 0.0));
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    archivo_entrada.read(reinterpret_cast<char *>(&dummy), tamanio_lectura_part);
    if (archivo_entrada.gcount() > 0) { leidas++; }
  }
  if (leidas > num_particulas) {
    // num_particles < particulas
    std::cerr << "Error: Number of particles mismatch. Header: " << num_particulas
              << ", Found: " << leidas << "\n";
    return error_number_particle_mismatch;
  }
  return 0;
}

int Progargs::getter_num_iteraciones() const {
  return numero_iteraciones;
}

int Progargs::asignar_valores(std::vector<std::string> const & args) {
  if (args.size() != 3) {
    std::cerr << "Error: invalid number of arguments: " << args.size() << ".\n";
    return -1;
  };
  int const validar_iteraciones = my_is_digit(args[0]);
  if (validar_iteraciones < 0) { return validar_iteraciones; }
  numero_iteraciones = validar_iteraciones;
  if (valida_entrada(args[1]) < 0) { return -3; }
  if (valida_salida(args[2]) < 0) { return -4; }
  return 0;
}

int Progargs::read_head(Malla & malla, Calculadora & calculadora) {
  float float_ppm                          = 0;
  int num_particulas                       = 0;
  int const error_invalid_number_particles = -5;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  archivo_entrada.read(reinterpret_cast<char *>(&float_ppm), 4);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  archivo_entrada.read(reinterpret_cast<char *>(&num_particulas), 4);
  if (num_particulas <= 0) {
    std::cerr << "Invalid number of particles: " << num_particulas << "\n";
    return error_invalid_number_particles;
  }
  calculadora.ppm            = (double) float_ppm;
  calculadora.num_particulas = num_particulas;

  Vector3d<double> const aux = calculadora.num_bloques_por_eje();

  malla.n_x = int(aux.x);
  malla.n_y = int(aux.y);
  malla.n_z = int(aux.z);

  return 0;
}

int Progargs::read_body(Simulacion & simulacion) {
  int leidas                               = 0;
  int const error_number_particle_mismatch = -5;
  int const size_param                     = 12;
  for (leidas = 0; leidas < simulacion.num_particulas; leidas++) {
    Vector3d<float> pos(0.0, 0.0, 0.0);
    Vector3d<float> grad(0.0, 0.0, 0.0);
    Vector3d<float> vel(0.0, 0.0, 0.0);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    archivo_entrada.read(reinterpret_cast<char *>(&pos),
                         size_param);  // lectura posicion particula i
    if (archivo_entrada.gcount() < size_param) {
      // num_particles > particulas
      std::cerr << "Error: Number of particles mismatch. Header: " << simulacion.num_particulas
                << ", Found: " << leidas << "\n";
      return error_number_particle_mismatch;
    }
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    archivo_entrada.read(reinterpret_cast<char *>(&grad), size_param);  // lectura h particula i
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    archivo_entrada.read(reinterpret_cast<char *>(&vel), size_param);  // lectura vel particula i
    add_particulas(simulacion, pos.to_double(), grad.to_double(), vel.to_double());
  }
  // comprobar que haya más partículas de las especificadas
  return read_till_end(simulacion.num_particulas, leidas);
}

int Progargs::valida_entrada(std::string const & argumento_entrada) {
  std::ifstream entrada(argumento_entrada);
  if (entrada.fail()) {
    std::cerr << "Error: Cannot open " << argumento_entrada << " for reading\n";
    return -3;
  }
  archivo_entrada = std::move(entrada);
  return 0;
}

int Progargs::valida_salida(std::string const & argumento_salida) {
  std::ofstream salida(argumento_salida, std::ios::binary);
  if (salida.fail()) {
    std::cerr << "Error: Cannot open " << argumento_salida << " for writing\n";
    return -4;
  }
  archivo_salida = std::move(salida);
  return 0;
}

int Progargs::write_file(double ppm, Simulacion & simulacion) {
  std::cout << "writing file...\n";
  auto ppm_float       = (float) ppm;
  int const size_param = 12;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  archivo_salida.write(reinterpret_cast<char *>(&ppm_float), 4);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  archivo_salida.write(reinterpret_cast<char *>(&simulacion.num_particulas), 4);

  for (int i = 0; i < simulacion.num_particulas; ++i) {
    Vector3d<float> posicion  = simulacion.particulas.pos[i].to_float();
    Vector3d<float> gradiente = simulacion.particulas.gradiente[i].to_float();
    Vector3d<float> velocidad = simulacion.particulas.velocidad[i].to_float();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    archivo_salida.write(reinterpret_cast<char *>(&posicion), size_param);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    archivo_salida.write(reinterpret_cast<char *>(&gradiente), size_param);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    archivo_salida.write(reinterpret_cast<char *>(&velocidad), size_param);
  }
  archivo_salida.close();
  return 0;
}

int Progargs::my_is_digit(std::string const & string_to_try) {
  bool negativo = false;
  if (string_to_try[0] == '-') {
    negativo = true;
  } else if (std::isdigit(string_to_try[0]) == 0) {
    std::cerr << "Error: time steps must be numeric.\n";
    return -1;
  }
  for (int i = 1; i < int(string_to_try.length()); i++) {
    if (std::isdigit(string_to_try[i]) == 0) {
      std::cerr << "Error: time steps must be numeric.\n";
      return -1;
    }
  }
  if (negativo) {
    std::cerr << "Error: Invalid number of time steps.\n";
    return -2;
  }
  return stoi(string_to_try);
}
