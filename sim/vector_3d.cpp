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
double Vector3d::distancia(Vector3d pos1, Vector3d pos2) const{
 return sqrt(pow(pos1.x-pos2.x,2)+ pow(pos1.y-pos2.y,2)+ pow(pos1.z-pos2.z,2));
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

Vector3d Vector3d::operator-(Vector3d const & other) const {
  double x1 = x - other.x;
  double y1 = y - other.y;
  double z1 = z - other.z;
  Vector3d result(x1, y1, z1);
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

Vector3d Vector3d::operator/(Vector3d const & other) {
  Vector3d aux(0.0,0.0,0.0);
  aux.x = x / other.x;
  aux.y = y / other.y;
  aux.z = z / other.z;
  return aux
}

Vector3d_float Vector3d::to_float() {
    return Vector3d_float((float)x, (float)y, (float)z);
}

Vector3d Vector3d_float::to_double() {
    return Vector3d((double)x, (double)y, (double)z);
}