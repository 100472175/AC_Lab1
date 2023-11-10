#include "../sim/simulacion.hpp"
#include "../sim/vector_3d.hpp"

#include <fstream> 
#include <string> 



int load_trz(std::string path, Simulacion & sim) {
    int number_blocks;
    int64_t particulas_block;
    std::ifstream traza(path);
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
            traza.read(reinterpret_cast<char*>(&dens), 8);
            traza.read(reinterpret_cast<char*>(&acel), 24);
            
            sim.malla.bloques[i].particulas.clear();
            sim.malla.bloques[i].particulas.push_back(id);
            sim.particulas.pos[id] = pos;
            sim.particulas.gradiente[id] = grad;
            sim.particulas.velocidad[id] = vel;
            sim.particulas.dens[id] = dens;
            sim.particulas.aceleracion[id] = acel;

        }
    }
    return 0;
}