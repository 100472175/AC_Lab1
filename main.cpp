#include <iostream>
#include <fstream>
#include <vector>

// Definición de la estructura de una partícula
struct Particle {
    float px, py, pz; // Coordenadas x, y, y z de la posición
    float hvx, hvy, hvz; // Coordenadas x, y, y z del vector hv
    float vx, vy, vz; // Coordenadas x, y, y z de la velocidad
};

int main() {
    const char* inputFile = "small.fld"; // Reemplaza con el nombre de tu archivo de entrada
    std::ifstream input(inputFile, std::ios::binary);

    if (!input) {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    // Leer la cabecera del archivo
    int ppm, np;
    input.read(reinterpret_cast<char*>(&ppm), sizeof(int));
    input.read(reinterpret_cast<char*>(&np), sizeof(int));

    std::cout << "Partículas por metro: " << ppm << std::endl;
    std::cout << "Número de partículas: " << np << std::endl;

    // Leer el cuerpo del archivo (partículas)
    std::vector<Particle> particles(np);
    input.read(reinterpret_cast<char*>(particles.data()), sizeof(Particle) * np);

    // Procesar los datos de las partículas (aquí puedes realizar tus cálculos)

    // Ejemplo: Imprimir la posición de la primera partícula
    std::cout << "Posición de la primera partícula: (" << particles[0].px << ", " << particles[0].py << ", " << particles[0].pz << ")" << std::endl;

    input.close();

    return 0;
}