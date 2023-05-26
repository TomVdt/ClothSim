#include "include/diskcloth.h"
#include "include/chaincloth.h"
#include "include/rectcloth.h"
#include "include/compositecloth.h"
#include "include/exceptions.h"
#include "include/test.h"

#include <iostream>
#include <memory>
#include <cmath>

int main() {
    int massCount(0);
    int springCount(0);
    DiskCloth* cloth1 = new DiskCloth(
        1.0,
        { 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        1.0,
        0.3, 100,
        90.0 * M_PI / 180.0
    );
    massCount += cloth1->getMassCount();
    springCount += cloth1->getSpringCount();

    ChainCloth* cloth2 = new ChainCloth(
        1.0, 0.3, 100, 1,
        {
            { 0.0, 0.1, 0.0 },
            { 0.0, 1.0, 0.0 },
            { 0.0, 2.0, 0.0 },
            { 0.0, 3.0, 0.0 },
            { 0.0, 4.0, 0.0 },
            { 0.0, 4.9, 0.0 }
        }
    );
    massCount += cloth2->getMassCount();
    springCount += cloth2->getSpringCount();

    RectCloth* cloth3 = new RectCloth(
        1.0,
        { 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0 },
        { 0.0, 5.0, 0.0 },
        0.3, 1, 100, 1.0
    );
    massCount += cloth3->getMassCount();
    springCount += cloth3->getSpringCount();

    CompositeCloth cloth4(100, 0.2);

    cloth4.linkCloth(std::unique_ptr<Cloth>(cloth1));
    cloth4.linkCloth(std::unique_ptr<Cloth>(cloth2));
    cloth4.linkCloth(std::unique_ptr<Cloth>(cloth3));

    std::cout << "Tissu composé:\n";
    std::cout << cloth4 << "\n";

    assertmsg("Nombre de masses", cloth4.getMassCount(), massCount);
    assertmsg("Nombre de ressorts", cloth4.getSpringCount(), springCount + 2);
    assertmsg("Valide", cloth4.check(), true);

    ChainCloth* cloth5 = new ChainCloth(
        1.0, 0.3, 100, 1.0,
        {
            { 420, 69, 42 }
        }
    );

    assertexception("Trop loin", cloth4.linkCloth(std::unique_ptr<Cloth>(cloth5)), ConnectionError);

    return 0;
}
