#include "include/cloth.h"
#include "include/constraint.h"
#include "include/mass.h"
#include "include/spring.h"
#include "include/system.h"
#include "include/textrenderer.h"
#include "include/util.h"
#include "include/vector3d.h"

void TextRenderer::draw(const Mass& mass) {
    // out << mass << std::endl;
    Vector3D pos(mass.getPos());
    out << pos.getX() << "," << pos.getY() << "," << pos.getZ() << "\n";
}

void TextRenderer::draw(const Spring& spring) {
    UNUSED(spring);
    // do nothing
    // out << spring << std::endl;
}

void TextRenderer::draw(const Cloth& cloth) {
    // out << cloth << std::endl;
    cloth.drawParticles(*this);
}

void TextRenderer::draw(const System& system) {
    // out << system << std::endl;
    system.drawContents(*this);
}

void TextRenderer::draw(const Constraint& constraint) {
    UNUSED(constraint);
    // do nothing
    // out << constraint << std::endl;
}


