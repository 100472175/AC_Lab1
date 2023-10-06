//
// Created by cesar on 29/09/23.
//

#include "vector_3d.hpp"

void Vector3d::set_values(double a, double b, double c) {
  x = a;
  y = b;
  z = c;
}

void Vector3d::operator+=(Vector3d const & v) {
  x += v.x;
  y += v.y;
  z += v.z;
}

void Vector3d::operator-=(Vector3d const & v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

Vector3d Vector3d::operator-(Vector3d const & other) {
  double x1 = x - other.x;
  double y1 = y - other.y;
  double z1 = z - other.z;
  Vector3d result{};
  result.set_values(x1, y1, z1);
  return result;
}

void Vector3d::operator*=(double const & scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

void Vector3d::operator/=(double const & scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
}

Vector3d_float Vector3d::to_float() {
    return Vector3d_float((float)x, (float)y, (float)z);
}

Vector3d Vector3d_float::to_double() {
    return Vector3d((double)x, (double)y, (double)z);
}