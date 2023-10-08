

#include "progargs.hpp"

// Created by paula on 29/09/23.
//



    Progargs::Progargs(std::vector<std::string> const &args) {
        if (args.size() != 3) {
            std::cerr << "Error: invalid number of arguments: " << args.size() << ".\n";
            std::exit(-1);
        };
        numero_iteraciones = my_is_digit(args[0]);
        archivo_entrada = valida_entrada(args[1]);
        archivo_salida = valida_salida(args[2]);
    }

    int Progargs::read_head(Malla & malla, Calculadora & calculadora) {
        std::cout << "cabecera\n";
        float float_ppm;
        int num_particulas;
        archivo_entrada.read(reinterpret_cast<char *>(&float_ppm), 4);
        archivo_entrada.read(reinterpret_cast<char *>(&num_particulas), 4);
        std::cout << "ppm: " << float_ppm << "\n";
        std::cout << "np: " << num_particulas << "\n";
        calculadora.ppm = (double)float_ppm;
        calculadora.num_particulas = num_particulas;

        Vector3d aux = calculadora.num_bloques_por_eje();

        malla.n_x = aux.x;
        malla.n_y = aux.y;
        malla.n_z = aux.z;

        return 0;
    }

    int Progargs::read_body(Simulacion & simulacion) {
        // body
        simulacion.num_iteraciones = numero_iteraciones;
        std::cout << "body\n";
        for (int i = 0; i < simulacion.num_particulas; i++) {
            Vector3d_float p(0.0, 0.0, 0.0), hv(0.0, 0.0, 0.0), v(0.0, 0.0, 0.0);
            archivo_entrada.read(reinterpret_cast<char *>(&p), 12);  // lectura posicion particula i
            if (archivo_entrada.gcount() < 12) {
                std::cerr << "Error: Number of particles mismatch. Header: " << simulacion.num_particulas << ", Found: "
                          << i << "\n";
                return -5;
            }
            archivo_entrada.read(reinterpret_cast<char *>(&hv), 12);  // lectura h particula i
            archivo_entrada.read(reinterpret_cast<char *>(&v), 12);   // lectura velocidad particula i

            simulacion.particulas.posicion.push_back(p.to_double());
            simulacion.particulas.suavizado.push_back(hv.to_double());
            simulacion.particulas.velocidad.push_back(v.to_double());
            simulacion.particulas.aceleracion.push_back(Vector3d(0.0, -9.8, 0.0));
        }
        return 0;
    }

    /*int Progargs::read_file(Simulacion &simulacion) {
        // head
        simulacion.num_iteraciones = numero_iteraciones;
        std::cout << "reading file...\n";
        std::ifstream file(archivo_entrada, std::ios::binary);
        if (file.fail()) {
            std::cerr << "Error: Cannot open " << archivo_entrada << " for reading\n";
            return -3;
        }
        read_head(file, simulacion);
        read_body(file, simulacion);
        int exit_code = read_body(file, simulacion);
        if (exit_code == -5) { return -5; }

        file.close();
        return 0;
    }*/

    std::ifstream Progargs::valida_entrada(const std::string& argumento_entrada){
        std::ifstream entrada(argumento_entrada);
        if (entrada.fail()) {
            std::cerr << "Error: Cannot open " << argumento_entrada << " for reading\n";
            std::exit(-3);
        }
        return entrada;
    }

    std::ofstream Progargs::valida_salida(const std::string& argumento_salida){
        std::ofstream salida(argumento_salida, std::ios::binary);
        if (salida.fail()) {
            std::cerr << "Error: Cannot open " << argumento_salida << " for writing\n";
            std::exit(-4);
        }
        return salida;
    }

    int Progargs::write_file(Simulacion & simulacion) {
        std::cout << "writing file...\n";
        /*
        std::ofstream file(archivo_salida, std::ios::binary);
        if (file.fail()) {
            std::cerr << "Error: Cannot open " << archivo_salida << "file\n";
            return -4;
        }*/
        float ppm_float = (float)simulacion.ppm;
        archivo_salida.write(reinterpret_cast<char *>(&ppm_float), 4);
        archivo_salida.write(reinterpret_cast<char *>(&simulacion.num_particulas), 4);

        for (int i = 0; i < simulacion.num_particulas; ++i) {
            Vector3d_float p = simulacion.particulas.posicion[i].to_float();
            Vector3d_float hv = simulacion.particulas.suavizado[i].to_float();;
            Vector3d_float v = simulacion.particulas.velocidad[i].to_float();;

            archivo_salida.write(reinterpret_cast<char *>(&p), 12);
            archivo_salida.write(reinterpret_cast<char *>(&hv), 12);
            archivo_salida.write(reinterpret_cast<char *>(&v), 12);
        }
        return 0;
    }

    int Progargs::my_is_digit(std::string const &string_to_try) {
        for (int i = 1; i < int(string_to_try.length()); i++) {
            if (std::isdigit(string_to_try[i]) == 0) {
                std::cerr << "Error: time steps must be numeric.\n";
                std::exit(-1);
            }
        }
        if (string_to_try[0] == '-') {
            std::cerr << "Error: Invalid number of time steps.\n";
            std::exit(-2);
        }
        if (std::isdigit(string_to_try[0]) != 1) { return -1; }
        return stoi(string_to_try);
    }

    /*
    int validate_arguments(int num_args, char ** args) {
      if (num_args != 4) {
        std::cerr << "Error: invalid number of arguments: " << num_args - 1 << ".\n";
        return -1;
      }
      int first_argument_validation = my_is_digit(args[1]);
      if (first_argument_validation != 0) { return first_argument_validation; }
      return 0;
    }*/

    Vector3d_int Progargs::fuera_de_rango(Vector3d_int indices) {
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