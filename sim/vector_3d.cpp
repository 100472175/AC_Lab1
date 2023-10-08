//
// Created by cesar on 29/09/23.
//

#include "vector_3d.hpp"

#include <cmath>

void Vector3d::set_values(double a, double b, double c) {
  x = a;
  y = b;
  z = c;
}

double Vector3d::distancia(Vector3d pos1, Vector3d pos2) {
  return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
}

Vector3d Vector3d::operator+(Vector3d const & other) const {
  return {this->x + other.x, this->y + other.y, this->z + other.z};
}

void Vector3d::operator+=(Vector3d const & v) {
  x += v.x;
  y += v.y;
  z += v.z;
}

Vector3d Vector3d::operator-(Vector3d const & other) const {
  double const x_1 = x - other.x;
  double const y_1 = y - other.y;
  double const z_1 = z - other.z;
  return {x_1, y_1, z_1};
}

void Vector3d::operator-=(Vector3d const & v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

Vector3d Vector3d::operator*(double const & scalar) const {
  return {this->x * scalar, this->y * scalar, this->z * scalar};
}

void Vector3d::operator*=(double const & scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

Vector3d Vector3d::operator/(Vector3d const & other) const {
  Vector3d aux(0.0, 0.0, 0.0);
  aux.x = x / other.x;
  aux.y = y / other.y;
  aux.z = z / other.z;
  return aux;
}

void Vector3d::operator/=(double const & scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
}

Vector3d_float Vector3d::to_float() {
  return {(float) x, (float) y, (float) z};
}

Vector3d Vector3d_float::to_double() {
  return Vector3d((double) x, (double) y, (double) z);
}