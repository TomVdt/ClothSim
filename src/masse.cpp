#include "include/constants.h"
#include "include/masse.h"
#include "include/spring.h"

// for std::swap
#include <utility>

using CONSTANTS::g;
using std::endl;
using std::swap;

// constructeur masse nécesssaire ensuite lambda, pos et vel peuvent etre par defaut
Masse::Masse(double mass, double lambda, const Vector3D& pos, const Vector3D& vel):
    mass(mass),
    lambda(lambda),
    pos(pos),
    vel(vel),
    force(mass * g),
    springList()
{}


// ajoute df à la force du vecteur
void Masse::addForce(const Vector3D& df) {
    force += df;
}


// renvoie l'acceleration
Vector3D Masse::acceleration() const {
    return force/mass;
}

void Masse::connectSpring(Spring* spring) {
    // TODO: ne vérifie pas si la masse est déjà connecté au ressort
    if (spring != nullptr) {
        springList.push_back(spring);
    }
}

void Masse::disconnectSpring(Spring* spring) {
    // find in spring list and remove it
    // assumes only 1 pointer to spring in list
    for (size_t i(0); i < springList.size(); ++i) {
        if (spring == springList[i]) {
            swap(springList[i], springList.back());
            springList.pop_back();
            return;
        }
    }
}

void Masse::disconnect() {
    springList.clear();
}

// met à jour la force sur la masse avec mg, -lambda*v et la somme des forces de rappel
void Masse::updateForce() {
    Vector3D springForce;
    for (const auto& spring : springList) {
        springForce += spring->springForce(this);
    }

    force = mass*g - lambda*vel + springForce;

}

void Masse::display(std::ostream& out) const {
    out << "Masse " << this << " {"
        << "masse: " << mass << ", "
        << "lambda: " << lambda << ", "
        << "position: " << pos << ", " 
        << "vitesse: " << vel << ", "
        << "force: " << force << ", "
        << "ressorts: ";

    size_t n(springList.size());
    for (size_t i(0); i < n; ++i) {
        out << springList[i];
        if (i != n - 1) {
            out << ", ";
        }
    }
}

// surcharge externe de << pour les masses
std::ostream& operator<<(std::ostream & out, const Masse & mass) {
    mass.display(out);
    return out;
}
