#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"

#include <iomanip>


Spring::Spring(double k, double l0, Masse* mass1, Masse* mass2) : k(k), l0(l0), mass1(mass1), mass2(mass2) {
    // Vérifie la connection
    connect(mass1, mass2);
}

Vector3D Spring::springForce(Masse* mass) const {
    if (not valid()) {
        // Le ressort est "inactif"
        return Vector3D();
    }

    Vector3D vecMassMass;
    if (mass == mass1) {
        // Sens masse 1 -> masse 2
        vecMassMass = mass2->getPos() - mass->getPos();
    } else if (mass == mass2) {
        // Sens masse 2 -> masse 1
        vecMassMass = mass1->getPos() - mass->getPos();
    } else {
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

void Spring::connect(Masse* m1, Masse* m2) {
    disconnect();

    mass1 = m1;
    mass2 = m2;

    // Seulement connecter si le ressort est valide
    // Garanti que les masses auront seulement des ressorts valides
    if (valid()) {
        mass1->connectSpring(this);
        mass2->connectSpring(this);
    }
}

void Spring::disconnect() {
    // Seulement deconnecter si le ressort est valide
    // Garanti que les masses auront seulement des ressorts valides
    if (not valid()) {
        return;
    }

    mass1->disconnectSpring(this);
    mass2->disconnectSpring(this);

    mass1 = nullptr;
    mass2 = nullptr;
}

bool Spring::massConnected(Masse* mass) {
    if (mass == mass1 or mass == mass2) return true;
    return false;
}


void Spring::display(std::ostream &out) const
{
    out << "Spring " << this << " {\n"
        << "  k: " << k << ",\n"
        << "  l0: " << l0 << ",\n"
        << "  masse 1: ";
    
    if (mass1 != nullptr) {
        out << *mass1;
    } else {
        out << "nullptr";
    }

    out << ",\n  masse 2: ";

    if (mass2 != nullptr) {
        out << *mass2;
    } else {
        out << "nullptr";
    }

    out << "\n}\n";
}

bool Spring::valid() const {
    return mass1 != nullptr and mass2 != nullptr and mass1 != mass2;
}

std::ostream& operator<<(std::ostream& out, const Spring& spring) {
    spring.display(out);
    return out;
}
