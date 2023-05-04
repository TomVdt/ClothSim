#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/renderer.h"
#include "include/util.h"


Vector3D Spring::springForce(Masse& mass) const {
    if (not valid()) {
        // Le ressort est "inactif"
        return Vector3D();
    }

    Vector3D vecMassMass;
    if (&mass == &mass2) {
        vecMassMass = mass1.getPos() - mass.getPos();
    }
    else if (&mass == &mass1) {
        vecMassMass = mass2.getPos() - mass.getPos();
    }
    else {
        // la masse n'appartient pas au spring, pas de force
        return Vector3D();
    }

    // Longueur du ressort
    const double dist(vecMassMass.norm());

    // Direction de la force
    const Vector3D dir(~vecMassMass);

    // La force
    return k * (dist - l0) * dir;
}

bool Spring::massConnected(Masse& mass) {
    return &mass == &mass1 or &mass == &mass2;
}

void Spring::display(std::ostream& out, size_t level) const
{
    out << indent(level) << "Spring " << this << " {" << std::endl
        << indent(level + 1) << "k: " << k << "," << std::endl
        << indent(level + 1) << "l0: " << l0 << "," << std::endl
        << indent(level + 1) << "masse 1: " << mass1 << "," << std::endl
        << indent(level + 1) << "masse 2: " << mass2 << std::endl
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