#include "include/attractionconstraint.h"
#include "include/cloth.h"
#include "include/constraint.h"
#include "include/eulercromerintegrator.h"
#include "include/rectcloth.h"
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

    Constraint* constraint1(new AttractionConstraint(
        Vector3D(-1, -5, -1),
        25,
        50,
        5
    ));

    System system;
    system.addCloth(std::unique_ptr<Cloth>(cloth1));
    system.addConstraint(std::unique_ptr<Constraint>(constraint1));

    std::ofstream file("output/testConstraint3.txt");
    TextRenderer renderer(file);
    EulerCromerIntegrator integrator;

    for (double i(0.0); i < 2.0; i += 0.01) {
        system.step(integrator, 0.01);
        system.draw(renderer);
    }

    file.close();
    return 0;
}