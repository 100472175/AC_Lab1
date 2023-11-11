#include "../sim/simulacion.hpp"
#include "../sim/vector_3d.hpp"

#include <fstream> 
#include <string> 



int load_trz(std::string path, Simulacion & sim) {
    int number_blocks;
    int64_t particulas_block;
    std::ifstream traza(path, std::ios::binary);
    traza.read(reinterpret_cast<char*>(&number_blocks), 4);

    for (int i = 0; i < number_blocks; ++i) {
        traza.read(reinterpret_cast<char*>(&particulas_block), 8);
        for (int j = 0; j < particulas_block; ++j){
            int64_t id;
            Vector3d<double> pos;
            Vector3d<double> grad;
            Vector3d<double> vel;
            Vector3d<double> acel;
            double dens;

            traza.read(reinterpret_cast<char*>(&id), 8);
            traza.read(reinterpret_cast<char*>(&pos), 24);
            traza.read(reinterpret_cast<char*>(&grad), 24);
            traza.read(reinterpret_cast<char*>(&vel), 24);
            traza.read(reinterpret_cast<char*>(&dens), 8);
            traza.read(reinterpret_cast<char*>(&acel), 24);
            
            sim.malla.bloques[i].particulas.clear();
            sim.malla.bloques[i].particulas.push_back(id);
            if (id >= sim.num_particulas || id < 0) {std::cout << "error\n"; return -1;}
            sim.particulas.pos[id] = pos;
            sim.particulas.gradiente[id] = grad;
            sim.particulas.velocidad[id] = vel;
            sim.particulas.dens[id] = dens;
            sim.particulas.aceleracion[id] = acel;

        }
    }
    return 0;
}

int write_trz(std::string path ,Simulacion & sim){
    std::ofstream salida(path);
    salida.write(reinterpret_cast<char*>(&sim.malla.tamano),4);

    for (int i = 0; i < sim.malla.tamano; i++){
        int64_t particulas = sim.malla.bloques[i].particulas.size();
        salida.write(reinterpret_cast<char*>(particulas), 8);
        for (int j = 0; j < particulas; j++){
            auto id_part = (int64_t)sim.malla.bloques[i].particulas[j];
            salida.write(reinterpret_cast<char*>(&id_part),8);
            salida.write(reinterpret_cast<char*>(&sim.particulas.pos[id_part]),24);
            salida.write(reinterpret_cast<char*>(&sim.particulas.gradiente[id_part]),24);
            salida.write(reinterpret_cast<char*>(&sim.particulas.velocidad[id_part]),24);
            salida.write(reinterpret_cast<char*>(&sim.particulas.dens[id_part]),8);
            salida.write(reinterpret_cast<char*>(&sim.particulas.aceleracion[id_part]),24);
        }
    }
}