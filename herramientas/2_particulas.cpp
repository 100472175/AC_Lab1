#include <iostream>
#include <fstream>


/* Uso del archivo: ./2_particulas out.fld */
int main(int argc, char **argv) {
  float ppm = 0.05;
  int np = 2;

  std::ofstream file(argv[1], std::ios::binary);

  float particle1[3][3] = {
    {-0.0573314, -0.0802636, -0.0577816},
    {0.211211, 0.118405, 0.140531},
    {0.213602, 0.123047, 0.138340}
  };
  float particle2[3][3] = {
    {-0.0573314, -0.0802636, -0.0577816},
    {0.211211, 0.118405, 0.140531},
    {0.213602, 0.123047, 0.138340}
  };
  file.write(reinterpret_cast<char*>(&ppm), 4);
  file.write(reinterpret_cast<char*>(&np), 4);
  file.write(reinterpret_cast<char*>(particle1), 36);
  file.write(reinterpret_cast<char*>(particle2), 36);
  return 0;
}