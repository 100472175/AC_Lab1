#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

struct Particle {
    float posx, posy, posz;
    float hvx, hvy, hvz;
    float velx, vely, vlez;
};

int main(int argc, char** argv) {
    std::ifstream file(argv[1], std::ios::binary);

    if (!file) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    float ppm;
    int32_t np;

    // Leer la cabecera
    file.read(reinterpret_cast<char*>(&ppm), sizeof(float));
    file.read(reinterpret_cast<char*>(&np), sizeof(int32_t));

    std::cout << "FILE: " << argv[1] << std::endl;
    std::cout << "==============\n";
    std::cout << "particulas por metro: " << ppm << std::endl;
    std::cout << "numero de particulas: " << np << "\n==============\n";

    for (int32_t i = 0; i < np; ++i) {
        Particle p;
        file.read(reinterpret_cast<char*>(&p), sizeof(Particle));

        std::cout << "***********" << std::endl;
        std::cout << "Particula: " << i << std::endl;
        std::cout << "Position (x, y, z): " << p.posx << ", " << p.posy << ", " << p.posz << std::endl;
        std::cout << "hv (x, y, z): " << p.hvx << ", " << p.hvy << ", " << p.hvz << std::endl;
        std::cout << "Velocity (x, y, z): " << p.velx << ", " << p.vely << ", " << p.vlez << std::endl;
        std::cout << "***********" << std::endl;
    }

    file.close();

    return 0;
}
