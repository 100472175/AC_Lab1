//
// Created by cesar on 27/09/23.
//

#include "lectura_archivo.hpp"

int read_file(const std::string &path, std::vector<Particle> &particles) {
    std::cout << "reading file...\n";

    particles.clear();
    float float_ppm;
    double ppm;
    int np;
    std::ifstream file(path, std::ios::binary);
    // cabecera
    file.read(reinterpret_cast<char *>(&float_ppm), 4);
    file.read(reinterpret_cast<char *>(&np), 4);

    ppm = (double)float_ppm;

    std::cout << "ppm: " << ppm << "\n"
        << "np: " << np << "\n";


    for (int i = 0; i < np; i++) {
        Vector3d_float p;
        Vector3d_float h;
        Vector3d_float v;

        Particle particle;
        particle.densidad=0;
        particle.a.set_values(0.0, 9.8, 0.0);

        file.read(reinterpret_cast<char *>(&p),12); // lectura posicion particula i
        file.read(reinterpret_cast<char *>(&h),12); // lectura h particula i
        file.read(reinterpret_cast<char *>(&v),12); // lectura velocidad particula i

        particle.p.set_values((double)p.x, (double)p.y, (double)p.z);
        particle.h.set_values((double)h.x, (double)h.y, (double)h.z);
        particle.v.set_values((double)v.x, (double)v.y, (double)v.z);
        particles.push_back(particle);
    }

    std::cout << "Almacenadas " << particles.size() << "particulas\n";

    return 0;
}
/*
int main() {
    std::vector<particle> particles;
    std::cout << "size: " << particles.size() << "\n";
    read_file("small.fld", &particles);
    std::cout << "size: " << particles.size() << "\n";

    return 0;
}*/