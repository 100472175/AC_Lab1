//
// Created by cesar on 29/09/23.
//

#include "vector_3d.hpp"
/*
#include <cmath>
template<typename T>
void Vector3d<T>::set_values(T a, T b, T c) {
    x = a;
    y = b;
    z = c;
}

template<typename T>
Vector3d<float> Vector3d<T>::to_float() {
    return Vector3d<float>((float)x, (float)y , (float)z);
}

template<typename T>
Vector3d<double> Vector3d<T>::to_double() {
    return Vector3d<double>((double)x, (double)y, (double)z);
}

template<typename T>
double Vector3d<T>::distancia(Vector3d pos1, Vector3d pos2) {
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
}

template<typename T>
void Vector3d<T>::operator+=(Vector3d const & v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

template<typename T>
Vector3d<T> Vector3d<T>::operator+(Vector3d<T> const & other) const {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

template<typename T>
void Vector3d<T>::operator-=(Vector3d<T> const & v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

template<typename T>
Vector3d<T> Vector3d<T>::operator-(Vector3d<T> const & other) const {
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}

template<typename T>
void Vector3d<T>::operator*=(const double &scalar) {
    x *= scalar;
    y *= scalar;
    z*= scalar;
}

template<typename T>
Vector3d<double> Vector3d<T>::operator*(double const & scalar) const {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}

template<typename T>
void Vector3d<T>::operator/=(double const & scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

template<typename T>
Vector3d<double> Vector3d<T>::operator/(Vector3d<T> const & other) const {
    return {this->x / (double)other.y, this->y / (double)y, this->z / (double)other.z};
}
*/
/*
void Vector3d<T>::set_values(T a, T b, T c) {
  x = a;
  y = b;
  z = c;
}

double Vector3d::distancia(Vector3d<T> pos1, Vector3d<T> pos2) {
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
}*/
