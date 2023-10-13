#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

struct Particle {
    int64_t id;
    double posx, posy, posz;
    double hvx, hvy, hvz;
    double velx, vely, vlez;
    double density;
    double accx, accy, accz;
};

void printParticle(const Particle& particle) {
    std::cout << "ID: " << particle.id << std::endl;
    std::cout << "Position (x, y, z): " << particle.posx << ", " << particle.posy << ", " << particle.posz << std::endl;
    std::cout << "hv (x, y, z): " << particle.hvx << ", " << particle.hvy << ", " << particle.hvz << std::endl;
    std::cout << "Velocity (x, y, z): " << particle.velx << ", " << particle.vely << ", " << particle.vlez << std::endl;
    std::cout << "Density: " << particle.density << std::endl;
    std::cout << "Acceleration (x, y, z): " << particle.accx << ", " << particle.accy << ", " << particle.accz << std::endl;
}

int main(int argc, char** argv) {
    std::ifstream file(argv[1], std::ios::binary);

    if (!file) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }
    std::cout << "FILE: " << argv[1] << "\n";

    int32_t totalBlocks;
    file.read(reinterpret_cast<char*>(&totalBlocks), sizeof(int32_t));
    std::cout << "==============\nnum_bloques: " << totalBlocks << "\n==============\n";
    for (int32_t block = 0; block < totalBlocks; ++block) {
        int64_t numParticles;
        file.read(reinterpret_cast<char*>(&numParticles), sizeof(int64_t));
        std::cout << "Bloque: " << block << "\n";
        std::cout <<"Particles in the block: " << numParticles << "\n";

        for (int64_t particle = 0; particle < numParticles; ++particle) {
            std::cout << "***********\n";
            std::cout << "Particula: " << particle << "\n";
            Particle p;
            file.read(reinterpret_cast<char*>(&p), sizeof(Particle));
            printParticle(p);
            std::cout << "***********\n";

        }
    }

    file.close();

    return 0;
}
