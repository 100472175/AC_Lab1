//
// Created by cesar on 27/09/23.
//

#include <iostream>
#include "lectura_archivo.hpp"

int read_head(std::ifstream& file, int &np, double &ppm) {
    //std::cout << "cabecera\n";
    float float_ppm;
    file.read(reinterpret_cast<char *>(&float_ppm), 4);
    file.read(reinterpret_cast<char *>(&np), 4);
    ppm = (double)float_ppm;
    std::cout << "ppm y np: " << ppm << " " << np << "\n";
    return 0;
}

int read_body(std::ifstream& file, int &np, std::vector<Particle>& particles) {
    // body
    for (int i = 0; i < np; i++) {
        Vector3d_float p, h, v;
        Particle particle;
        particle.densidad=0;
        particle.a.set_values(0.0, 9.8, 0.0);
        file.read(reinterpret_cast<char *>(&p),12); // lectura posicion particula i
        if (file.gcount() < 12) {
            std::cerr << "ERROR: MENOS PARTÍCULAS DE LAS ESPERADAS " << np << " > " << i << "\n";
            return -5;
        }
        file.read(reinterpret_cast<char *>(&h),12); // lectura h particula i
        file.read(reinterpret_cast<char *>(&v),12); // lectura velocidad particula i
        particle.p.set_values((double)p.x, (double)p.y, (double)p.z);
        particle.h.set_values((double)h.x, (double)h.y, (double)h.z);
        particle.v.set_values((double)v.x, (double)v.y, (double)v.z);
        particles.push_back(particle);
    }
    return 0;
}

int read_file(const std::string &path, std::vector<Particle> &particles) {
    //head
    //std::cout << "reading file...\n";
    double ppm;
    int np;
    std::ifstream file(path, std::ios::binary);
    if (file.fail()){
        std::cerr <<"Error: Cannot open " << path <<" for reading\n";
        return -3;
    }
    read_head(file, np, ppm);
    std::cout << "ppm y np: " << ppm << " " << np << "\n";
    int exit_code = read_body(file, np, particles);
    if (exit_code == -5) {
        return -5;
    }

    file.close();
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