#include "include/diskcloth.h"
#include "include/exceptions.h"
#include "include/test.h"

#include <iostream>
#include <cmath>

int main() {
    DiskCloth cloth1(
        1.0,
        { 0.0, 0.0, 0.0 },
        { 0.0, 2.0, 0.0 },
        1.0,
        0.3, 100,
        45.0 * M_PI / 180.0
    );

    std::cout << "Tissu disque:\n";
    std::cout << cloth1 << "\n";

    assertmsg("Nombre de masses", cloth1.getMassCount(), 1 + 8 + 8);
    assertmsg("Nombre de ressorts", cloth1.getSpringCount(), 8 + 8 + 8 + 8);
    assertmsg("Valide", cloth1.check(), true);

    DiskCloth cloth2(
        1.0,
        { 0.0, 0.0, 0.0 },
        { 2.0, 2.0, 2.0 },
        1.0,
        0.3, 100,
        45.0 * M_PI / 180.0
    );
    // Radius: ~3.4

    std::cout << "Tissu disque tourné:\n";
    std::cout << cloth2 << "\n";

    assertmsg("Nombre de masses", cloth2.getMassCount(), 1 + 8 + 8 + 8);
    assertmsg("Nombre de ressorts", cloth2.getSpringCount(), 8 + 8 + 8 + 8 + 8 + 8);
    assertmsg("Valide", cloth2.check(), true);

    DiskCloth cloth3(
        1.0,
        { 0.0, 0.0, 0.0 },
        { 0.0, 2.0, 0.0 },
        1.0,
        0.3, 100,
        -M_PI
    );

    std::cout << "Tissu disque, pas angulaire -180deg:\n";
    std::cout << cloth3 << "\n";

    assertmsg("Nombre de masses", cloth3.getMassCount(), 1 + 2 + 2);
    // 2 ressorts se superposent, on considère que c'est le comportement normal
    // pour un disque de pas angulaire 180deg, puisque les ressorts représentent
    // en réalité des arc de cercle
    assertmsg("Nombre de ressorts", cloth3.getSpringCount(), 2 + 2 + 2 + 2);
    assertmsg("Valide", cloth3.check(), true);

    std::cout << "Valeurs incorrectes\n";
    assertexception("Pas negatif", DiskCloth(1, {}, {0, 1, 0}, -42, 0.3, 100), ValueError);
    assertexception("Gros pas", DiskCloth(1, {}, {0, 1, 0}, 1, 0.3, 100, 69), ValueError);
    assertexception("Tout petit pas", DiskCloth(1, {}, {0, 1, 0}, 1, 0.3, 100, 0.0), ValueError);

    return 0;
}
