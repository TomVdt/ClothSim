#include "include/constants.h"
#include "include/masse.h"
#include "include/spring.h"


// for std::swap
#include <utility>
#include <algorithm>

using CONSTANTS::g;
using std::endl;
using std::swap;


Masse::Masse(double mass, double lambda, const Vector3D& pos, const Vector3D& vel):
    mass(mass),
    lambda(lambda),
    pos(pos),
    vel(vel),
    force(mass * g),
    springList() {
        if (mass <= 0.0) {
            std::cerr << "tut tut fils de pute masse négative" << endl;
            mass = 1.0;
        }
        if (lambda < 0.0) {
            std::cerr << "zarma lambda négatif" << endl;
            lambda = 0.0;
        }
}


Vector3D Masse::acceleration() const {
    return force/mass;
}


void Masse::updateForce() {
    Vector3D springForce;
    // création d'un vecteur en plus pour rendre le code plus clair avec une formule claire pour la force
    for (const auto& spring : springList) {
        springForce += spring->springForce(this);
    }

    force = mass*g - lambda*vel + springForce;
}

void Masse::addForce(const Vector3D& df) {
    force += df;
}


void Masse::connectSpring(Spring* spring) {
    if (spring == nullptr) return;

    if (std::find(springList.begin(), springList.end(), spring) == springList.end()) {
        springList.push_back(spring);
    }
}

void Masse::disconnectSpring(Spring* spring) {
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

bool Masse::springConnected(Spring* spring) {
    if (std::find(springList.begin(), springList.end(), spring) == springList.end()) return false;
    return true;
}


void Masse::display(std::ostream& out) const {
    out << "Masse " << this << " {"
        << "masse: " << mass << ", "
        << "lambda: " << lambda << ", "
        << "position: " << pos << ", " 
        << "vitesse: " << vel << ", "
        << "force: " << force << ", "
        << "ressorts: [";

    size_t n(springList.size());
    for (size_t i(0); i < n; ++i) {
        out << springList[i];
        if (i != n - 1) {
            out << ", ";
        }
    }

    out << "]}";
}

std::ostream& operator<<(std::ostream & out, const Masse & mass) {
    mass.display(out);
    return out;
}
