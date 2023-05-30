#include "include/cloth.h"
#include "include/eulercromerintegrator.h"
#include "include/hookconstraint.h"
#include "include/mass.h"
#include "include/system.h"
#include "include/textrenderer.h"
#include "include/vector3d.h"

#include <iostream>
#include <memory>

// "TextViewer" -> common/include/textrenderer.h, common/textrenderer.cpp

int main() {
    std::unique_ptr<Cloth> cloth(std::make_unique<Cloth>());

    cloth->addMass(0.33, 0.3, Vector3D(0, -3, 0), Vector3D(0, 0, 0));
    cloth->addMass(1, 0.3, Vector3D(-0.5, 0, 0), Vector3D(0, 0, 0));
    cloth->addMass(1, 0.3, Vector3D(0.5, 0, 0), Vector3D(0, 0, 0));
    cloth->connect(0, 1, 0.6, 2.5);
    cloth->connect(0, 2, 0.6, 2.5);

    EulerCromerIntegrator integrator;
    System system;
    system.addCloth(std::move(cloth));
    system.addConstraint(std::make_unique<HookConstraint>(Vector3D(-0.5, 0, 0), 0.1));
    system.addConstraint(std::make_unique<HookConstraint>(Vector3D(0.5, 0, 0), 0.1));

    TextRenderer renderer(std::cout);

    for (int i(0); i < 251; ++i) {
        system.step(integrator, 0.1);
        std::cout << "===============\nt = " << 0.1 * i << std::endl;
        system.draw(renderer);
    }

    return 0;
}
