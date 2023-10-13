#include <iostream> 

/*
 | cte | Descripción            | valor    |
 |-----|------------------------|----------|
 | r   | Multiplicador de radio | 1.695    |
 | ρ   | Densidad de fluido     | 103      |
 | ps  | Presión de rigidez     | 3.0      | 
 | sc  | Colisiones de rigidez  | 3 · 104  |
 | dv  | Amortiguamiento        | 128.0    |
 | μ   | Viscosidad             | 0.4      |
 | dp  | Tamaño de partícula    | 2 · 10−4 |
 | ∆t  | Paso de tiempo         | 10−3     |

*/
typedef struct _particle {
    float px;
    float py;
    float pz;
    float hvx;
    float hvy;
    float hvz;
    float vx;
    float vy;
    float vz;
} particle;

int main() {
  FILE* small = fopen("final.fld", "r");
  float ppm;
  int32_t np;
  int n_bytes = 0;
  n_bytes = fread(&ppm, 4, 1, small);
  if (n_bytes != 1) {
    printf("ERROR: ppm nor read correctly\n");
    return -1;
  }
  printf("===================\n");
  printf("ppm: = %f\n", ppm);
  n_bytes = fread(&np, 4, 1, small);

  if (n_bytes != 1) {
    printf("ERROR: ppm nor read correctly\n");
    return -1;
  }

  printf("np = %i\n", np);
  printf("===================\n");

  for (int i = 0; i < np; ++i) {
    float buffer[9];
    n_bytes = fread(buffer, 4, 9, small);
    if (n_bytes < 9) {
      printf("ERROR: datos de partícula %i mal leídos", i);
      return -1;
    }
    printf("***\n");
    printf("particle %i:\n  px = %f\n  py = %f\n  pz = %f\n  hx = %f\n  hy = %f\n  hz = %f\n  vx = %f\n  vy = %f\n  vz = %f\n", i, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8]);
    printf("***\n");
    return 0;
  }
  n_bytes = fread(&ppm, 1, 1, small);
  if (n_bytes > 0) printf("queda archivo sin leer\n");

    return 0;
}

int main_() {
    FILE* small = fopen("out/small-1.fld", "r");
    float ppm;
    int32_t np;
    int n_bytes = 0;
    n_bytes = fread(&ppm, 4, 1, small);
    if (n_bytes != 1) {
    printf("ERROR: ppm nor read correctly\n");
    return -1;
    }
    printf("===================\n");
    printf("ppm: = %f\n", ppm);
    n_bytes = fread(&np, 4, 1, small);

    if (n_bytes != 1) {
    printf("ERROR: ppm nor read correctly\n");
    return -1;
    }

    printf("np = %i\n", np);
    printf("===================\n");

    for (int i = 0; i < np; ++i) {
    float buffer[9];
    n_bytes = fread(buffer, 4, 9, small);
    if (n_bytes < 9) {
      printf("ERROR: datos de partícula %i mal leídos", i);
      return -1;
    }
    printf("***\n");
    printf("particle %i:\n  px = %f\n  py = %f\n  pz = %f\n  hx = %f\n  hy = %f\n  hz = %f\n  vx = %f\n  vy = %f\n  vz = %f\n", i, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8]);
    printf("***\n");
    }
    n_bytes = fread(&ppm, 1, 1, small);
    if (n_bytes > 0) printf("queda archivo sin leer\n");



    return 0;
}