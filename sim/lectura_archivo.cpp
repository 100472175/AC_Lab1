//
// Created by cesar on 27/09/23.
//

#include "lectura_archivo.hpp"

int read_file(const std::string &path, std::vector<particle>& particles) {
    std::cout << "reading file...\n";
    particles.clear();
    float float_ppm;
    double ppm;
    int np;
    std::ifstream file(path, std::ios::binary);
    // cabecera
    file.read(reinterpret_cast<char *> (&float_ppm), 4);
    file.read(reinterpret_cast<char *>(&np), 4);

    ppm = (double) float_ppm;

    std::cout << "ppm: " << ppm << "\n" << "np: " << np << "\n";
    for (int i = 0; i < np; i++) {
        float particle_data[9];
        particle p;
        file.read(reinterpret_cast<char *>(particle_data), 36); // lectura de particulas +1

        p.density = 0;
        p.id = i;
        p.px = (double) particle_data[0];
        p.py = (double) particle_data[1];
        p.pz = (double) particle_data[2];
        p.hx = (double) particle_data[3];
        p.hy = (double) particle_data[4];
        p.hz = (double) particle_data[5];
        p.vx = (double) particle_data[6];
        p.vy = (double) particle_data[7];
        p.vz = (double) particle_data[8];

        particles.push_back(p);
    }


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