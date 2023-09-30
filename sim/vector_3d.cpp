//
// Created by cesar on 29/09/23.
//

#include "vector_3d.hpp"

void Vector3d::set_values(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}

void Vector3d::operator+=(Vector3d const& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3d::operator-=(Vector3d const& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector3d::operator*=(double const& scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void Vector3d::operator/=(const double & scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
}