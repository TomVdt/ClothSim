#include "include/cloth.h"
#include "include/constraint.h"
#include "include/eulercromerintegrator.h"
#include "include/hookconstraint.h"
#include "include/rectcloth.h"
#include "include/sineimpulsionconstraint.h"
#include "include/system.h"
#include "include/textrenderer.h"
#include "include/vector3d.h"

#include <fstream>

int main() {
    Cloth* cloth1(new RectCloth(
        0.3125,
        Vector3D(3, 0, 0), Vector3D(0, 0, 3),
        Vector3D(),
        0.3,
        1.0,
        1.0,
        1.0
    ));

    Constraint* constraint1(new HookConstraint(
        Vector3D(),
        0.1
    ));

    Constraint* constraint2(new HookConstraint(
        Vector3D(0, 0, 3),
        0.1
    ));

    Constraint* constraint3(new SineImpulsionConstraint(
        Vector3D(3, 0, 0),
        0.5,
        0.0, 2.0,
        Vector3D(0, 30, 0),
        1.5,
        {
            cloth1
        }
    ));

    Constraint* constraint4(new SineImpulsionConstraint(
        Vector3D(3, 0, 3),
        0.5,
        0.0, 2.0,
        Vector3D(0, 30, 0),
        1.5,
        {
            cloth1
        }
    ));

    System system;
    system.addCloth(std::unique_ptr<Cloth>(cloth1));
    system.addConstraint(std::unique_ptr<Constraint>(constraint1));
    system.addConstraint(std::unique_ptr<Constraint>(constraint2));
    system.addConstraint(std::unique_ptr<Constraint>(constraint3));
    system.addConstraint(std::unique_ptr<Constraint>(constraint4));

    std::ofstream file("output/testConstraint2.txt");
    TextRenderer renderer(file);
    EulerCromerIntegrator integrator;

    for (double i(0.0); i < 2.0; i += 0.01) {
        system.step(integrator, 0.01);
        system.draw(renderer);
    }

    file.close();
    return 0;
}