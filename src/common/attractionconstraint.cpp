#include "include/attractionconstraint.h"
#include "include/constants.h"
#include "include/exceptions.h"
#include "include/mass.h"
#include "include/util.h"
#include "include/vector3d.h"

#include <iostream>

AttractionConstraint::AttractionConstraint(const Vector3D& pos, double spherOfInfluence, double intensity, double innerRadius): Constraint(pos, spherOfInfluence), intensity(intensity), innerRadius(innerRadius) {
    if (innerRadius < CONSTANTS::EPSILON) {
        ERROR(ValueError, "Inner radius must be strictly positive");
    }
}

void AttractionConstraint::apply(Mass& mass, double time) const {
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
