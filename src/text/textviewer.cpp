#include "include/textviewer.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/system.h"

void TextViewer::draw(Masse& mass) {
    out << mass << std::endl;
}

void TextViewer::draw(Cloth & cloth) {
    out << cloth << std::endl;
}

void TextViewer::draw(System & system) {
    out << system << std::endl;
}


