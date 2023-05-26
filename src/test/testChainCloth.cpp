#include "include/chaincloth.h"
#include "include/test.h"

#include <iostream>

int main() {
    ChainCloth cloth(
        1.0, 0.3, 100, 1,
        {
            {0.0, 0.0, 0.0},
            {1.0, 0.0, 0.0},
            {2.0, 0.0, 0.0},
            {2.0, 1.0, 0.0},
            {2.0, 2.0, 0.0}
        }
    );

    std::cout << "Tissu chaine:\n";
    std::cout << cloth << "\n";

    assertmsg("Nombre de masses", cloth.getMassCount(), 5);
    assertmsg("Nombre de ressorts", cloth.getSpringCount(), 4);
    assertmsg("Valide", cloth.check(), true);

    return 0;
}
