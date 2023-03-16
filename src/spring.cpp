#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"

Vector3D Spring::springForce(Masse* mass) const {
    Vector3D vecMassMass;
    if (mass == mass1) {
        vecMassMass = mass2->getPos() - mass->getPos();
    } else if (mass == mass2) {
        vecMassMass = mass1->getPos() - mass->getPos();
    } else {
        // la masse n'appartient pas au spring, pas de force
        // TODO: warn?
        std::cout << "UNCONNECTED SPRING!!! " << mass << "\n";
        return Vector3D();
    }

    const double dist(vecMassMass.norm());
    const Vector3D dir(~vecMassMass);
    return k * (dist - l0) * dir;
}

std::ostream& operator<<(std::ostream& out, const Spring& spring) {
    out << "Spring " << &spring << "(\n"
        << "\tmasse 1: " << spring.getMass1() << "\n"
        << "\tmasse 2: " << spring.getMass2() << "\n"
        << "\tk: " << spring.getK() << "\n"
        << "\tl0: " << spring.getL0() << "\n)\n";
}
