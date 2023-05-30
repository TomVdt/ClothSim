#include "include/mass.h"
#include "include/renderer.h"
#include "include/spring.h"
#include "include/util.h"
#include "include/vector3d.h"

#include <iostream>
#include <vector>

int Spring::COUNT(0);

Vector3D Spring::springForce(const Mass& mass) const {
    if (not valid()) {
        // Le ressort est "inactif"
        return Vector3D();
    }

    int heading;
    if (&mass == &mass2) {
        heading = 1;
    }
    else if (&mass == &mass1) {
        heading = -1;
    }
    else {
        // la masse n'appartient pas au spring, pas de force
        return Vector3D();
    }

    // Direction de la force
    const Vector3D vecMassMass(mass1.getPos() - mass2.getPos());
    const Vector3D dir(~vecMassMass);

    return heading * k * (length() - l0) * dir;
}

double Spring::energy() const {
    if (not valid()) {
        // Le ressort est "inactif"
        return 0.0;
    }

    const double deltaL((length() - l0));

    return 0.5 * k * deltaL * deltaL;
}

double Spring::length() const {
    // Longueur du ressort
    return Vector3D::dist(mass1.getPos(), mass2.getPos());
}

bool Spring::massConnected(const Mass& mass) const {
    return &mass == &mass1 or &mass == &mass2;
}

void Spring::display(std::ostream& out, size_t level) const
{
    out << indent(level) << "Spring " << this << " {" << std::endl
        << indent(level + 1) << "k: " << k << "," << std::endl
        << indent(level + 1) << "l0: " << l0 << "," << std::endl
        << indent(level + 1) << "mass 1: " << mass1 << "," << std::endl
        << indent(level + 1) << "mass 2: " << mass2 << std::endl
        << indent(level) << "}";
}

bool Spring::valid() const {
    return (&mass1 != &mass2);
}

bool Spring::areEndsValid() const {
    return valid() and mass1.springConnected(*this) and mass2.springConnected(*this);
}

std::ostream& operator<<(std::ostream& out, const Spring& spring) {
    spring.display(out);
    return out;
}

void Spring::draw(Renderer& dest) {
    dest.draw(*this);
}