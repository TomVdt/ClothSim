#include "include/hookconstraint.h"
#include "include/mass.h"
#include "include/util.h"

#include <iostream>

void HookConstraint::apply(Mass& mass, double time) const {
    UNUSED(time);
    mass.setVel(Vector3D(0, 0, 0));
    mass.addForce(-mass.getForce());
}

void HookConstraint::display(std::ostream& out, size_t level) const {
    out << indent(level) << "HookConstraint {";
    Constraint::display(out, level);
    out << "}";
}
