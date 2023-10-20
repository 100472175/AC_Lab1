

#include "progargs.hpp"

// Created by paula on 29/09/23.

void add_particulas(Simulacion & simulacion, Vector3d<double> p, Vector3d<double> hv, Vector3d<double> v) {
    simulacion.particulas.posicion.push_back(p.to_double());
    simulacion.particulas.gradiente.push_back(hv.to_double());
    simulacion.particulas.velocidad.push_back(v.to_double());
    simulacion.particulas.densidad.push_back(0.0);
    simulacion.particulas.aceleracion.push_back(Vector3d<double>(0.0, -9.8, 0.0));
}

int Progargs::read_till_end(int num_particulas, int leidas) {
    while (archivo_entrada.gcount() > 0) {
        Vector3d<Vector3d<float>> dummy(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(0.0, 0.0, 0.0),
                                        Vector3d<float>(0.0, 0.0, 0.0));
        archivo_entrada.read(reinterpret_cast<char *>(&dummy), 36);
        if (archivo_entrada.gcount() > 0) leidas++;
    }
    if (leidas > num_particulas) {
        //num_particles < particulas
        std::cerr << "Error: Number of particles mismatch. Header: " << num_particulas
                  << ", Found: " << leidas << "\n";
        return -5;
    }
    return 0;
}

int Progargs::getter_num_iteraciones() const {
    return numero_iteraciones;
}

int Progargs::asignar_valores(std::vector<std::string> const &args) {
    if (args.size() != 3) {
        std::cerr << "Error: invalid number of arguments: " << args.size() << ".\n";
        return -1;
    };
    int const validar_iteraciones = my_is_digit(args[0]);
    if (validar_iteraciones < 0) { return validar_iteraciones; }
    numero_iteraciones = validar_iteraciones;
    if(valida_entrada(args[1]) < 0){
        return -3;
    }
    if( valida_salida(args[2]) < 0){
        return -4;
    }
    return 0;
}

int Progargs::read_head(Malla &malla, Calculadora &calculadora) {
    float float_ppm;
    int num_particulas;

    archivo_entrada.read(reinterpret_cast<char *>(&float_ppm), 4);
    archivo_entrada.read(reinterpret_cast<char *>(&num_particulas), 4);
    if (num_particulas <= 0) {
        std::cerr << "Invalid number of particles: " << num_particulas << "\n";
        return -5;
    }
    calculadora.ppm = (double) float_ppm;
    calculadora.num_particulas = num_particulas;

    Vector3d<double> aux = calculadora.num_bloques_por_eje();

    malla.n_x = aux.x;
    malla.n_y = aux.y;
    malla.n_z = aux.z;

    return 0;
}

int Progargs::read_body(Simulacion &simulacion) {
    int leidas;
    for (leidas = 0; leidas < simulacion.num_particulas; leidas++) {
        Vector3d<float> p(0.0, 0.0, 0.0), hv(0.0, 0.0, 0.0), v(0.0, 0.0, 0.0);
        archivo_entrada.read(reinterpret_cast<char *>(&p), 12);  // lectura posicion particula i
        if (archivo_entrada.gcount() < 12) {
            // num_particles > particulas
            std::cerr << "Error: Number of particles mismatch. Header: " << simulacion.num_particulas
                      << ", Found: " << leidas << "\n";
            return -5;
        }
        archivo_entrada.read(reinterpret_cast<char *>(&hv), 12);  // lectura h particula i
        archivo_entrada.read(reinterpret_cast<char *>(&v), 12);   // lectura velocidad particula i
        add_particulas(simulacion, p.to_double(), hv.to_double(), v.to_double());

    }
    // comprobar que haya más partículas de las especificadas
    return read_till_end(simulacion.num_particulas, leidas);
}

int Progargs::valida_entrada(std::string const &argumento_entrada) {
    std::ifstream entrada(argumento_entrada);
    if (entrada.fail()) {
        std::cerr << "Error: Cannot open " << argumento_entrada << " for reading\n";
        return -3;
    }
    archivo_entrada = std::move(entrada);
    return 0;
}

int Progargs::valida_salida(std::string const &argumento_salida) {
    std::ofstream salida(argumento_salida, std::ios::binary);
    if (salida.fail()) {
        std::cerr << "Error: Cannot open " << argumento_salida << " for writing\n";
        return -4;
    }
    archivo_salida = std::move(salida);
    return 0;
}

int Progargs::write_file(double ppm, Simulacion &simulacion) {
    std::cout << "writing file...\n";
    /*
    std::ofstream file(archivo_salida, std::ios::binary);
    if (file.fail()) {
        std::cerr << "Error: Cannot open " << archivo_salida << "file\n";
        return -4;
    }*/
    float ppm_float = (float) ppm;
    archivo_salida.write(reinterpret_cast<char *>(&ppm_float), 4);
    archivo_salida.write(reinterpret_cast<char *>(&simulacion.num_particulas), 4);

    for (int i = 0; i < simulacion.num_particulas; ++i) {
        Vector3d<float> p = simulacion.particulas.posicion[i].to_float();
        Vector3d<float> hv = simulacion.particulas.gradiente[i].to_float();;
        Vector3d<float> v = simulacion.particulas.velocidad[i].to_float();;

        archivo_salida.write(reinterpret_cast<char *>(&p), 12);
        archivo_salida.write(reinterpret_cast<char *>(&hv), 12);
        archivo_salida.write(reinterpret_cast<char *>(&v), 12);
    }
    return 0;
}

int Progargs::my_is_digit(std::string const &string_to_try) {
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

Vector3d<int> Progargs::fuera_de_rango(Vector3d<int> indices) {
    if (indices.x < 0) {
        indices.x = 0;
    } else if (indices.x > 14) {
        indices.x = 14;
    }
    if (indices.y < 0) {
        indices.y = 0;
    } else if (indices.y > 20) {
        indices.y = 20;
    }
    if (indices.z < 0) {
        indices.z = 0;
    } else if (indices.z > 14) {
        indices.z = 14;
    }
    return indices;
}

// namespace Sim