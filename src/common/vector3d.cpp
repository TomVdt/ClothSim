#include "include/constants.h"
#include "include/exceptions.h"
#include "include/vector3d.h"

#include <cmath>
#include <iostream>
#include <glm/vec3.hpp>


double Vector3D::norm() const {
    return sqrt(normSq());
}

double Vector3D::normSq() const {
    return x * x + y * y + z * z;
}

Vector3D& Vector3D::normalize() {
    double norme = norm();
    if (fabs(norme) < CONSTANTS::EPSILON) {
        ERROR(ZeroDivisionError, "Can't normalize null vector");
    }
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
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3D Vector3D::cross(const Vector3D& vec) const {
    return Vector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

Vector3D& Vector3D::rotate(double angle, const Vector3D& axis) {
    *this = rotated(angle, axis);
    return *this;
}

Vector3D Vector3D::rotated(double angle, const Vector3D& axis) const {
    // (cos θ) u+(1-cosθ)(u.n) n+(sinθ) (n ^ u)
    const double costheta(std::cos(angle));
    const double sintheta(std::sin(angle));

    return costheta * *this + (1 - costheta) * (dot(axis)) * axis - sintheta * cross(axis);
}

double Vector3D::dist(const Vector3D& a, const Vector3D& b) {
    return (b - a).norm();
}


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

double Vector3D::operator*(const Vector3D& vec) const {
    return dot(vec);
}

Vector3D Vector3D::operator^(const Vector3D& vec) const {
    return cross(vec);
}

Vector3D Vector3D::operator~() const {
    return normalized();
}

bool Vector3D::operator==(const Vector3D& vec) const {
    return (
        (fabs(x - vec.x) < CONSTANTS::EPSILON) and
        (fabs(y - vec.y) < CONSTANTS::EPSILON) and
        (fabs(z - vec.z) < CONSTANTS::EPSILON)
        );
}

bool Vector3D::operator!=(const Vector3D& vec) const {
    return !(operator==(vec));
}

Vector3D Vector3D::cross(const Vector3D& v1, const Vector3D& v2) {
    return v1.cross(v2);
}

double Vector3D::dot(const Vector3D& v1, const Vector3D& v2) {
    return v1.dot(v2);
}

glm::vec3 Vector3D::toGlmVec3() const {
    return glm::vec3(x, y, z);
}



Vector3D operator+(Vector3D vec1, const Vector3D& vec2) {
    vec1 += vec2;
    return vec1;
}

Vector3D operator-(Vector3D vec) {
    vec *= -1;
    return vec;
}

Vector3D operator-(Vector3D vec1, const Vector3D& vec2) {
    vec1 -= vec2;
    return vec1;
}

Vector3D operator*(Vector3D vec, double k) {
    vec *= k;
    return vec;
}

Vector3D operator*(double k, const Vector3D& vec) {
    return vec * k;
}

Vector3D operator/(Vector3D vec, double k) {
    vec /= k;
    return vec;
}

std::ostream& operator<<(std::ostream& out, const Vector3D& vec) {
    out << "(" << vec.getX() << " " << vec.getY() << " " << vec.getZ() << ")";
    return out;
}
