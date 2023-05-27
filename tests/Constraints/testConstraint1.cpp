#include "include/chaincloth.h"
#include "include/cloth.h"
#include "include/constraint.h"
#include "include/integrator.h"
#include "include/system.h"
#include "include/textrenderer.h"
#include "include/vector3d.h"

#include <fstream>

int main() {
    Cloth* cloth1(new ChainCloth(
        1, 0.3,
        3.0, 1.0,
        {
            Vector3D(-0.5, 0, 0),
            Vector3D(0, -3, 0),
            Vector3D(0.5, 0, 0)
        }
    ));

    Constraint* constraint1(new HookConstraint(
        Vector3D(-0.5, 0, 0),
        0.1
    ));

    Constraint* constraint2(new HookConstraint(
        Vector3D(0.5, 0, 0),
        0.1
    ));

    System system;
    system.addCloth(std::unique_ptr<Cloth>(cloth1));
    system.addConstraint(std::unique_ptr<Constraint>(constraint1));
    system.addConstraint(std::unique_ptr<Constraint>(constraint2));

    std::ofstream file("output/testConstraint1.txt");
    TextRenderer renderer(file);
    EulerCromerIntegrator integrator;

    for (double i(0.0); i < 2.0; i += 0.01) {
        system.step(integrator, 0.01);
        system.draw(renderer);
    }

    file.close();
    return 0;
}