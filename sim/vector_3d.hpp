//
// Created by cesar on 29/09/23.
//

#ifndef AC_LAB1_VECTOR_3D_H
#define AC_LAB1_VECTOR_3D_H

struct Vector3d_float {
    float x, y, z;

    Vector3d_float(float x, float y, float z) : x(x), y (y), z(z) {};
};

struct Vector3d {
  public:
    double x, y, z;
    void set_values(double a, double b, double c);

    Vector3d_float to_float();

    // Para sumar dos vectores
    void operator+=(Vector3d const & v);
    // Para restar dos vectores
    void operator-=(Vector3d const & v);
    Vector3d operator-(Vector3d const & other);
    // Para multiplicar todos los elementos por un escalar
    void operator*=(double const & scalar);
    // Para dividir todos los elementos por un escalar
    void operator/=(double const & scalar);
};



struct Vector3d_int {
    int x, y, z;

};

#endif  // AC_LAB1_VECTOR_3D_H
