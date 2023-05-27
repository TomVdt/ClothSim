#include "include/exceptions.h"
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

    assertexception("Colineaire", RectCloth(
            1.0,
            { 5.0, 0.0, 0.0 },
            { 5.0, 0.0, 0.0 },
            { 0.0, 0.0, 0.0 },
            0.3, 1.0,
            100, 1.0
        ),
        ValueError
    );

    assertexception("Colineaire different", RectCloth(
            1.0,
            { 5.0, 0.0, 0.0 },
            { -5.0, 0.0, 0.0 },
            { 0.0, 0.0, 0.0 },
            0.3, 1.0,
            100, 1.0
        ),
        ValueError
    );

    return 0;
}
