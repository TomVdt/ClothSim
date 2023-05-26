#include "include/textrenderer.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/cloth.h"
#include "include/system.h"
#include "include/util.h"

void TextRenderer::draw(const Masse& mass) {
    // out << mass << std::endl;
    auto pos(mass.getPos());
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


