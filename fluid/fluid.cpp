//
// Created by paula on 27/09/23.
//
/*int main(int argc, char* argv[]) {


}*/

#include "../sim/lectura_archivo.hpp"

int main() {
    std::vector<particle> particles;
    read_file("../small.fld", particles);
    std::cout << particles.size() << std::endl;
    int i = 0;
    for (auto p : particles) {
        std::cout << "particle " << i++ << ":\n" << p.px << "\n";
        std::cout << "=========\n";
    }

    return 0;
}