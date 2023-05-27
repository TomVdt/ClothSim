#include "include/constraint.h"
#include "include/util.h"
#include "include/constants.h"
#include "include/exceptions.h"

#include <cmath>
#include <algorithm>
#include <iostream>

//// Generic constraint ////

Constraint::Constraint(const Vector3D& pos, double radius): pos(pos), radius(radius) {}

bool Constraint::isApplicable(const Masse& masse, double time) const {
    UNUSED(time);
    return Vector3D::dist(masse.getPos(), pos) < radius;
}

void Constraint::apply(Cloth& cloth, double time) const {
    // Double dispatch
    cloth.applyConstraint(*this, time);
}

void Constraint::draw(Renderer& dest) {
    dest.draw(*this);
}

void Constraint::display(std::ostream& out, size_t level) const {
    UNUSED(level);
    out << "pos: " << pos << ", radius: " << radius;
}

std::ostream& operator<<(std::ostream& out, const Constraint& constraint) {
    constraint.display(out);
    return out;
}

//// Captain Hook ////

void HookConstraint::apply(Masse& mass, double time) const {
    UNUSED(time);
    mass.setVel(Vector3D(0, 0, 0));
    mass.addForce(-mass.getForce());
}

void HookConstraint::display(std::ostream& out, size_t level) const {
    out << indent(level) << "HookConstraint {";
    Constraint::display(out, level);
    out << "}";
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
    UNUSED(time);
    mass.addForce(-CONSTANTS::g * mass.getMass());
    mass.addForce(force);
}

void ImpulsionConstraint::display(std::ostream& out, size_t level) const {
    out << indent(level) << "ImpulsionConstraint {";
    Constraint::display(out, level);
    out << ", force: " << force << "}";
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

void SineImpulsionConstraint::display(std::ostream& out, size_t level) const {
    out << indent(level) << "SineImpulsionConstraint {";
    Constraint::display(out, level);
    out << ", force: " << force << ", frequence: " << frequency << "}";
}

//// Attraction point ////

AttractionConstraint::AttractionConstraint(const Vector3D& pos, double spherOfInfluence, double intensity, double innerRadius): Constraint(pos, spherOfInfluence), intensity(intensity), innerRadius(innerRadius) {
    if (innerRadius < CONSTANTS::EPSILON) {
        ERROR(ValueError, "Inner radius must be strictly positive");
    }
}

void AttractionConstraint::apply(Masse& mass, double time) const {
    UNUSED(time);
    Vector3D dir;
    if (mass.getPos() == getPos()) {
        dir = Vector3D(0, 1, 0);
    } else {
        dir = ~(getPos() - mass.getPos());
    }
    const double dist(
        std::max(Vector3D::dist(mass.getPos(), getPos()), innerRadius)
    );
    const Vector3D force(mass.getMass() * intensity / (dist * dist) * dir);
    mass.addForce(force);
}

void AttractionConstraint::display(std::ostream& out, size_t level) const {
    out << indent(level) << "AttractionConstraint {";
    Constraint::display(out, level);
    out << "}";
}
