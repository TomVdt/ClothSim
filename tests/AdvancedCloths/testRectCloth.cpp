#include "include/rectcloth.h"
#include "include/test.h"

#include <iostream>

int main() {
    RectCloth cloth1(
        1.0,
        { 5.0, 0.0, 0.0 },
        { 0.0, 0.0, 5.0 },
        { 0.0, 0.0, 0.0 },
        0.3, 1.0,
        100, 1.0
    );

    std::cout << "Tissu rectangle plat:\n";
    std::cout << cloth1 << "\n";

    assertmsg("Nombre de masses", cloth1.getMassCount(), 36u);
    assertmsg("Nombre de ressorts", cloth1.getSpringCount(), 60u);
    assertmsg("Valide", cloth1.check(), true);

    RectCloth cloth2(
        1.0,
        { 5.0, 0.0, 0.0 },
        { 5.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 },
        0.3, 1.0,
        100, 1.0
    );

    std::cout << "Colinéaire:\n";
    std::cout << cloth2 << "\n";

    assertmsg("Nombre de masses", cloth2.getMassCount(), 0u);
    assertmsg("Nombre de ressorts", cloth2.getSpringCount(), 0u);
    assertmsg("Valide", cloth2.check(), true);

    RectCloth cloth3(
        1.0,
        { 5.0, 0.0, 0.0 },
        { -5.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 },
        0.3, 1.0,
        100, 1.0
    );

    std::cout << "Colinéaire différent:\n";
    std::cout << cloth3 << "\n";

    assertmsg("Nombre de masses", cloth3.getMassCount(), 0u);
    assertmsg("Nombre de ressorts", cloth3.getSpringCount(), 0u);
    assertmsg("Valide", cloth3.check(), true);

    return 0;
}
