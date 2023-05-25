#include "include/constants.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/exceptions.h"
#include "include/renderer.h"
#include "include/constraint.h"
#include "include/util.h"

// for std::swap
#include <utility>
#include <algorithm>
#include <memory>

using CONSTANTS::g;
using std::endl;
using std::swap;

int Masse::COUNT(0);

Masse::Masse(double mass, double lambda, const Vector3D& pos, const Vector3D& vel):
    mass(mass),
    lambda(lambda),
    pos(pos),
    vel(vel),
    force(mass * g),
    springs(),
    constraints(),
    id(COUNT++)
{
    if (mass <= 0.0) {
        ERROR(ValueError, "Mass must be strictly positive");
    }
    if (lambda < 0.0) {
        ERROR(ValueError, "Coefficient of friction must be positive");
    }
}

Vector3D Masse::acceleration() const {
    return force / mass;
}

Vector3D Masse::acceleration(double time, const Vector3D& p, const Vector3D& v) {
    Vector3D posBackup(pos);
    Vector3D velBackup(vel);

    pos = p;
    vel = v;
    updateForce();
    pos = posBackup;
    vel = velBackup;

    applyConstraints(time);

    return acceleration();
}

double Masse::energy() const {
    // TODO: gravity norm, correctly with constexpr
    // return - mass * CONSTANTS::g.getY() * pos.getY();
    // return 1/2 * mass * vel.normSq();
    return 0.5 * mass * vel.normSq() + mass * CONSTANTS::g.norm() * pos.getY();
}

void Masse::addConstraint(const Constraint& constraint) {
    constraints.push_back(&constraint);
}

void Masse::clearConstraints() {
    constraints.clear();
}

void Masse::applyConstraint(const Constraint& constraint, double time) {
    if (constraint.isApplicable(*this, time)) {
        constraint.apply(*this, time);
    }
}

void Masse::applyConstraints(double time) {
    for (const auto& constraint : constraints) {
        applyConstraint(*constraint, time);
    }
}

void Masse::updateForce() {
    Vector3D springForce;
    for (const auto& spring : springs) {
        springForce += spring->springForce(*this);
    }
    force = mass * g - lambda * vel + springForce;
}

void Masse::addForce(const Vector3D& df) {
    force += df;
}

void Masse::connectSpring(Spring& spring) {
    if (not springConnected(spring)) {
        springs.push_back(&spring);
    }
}

void Masse::disconnectSpring(const Spring& spring) {
    for (size_t i(0); i < springs.size(); ++i) {
        if (&spring == springs[i]) {
            swap(springs[i], springs.back());
            springs.pop_back();
            return;
        }
    }
}

void Masse::disconnect() {
    springs.clear();
}

bool Masse::springConnected(const Spring& spring) const {
    for (const auto& s : springs) {
        if (&spring == s) {
            return true;
        }
    }
    return false;
}

// std::unique_ptr<Masse> Masse::copy() const {
//     return std::make_unique<Masse>(mass, lambda, pos, vel, locked);
// }

void Masse::draw(Renderer& dest) {
    dest.draw(*this);
}

void Masse::display(std::ostream& out, size_t level) const {
    out << indent(level) << "Masse " << this << " {"
        << "masse: " << mass << ", "
        << "lambda: " << lambda << ", "
        << "position: " << pos << ", "
        << "vitesse: " << vel << ", "
        << "force: " << force << ", "
        << "ressorts: [";

    size_t n(springs.size());
    for (size_t i(0); i < n; ++i) {
        out << springs[i];
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
