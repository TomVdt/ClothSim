#include "include/constants.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/exceptions.h"
#include "include/util.h"

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
    force(mass* g),
    springList()
{
    if (mass <= 0.0) {
        throw InvalidValueException("Mass must be strictly positive");
    }
    if (lambda < 0.0) {
        throw PerpetualMotionException("Coefficient of friction must be positive (perpetual energy go brrrrrrrr)");
    }
}

Vector3D Masse::acceleration() const {
    return force / mass;
}

void Masse::updateForce() {
    Vector3D springForce;
    for (const auto& spring : springList) {
        springForce += spring->springForce(*this);
    }

    force = mass * g - lambda * vel + springForce;
}

void Masse::addForce(const Vector3D& df) {
    force += df;
}

void Masse::connectSpring(Spring& spring) {
    if (not springConnected(spring)) {
        springList.push_back(&spring);
    }
}

void Masse::disconnectSpring(const Spring& spring) {
    for (size_t i(0); i < springList.size(); ++i) {
        if (&spring == springList[i]) {
            swap(springList[i], springList.back());
            springList.pop_back();
            return;
        }
    }
}

void Masse::disconnect() {
    springList.clear();
}

bool Masse::springConnected(const Spring& spring) const {
    for (const auto& s : springList) {
        if (&spring == s) {
            return true;
        }
    }
    return false;
}

Masse* Masse::copy() const {
    return new Masse(mass, lambda, pos, vel);
}

void Masse::display(std::ostream& out, size_t level) const {
    out << indent(level) << "Masse " << this << " {"
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

std::ostream& operator<<(std::ostream& out, const Masse& mass) {
    mass.display(out);
    return out;
}
