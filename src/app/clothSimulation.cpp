#include "include/attractionconstraint.h"
#include "include/chaincloth.h"
#include "include/cloth.h"
#include "include/compositecloth.h"
#include "include/diskcloth.h"
#include "include/hookconstraint.h"
#include "include/impulsionconstraint.h"
#include "include/rectcloth.h"
#include "include/sineimpulsionconstraint.h"
#include "include/vector3d.h"
#include "include/window.h"

#include <vector>

int main() {
    // Create system
    System system;

    // Disk
    system.addCloth(std::make_unique<DiskCloth>(
        0.2,
        Vector3D(),
        Vector3D(0.0, 10.0, 0.0),
        2.0,
        0.3,
        100.0
    ));

    system.addConstraint(std::make_unique<HookConstraint>(
        Vector3D(),
        0.1
    ));

    // Rectangle
    system.addCloth(std::make_unique<RectCloth>(
        0.1,
        Vector3D(20, 10, 4),
        Vector3D(-4.8, 3.2, 16),
        Vector3D(20, -5, -10),
        0.3, 1.5, 100, 1.5
    ));

    system.addConstraint(std::make_unique<HookConstraint>(
        Vector3D(20, -5, -10), 0.8
    ));

    system.addConstraint(std::make_unique<HookConstraint>(
        Vector3D(40, 5, -6), 0.8
    ));

    system.addConstraint(std::make_unique<HookConstraint>(
        Vector3D(15.2, -1.8, 6), 0.8
    ));

    system.addConstraint(std::make_unique<HookConstraint>(
        Vector3D(35.2, 8.2, 10), 0.8
    ));

    // Spiraly-chain
    Cloth* cloth0(new ChainCloth(
        1.0, 0.3, 100, 2.0,
        std::vector<Vector3D>({
            Vector3D(-20, 15, 0),
            Vector3D(-20, 15, 2),
            Vector3D(-18, 15, 2),
            Vector3D(-18, 15, 0),
            Vector3D(-18, 15, -2),
            Vector3D(-20, 15, -2),
            Vector3D(-22, 15, -2),
            Vector3D(-22, 15, 0),
            Vector3D(-22, 15, 2),
            Vector3D(-22, 15, 4),
            Vector3D(-20, 15, 4),
            Vector3D(-18, 15, 4),
            Vector3D(-16, 15, 4),
            Vector3D(-16, 15, 2),
            Vector3D(-16, 15, 0),
            Vector3D(-16, 15, -2),
        })
    ));

    system.addConstraint(std::make_unique<HookConstraint>(
        Vector3D(-20, 15, 0), 0.1
    ));

    system.addConstraint(std::make_unique<SineImpulsionConstraint>(
        Vector3D(-16, 15, -2), 0.1,
        0.0, 10.0,
        Vector3D(-5, 20, -5),
        1,
        std::vector<Cloth*>({ cloth0 })
    ));

    system.addCloth(std::unique_ptr<Cloth>(cloth0));

    // Flag
    Cloth* cloth1(new RectCloth(
        1.0,
        Vector3D(30, 0, 0),
        Vector3D(0, 20, 0),
        Vector3D(0, 40, 20),
        0.3, 1.0, 200, 1.0
    ));

    std::vector<Vector3D> pos;
    for (int i(0); i <= 60; i += 2) {
        pos.emplace_back(-0.1, i, 20);
    }

    Cloth* cloth2(new ChainCloth(
        1.0, 0.3, 100, 2.0,
        pos
    ));

    CompositeCloth* cloth3(new CompositeCloth(100, 0.2));
    cloth3->linkCloth(std::unique_ptr<Cloth>(cloth1));
    cloth3->linkCloth(std::unique_ptr<Cloth>(cloth2));

    system.addCloth(std::unique_ptr<Cloth>(cloth3));

    system.addConstraint(std::make_unique<ImpulsionConstraint>(
        Vector3D(15, 50, 20),
        20, 0.0, 10.0,
        Vector3D(2, -1, 0.5),
        std::vector<Cloth*>({ cloth3 })
    ));

    for (int i(0); i < 30; ++i) {
        system.addConstraint(std::make_unique<HookConstraint>(
            Vector3D(i, 60, 20), 0.1
        ));
        system.addConstraint(std::make_unique<HookConstraint>(
            Vector3D(-0.1, 2 * i, 20), 0.1
        ));
    }

    // Ejection par aide gravitationelle
    system.addCloth(std::make_unique<ChainCloth>(
        1.0, 0.3, 100, 1.0,
        std::vector<Vector3D>({
            Vector3D(-20, 40, 20),
            Vector3D(-20, 39, 20),
            Vector3D(-20, 38, 20),
            Vector3D(-20, 37, 20),
            Vector3D(-20, 36, 20),
            Vector3D(-20, 35, 20),
            Vector3D(-20, 34, 20),
            Vector3D(-20, 33, 20),
            Vector3D(-20, 32, 20),
            Vector3D(-20, 31, 20),
            Vector3D(-20, 30, 20)
        })
    ));

    system.addConstraint(std::make_unique<AttractionConstraint>(
        Vector3D(-28, 21, 20), 10, 666, 0.01
    ));

    // Charges opposées
    system.addCloth(std::make_unique<DiskCloth>(
        1.0,
        Vector3D(0, 0, -25),
        Vector3D(0, 10, 2),
        1, 0.3, 100,
        // 30 deg
        0.523598776
    ));

    system.addConstraint(std::make_unique<AttractionConstraint>(
        Vector3D(0, -10, -30), 10, -666, 0.01
    ));

    // Create window
    Window window(std::move(system));

    // Execute update & draw loop
    window.run();

    return 0;
}
