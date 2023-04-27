#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/integrator.h"
#include "include/textrenderer.h"
#include "include/system.h"
#include "include/cloth.h"

#include <iostream>
#include <fstream>
#include <memory>

int main() {
    std::unique_ptr<Cloth> cloth(std::make_unique<Cloth>());

    cloth->addMass(std::make_unique<Masse>(0.33, 0.3, Vector3D(0, -3, 0), Vector3D(0, 0, 0)));
    cloth->addMass(std::make_unique<Masse>(1, 0.3, Vector3D(-2, 0, 0), Vector3D(0, 0, 0)));
    cloth->addMass(std::make_unique<Masse>(1, 0.3, Vector3D(0.5, 0, 0), Vector3D(0, 0, 0)));
    cloth->connect(0, 1, 0.6, 2.5);
    cloth->connect(0, 2, 0.6, 2.5);

    EulerCromerIntegrator integrator;
    System system;
    system.addCloth(std::move(cloth));
    // system.addConstraint(mass2);
    // system.addConstraint(mass3);

    TextRenderer renderer(std::cout);

    for (int i(0); i < 251; ++i) {
        system.step(integrator, 0.1);
        std::cout << "===============\nt = " << 0.1 * i << std::endl;
        system.draw(renderer);
    }

    return 0;
}
