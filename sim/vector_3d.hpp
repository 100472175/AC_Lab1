//
// Created by cesar on 29/09/23.
//

#ifndef AC_LAB1_VECTOR_3D_H
#define AC_LAB1_VECTOR_3D_H
#include <cmath>

constexpr double cuadrado(double numero) {
  return numero * numero;
}

template <typename T>
struct Vector3d {
    T x, y, z;
    constexpr Vector3d(T x, T y, T z) : x(x), y(y), z(z){};

    void set_values(T a, T b, T c) {
      x = a;
      y = b;
      z = c;
    }

    Vector3d<float> to_float() { return {(float) x, (float) y, (float) z}; }

    Vector3d<double> to_double() { return {(double) x, (double) y, (double) z}; }

    static double sq_distancia(Vector3d pos1, Vector3d pos2) {
      return cuadrado(pos1.x - pos2.x) + cuadrado(pos1.y - pos2.y) + cuadrado(pos1.z - pos2.z);
    }

    static double distancia(Vector3d pos1, Vector3d pos2) {
      return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
    }

    // Para sumar dos vectores
    Vector3d operator+=(Vector3d<T> const & v) {
      x += v.x;
      y += v.y;
      z += v.z;
      return *this;
    }

    Vector3d operator+(Vector3d<T> const & other) const {
      return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    // Para restar dos vectores
    Vector3d operator-=(Vector3d const & v) {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      return *this;
    }

    Vector3d operator-(Vector3d const & other) const {
      return {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    // Para multiplicar todos los elementos por un escalar
    Vector3d operator*=(double const & scalar) {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }

    Vector3d operator*(T const scalar) const {
      return {this->x * scalar, this->y * scalar, this->z * scalar};
    }

    // Para dividir todos los elementos por un escalar
    Vector3d operator/=(double const & scalar) {
      x /= scalar;
      y /= scalar;
      z /= scalar;
      return *this;
    }

    // Para dividir todos los elementos por un vector
    Vector3d<double> operator/(Vector3d<T> const & other) const {
      return {this->x / (double) other.x, this->y / (double) other.y, this->z / (double) other.z};
    }
};

#endif  // AC_LAB1_VECTOR_3D_H
