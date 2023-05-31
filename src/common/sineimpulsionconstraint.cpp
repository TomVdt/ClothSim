#include "include/constants.h"
#include "include/mass.h"
#include "include/sineimpulsionconstraint.h"
#include "include/util.h"
#include "include/vector3d.h"

#include <cmath>
#include <iostream>

SineImpulsionConstraint::SineImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, double frequency, std::vector<Cloth*> targetCloths):
    ImpulsionConstraint(pos, radius, start, end, force, targetCloths),
    frequency(frequency)
{}

void SineImpulsionConstraint::apply(Mass& mass, double time) const {
    if (isInList(mass) and isInTime(time)) {
        Vector3D theRealForce(std::sin(2 * M_PI * frequency * (time - startTime)) * force);
        mass.addForce(-CONSTANTS::g * mass.getMass());
        mass.addForce(theRealForce);
    }
}

void SineImpulsionConstraint::display(std::ostream& out, size_t level) const {
    out << indent(level) << "SineImpulsionConstraint {";
    Constraint::display(out, level);
    out << ", force: " << force << ", frequence: " << frequency << "}";
}
