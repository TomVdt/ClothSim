#include <cmath>
#include "include/vector3d.h"
#include "include/constants.h"

// Constructeurs
Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}

Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}


// Methodes et interface
double Vector3D::norm() const {
    return sqrt(normSq());
}

double Vector3D::normSq() const {
    return x*x + y*y + z*z;
}

Vector3D& Vector3D::normalize() {
    // TODO : division par zéro
    double norme = norm();
    *this /= norme;
    return *this;
}

Vector3D Vector3D::normalized() const {
    // Renvoie un nouveau vecteur, copie le vecteur actuel
    Vector3D vec(*this);
    vec.normalize();
    return vec;
}

double Vector3D::dot(const Vector3D& vec) const {
    return x*vec.x + y*vec.y + z*vec.z;
}

Vector3D Vector3D::cross(const Vector3D& vec) const {
    return Vector3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}


// Surcharge interne
Vector3D& Vector3D::operator+=(const Vector3D& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector3D& Vector3D::operator*=(double k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

Vector3D& Vector3D::operator/=(double k) {
    x /= k;
    y /= k;
    z /= k;
    return *this;
}

const Vector3D Vector3D::operator*(double k) const {
    // Copie necessaire car nouveau vecteur
    Vector3D vec(*this);
    vec *= k;
    return vec;
}

const double Vector3D::operator*(const Vector3D& vec) const{
    return dot(vec);
}

const Vector3D Vector3D::operator^(const Vector3D& vec) const {
    return cross(vec);
}

const Vector3D Vector3D::operator~() const {
    return normalized();
}

const Vector3D Vector3D::operator/(double k) const {
    Vector3D vec(*this);
    vec /= k;
    return vec;
}

const Vector3D Vector3D::operator-() const {
    Vector3D vec(*this);
    vec *= -1;
    return vec;
}

bool Vector3D::operator==(const Vector3D& vec) const {
    return (
        (abs(x - vec.x) < CONSTANTS::EPSILON) and
        (abs(y - vec.y) < CONSTANTS::EPSILON) and
        (abs(z - vec.z) < CONSTANTS::EPSILON)
    );
}

bool Vector3D::operator!=(const Vector3D& vec) const {
    return !(operator==(vec));
}


// Surcharge externe
const Vector3D operator+(Vector3D vec1, const Vector3D& vec2) {
    vec1 += vec2;
    return vec1;
}

const Vector3D operator-(Vector3D vec1, const Vector3D& vec2) {
    vec1 -= vec2;
    return vec1;
}

const Vector3D operator*(double k, const Vector3D& vec) {
    return vec * k;
}

std::ostream& operator<<(std::ostream& out, const Vector3D& vec) {
    out << "(" << vec.getX() << " " << vec.getY() << " " << vec.getZ() << ")";
    return out;
}
