#include "include/cloth.h"
#include "include/impulsionconstraint.h"
#include "include/mass.h"
#include "include/util.h"

#include <algorithm>
#include <iostream>
#include <vector>

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

bool ImpulsionConstraint::isInList(const Mass& mass) const {
    return std::find(massIds.begin(), massIds.end(), mass.getId()) != massIds.end();
}

bool ImpulsionConstraint::isInTime(double time) const {
    return startTime <= time and time <= endTime;
}

void ImpulsionConstraint::apply(Mass& mass, double time) const {
    if (isInList(mass) and isInTime(time)) {
        mass.addForce(-CONSTANTS::g * mass.getMass());
        mass.addForce(force);
    }
}

void ImpulsionConstraint::display(std::ostream& out, size_t level) const {
    out << indent(level) << "ImpulsionConstraint {";
    Constraint::display(out, level);
    out << ", force: " << force << "}";
}
