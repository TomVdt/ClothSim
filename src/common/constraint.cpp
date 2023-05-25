#include "include/constraint.h"
#include "include/constants.h"

#include <cmath>
#include <algorithm>
#include <iostream>

//// Generic constraint ////

Constraint::Constraint(const Vector3D& pos, double radius): pos(pos), radius(radius) {}

bool Constraint::isApplicable(const Masse& masse, double time) const {
    return Vector3D::dist(masse.getPos(), pos) < radius;
}

void Constraint::apply(Cloth& cloth, double time) const {
    // Double dispatch
    cloth.applyConstraint(*this, time);
}

//// Captain Hook ////

HookConstraint::HookConstraint(const Vector3D& pos, double radius): Constraint(pos, radius) {}

void HookConstraint::apply(Masse& mass, double time) const {
    mass.setVel(Vector3D(0, 0, 0));
    mass.addForce(-mass.getForce());
}

//// Impulsion ////

ImpulsionConstraint::ImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, std::vector<Cloth*> targetCloths):
    Constraint(pos, radius),
    massIds(),
    startTime(start),
    endTime(end),
    force(force)
{
    if (endTime < startTime) {
        std::swap(startTime, endTime);
    }

    for (auto& cloth : targetCloths) {
        auto massesInRange(cloth->getMassIdsInRange(pos, radius));
        for (auto& mass : massesInRange) {
            massIds.push_back(mass);
        }
    }
}

bool ImpulsionConstraint::isInList(const Masse& mass) const {
    return std::find(massIds.begin(), massIds.end(), mass.getId()) != massIds.end();
}

bool ImpulsionConstraint::isInTime(double time) const {
    return startTime <= time and time <= endTime;
}

bool ImpulsionConstraint::isApplicable(const Masse& mass, double time) const {
    return isInList(mass) and isInTime(time);
}

void ImpulsionConstraint::apply(Masse& mass, double time) const {
    mass.addForce(-CONSTANTS::g * mass.getMass());
    mass.addForce(force);
}

//// Sine impulsion ////

SineImpulsionConstraint::SineImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, double frequency, std::vector<Cloth*> targetCloths):
    ImpulsionConstraint(pos, radius, start, end, force, targetCloths),
    frequency(frequency)
{}

void SineImpulsionConstraint::apply(Masse& mass, double time) const {
    Vector3D theRealForce(std::sin(2 * M_PI * frequency * (time - startTime)) * force);
    mass.addForce(-CONSTANTS::g * mass.getMass());
    mass.addForce(theRealForce);
}
