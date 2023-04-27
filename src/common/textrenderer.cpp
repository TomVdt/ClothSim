#include "include/textrenderer.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/system.h"

void TextRenderer::draw(const Masse& mass) {
    out << mass << std::endl;
}

void TextRenderer::draw(const Cloth & cloth) {
    out << cloth << std::endl;
}

void TextRenderer::draw(const System & system) {
    out << system << std::endl;
}


