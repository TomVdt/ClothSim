#include "include/vector3d.h"
#include <cmath>
#include "vector3d.h"

double Vector3D::norm() const {
    return sqrt(normSq());
}


double Vector3D::normSq() const {
    return x*x + y*y + z*z;
}


void Vector3D::normalize() {                // TODO : division par zéro
    double norme = norm();
    *this /= norm();
}


Vector3D Vector3D::normalized() const {
    Vector3D vec(*this);
    vec.normalize();
    return vec;
}


double Vector3D::dot(const Vector3D& vec) const {
    return x*vec.x + y*vec.y + z*vec.z;
}


// actuel cross l'argument
Vector3D Vector3D::cross(const Vector3D& vec) const {
    return Vector3D(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}
