#include "include/vector3d.h"
#include "include/cloth.h"
#include "include/rectcloth.h"
#include "include/constraint.h"
#include "include/system.h"
#include "include/textrenderer.h"

int main() {
    Cloth* cloth2(new RectCloth(
        0.3125,
        Vector3D(3, 0, 0), Vector3D(0, 0, 3),
        Vector3D(),
        0.3,
        1.0,
        1.0,
        1.0
    ));

    Constraint* constraint3(new HookConstraint(
        Vector3D(),
        0.1
    ));

    Constraint* constraint4(new HookConstraint(
        Vector3D(0, 0, 3),
        0.1
    ));

    Constraint* constraint5(new SineImpulsionConstraint(
        Vector3D(3, 0, 0),
        0.5,
        0.0, 2.0,
        Vector3D(0, 30, 0),
        1.5,
        {
            cloth2
        }
    ));

    Constraint* constraint6(new SineImpulsionConstraint(
        Vector3D(3, 0, 3),
        0.5,
        0.0, 2.0,
        Vector3D(0, 30, 0),
        1.5,
        {
            cloth2
        }
    ));

    System system;
    system.addCloth(std::unique_ptr<Cloth>(cloth2));
    system.addConstraint(std::unique_ptr<Constraint>(constraint3));
    system.addConstraint(std::unique_ptr<Constraint>(constraint4));
    system.addConstraint(std::unique_ptr<Constraint>(constraint5));
    system.addConstraint(std::unique_ptr<Constraint>(constraint6));

    TextRenderer renderer;
    EulerCromerIntegrator integrator;

    for (double i(0.0); i < 2.0; i += 0.01) {
        system.step(integrator, 0.01);
        system.draw(renderer);
    }

    return 0;
}