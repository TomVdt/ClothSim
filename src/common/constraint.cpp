#include "include/cloth.h"
#include "include/constraint.h"
#include "include/mass.h"
#include "include/renderer.h"
#include "include/util.h"
#include "include/vector3d.h"

#include <iostream>

Constraint::Constraint(const Vector3D& pos, double radius): pos(pos), radius(radius) {}

bool Constraint::isApplicable(const Mass& masse, double time) const {
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
