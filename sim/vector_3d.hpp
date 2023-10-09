//
// Created by cesar on 29/09/23.
//

#ifndef AC_LAB1_VECTOR_3D_H
#define AC_LAB1_VECTOR_3D_H
#include <cmath>

template<typename T>
struct Vector3d {
    T x, y, z;
    constexpr Vector3d(T x, T y, T z) : x(x), y(y), z(z){};

    void set_values(T a, T b, T c) {
        x = a;
        y = b;
        z = c;
    }
    Vector3d<float> to_float() {
        return Vector3d<float>((float)x, (float)y , (float)z);
    }
    Vector3d<double> to_double() {
        return Vector3d<double>((double)x, (double)y, (double)z);
    }
    static double distancia(Vector3d pos1, Vector3d pos2) {
        return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
    }
    // Para sumar dos vectores
    void operator+=(Vector3d<T> const & v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    Vector3d<T> operator+(Vector3d<T> const & other) const {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }
    // Para restar dos vectores
    void operator-=(Vector3d const & v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    Vector3d<T> operator-(Vector3d const & other) const {
        return {this->x - other.x, this->y - other.y, this->z - other.z};
    }
    // Para multiplicar todos los elementos por un escalar
    void operator*=(double const & scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }
    Vector3d<double> operator*(double const & scalar) const {
        return {this->x * scalar, this->y * scalar, this->z * scalar};

    }
    // Para dividir todos los elementos por un escalar
    void operator/=(double const & scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    // Para dividir todos los elementos por un vector
    Vector3d<double> operator/(Vector3d<T> const & other) const {
        return {this->x / (double)other.x, this->y / (double)other.y, this->z / (double)other.z};

    }
};

/*
struct Vector3d_float {
    float x, y, z;
    constexpr Vector3d_float(float x, float y, float z) : x(x), y(y), z(z){};
    Vector3d to_double();
};

struct Vector3d {
  public:
    double x, y, z;
    void set_values(double a, double b, double c);
    static double distancia(Vector3d pos1, Vector3d pos2);
    constexpr Vector3d(double x, double y, double z) : x(x), y(y), z(z){};
    Vector3d_float to_float();

    // Para sumar dos vectores
    void operator+=(Vector3d const & v);
    Vector3d operator+(Vector3d const & other) const;
    // Para restar dos vectores
    void operator-=(Vector3d const & v);
    Vector3d operator-(Vector3d const & other) const;
    // Para multiplicar todos los elementos por un escalar
    void operator*=(double const & scalar);
    Vector3d operator*(double const & scalar) const;
    // Para dividir todos los elementos por un escalar
    void operator/=(double const & scalar);
    // Para dividir todos los elementos por un vector
    Vector3d operator/(Vector3d const & other) const;
};

struct Vector3d_int {
    int x, y, z;
};
*/
#endif  // AC_LAB1_VECTOR_3D_H
