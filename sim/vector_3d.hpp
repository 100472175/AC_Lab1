#ifndef AC_LAB1_VECTOR_3D_H
#define AC_LAB1_VECTOR_3D_H

#include <cmath>

constexpr double cuadrado(double numero) {
  return numero * numero;
}

template <typename T>
struct Vector3d {
    T x, y, z;

    /**
     * Función que realiza el cast de los valores x,y,z del Vector3d a float.
     *
     * @return Devuelve un Vector3d de tipo float.
     */
    constexpr Vector3d<float> to_float() { return {(float) x, (float) y, (float) z}; }

    /**
     * Función que realiza el cast de los valores x,y,z del Vector3d a double.
     *
     * @return Devuelve un Vector3d de tipo double.
     */
    constexpr Vector3d<double> to_double() { return {(double) x, (double) y, (double) z}; }

    /**
     * Función que realiza el cast de los valores x,y,z del Vector3d a int.
     *
     * @return Devuelve un Vector3d de tipo int.
     */
    constexpr Vector3d<int> to_int() { return {(int) x, (int) y, (int) z}; }

    /**
     * Función que calcula la distancia entre dos Vector3d y eleva al cuadrado el resultado, la
     * implementación evita calcular la raíz y elevarla al cuadrado.
     *
     * @param pos1 Primer Vector3d.
     * @param pos2 Segundo Vector3d.
     *
     * @return Devuelve un double de la distancia al cuadrado.
     */

    constexpr static double sq_distancia(Vector3d pos1, Vector3d pos2) {
      return cuadrado(pos1.x - pos2.x) + cuadrado(pos1.y - pos2.y) + cuadrado(pos1.z - pos2.z);
    }

    /**
     * Función que devuelve la distancia entre dos coordenadas en un espacio tridimensional.
     *
     * @param pos1 Primer Vector3d.
     * @param pos2 Segundo Vector3d.
     *
     * @return Devuelve un double de la distancia.
     */
    constexpr static double distancia(Vector3d pos1, Vector3d pos2) {
      return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
    }

    /**
     * Función que devuelve el valor absoluto de la diferencia de cada una de las coordenadas.
     *
     * @param pos1 Primer Vector3d.
     * @param pos2 Segundo Vector3d.
     *
     * @return Devuelve un Vector3d de tipo double con el valor absoluto calculado.
     */
    constexpr static Vector3d<double> abs_diff(Vector3d pos1, Vector3d pos2) {
      return {std::abs(pos1.x - pos2.x), std::abs(pos1.y - pos2.y), std::abs(pos1.z - pos2.z)};
    }

    /**
     * Sobrecarga del operador += para calcular la suma del propio vector con otro. Se almacena el
     * resultado en el propio vector.
     *
     * @param v Vector con el que se realiza la suma.
     *
     * @return Devuelve el mismo Vector3d con la suma calculada.
     */
    constexpr Vector3d operator+=(Vector3d<T> const & v) {
      x += v.x;
      y += v.y;
      z += v.z;
      return *this;
    }

    /**
     * Sobrecarga del operador + para calcular la suma de dos Vector3d coordenada por coordenada.
     *
     * @param other Vector con el que se realiza la suma.
     *
     * @return Devuelve otro Vector3d que almacena la suma.
     */
    constexpr Vector3d operator+(Vector3d<T> const & other) const {
      return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    /**
     * Sobrecarga del operador -= para calcular la resta del propio vector con otro, se almacena el
     * resultado en el propio vector.
     *
     * @param v Vector con el que se realiza la suma.
     *
     * @return Devuelve el mismo Vector3d con la resta calculada.
     */
    constexpr Vector3d operator-=(Vector3d const & v) {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      return *this;
    }

    /**
     * Sobrecarga del operador - para calcular la resta de dos vectores y almacena el resultado en
     * otro vector3d.
     *
     * @param other Vector con el que se realiza la resta.
     *
     * @return Devuelve otro Vector3d que almacena la resta.
     */
    constexpr Vector3d operator-(Vector3d const & other) const {
      return {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    /**
     * Sobrecarga del operador *= para calcular la multiplicación de un escalar por el propio
     * vector, almacenando el valor en el propio vector.
     *
     * @param scalar Variable de cualquier tipo con el que se realiza la multiplicación.
     *
     * @return Devuelve el propio Vector3d con el valor calculado.
     */
    constexpr Vector3d operator*=(T const & scalar) {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }

    /**
     * Sobrecarga del operador * que multiplica el propio vector3d por un escalar y almacena el
     * resultado en otro Vector3d.
     *
     * @param scalar Variable escalar de cualquier tipo.
     *
     * @return Devuelve un nuevo Vector3d con los valores calculados.
     */
    constexpr Vector3d operator*(T const scalar) const {
      return {this->x * scalar, this->y * scalar, this->z * scalar};
    }

    /**
     * Sobrecarga del operador /= para calcular la división del propio Vector3d por un escalar,
     * almacena el valor en el propio Vector3d.
     *
     * @param scalar Variable escalar de cualquier tipo.
     *
     * @return Devuelve el propio Vector3d con el valor calculado.
     */
    constexpr Vector3d operator/=(T const & scalar) {
      x /= scalar;
      y /= scalar;
      z /= scalar;
      return *this;
    }

    /**
     * Sobrecarga del operador / para calcular la división del propio Vector3d por otro Vector3d y
     * almacena el valor en otro Vector3d.
     *
     * @param other Vector3d con el que se realiza la división.
     *
     * @return Devuelve un Vector3d con los valores calculados.
     */
    constexpr Vector3d<T> operator/(Vector3d<T> const & other) const {
      return {this->x / (double) other.x, this->y / (double) other.y, this->z / (double) other.z};
    }
};

#endif  // AC_LAB1_VECTOR_3D_H
