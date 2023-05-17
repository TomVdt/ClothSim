#include "include/window.h"
#include "include/cloth.h"
#include "include/diskcloth.h"
#include "include/constraint.h"

int main() {
    // Create window
    Window window;

    // Create system
    System system;
    Cloth* cloth1(new DiskCloth(
        1.0,
        Vector3D(),
        Vector3D(0.0, 100.0, 0.0),
        2.0,
        0.3,
        100.0
    ));

    Constraint* constraint1(new HookConstraint(
        Vector3D(),
        0.1
    ));

    system.addCloth(std::unique_ptr<Cloth>(cloth1));
    system.addConstraint(std::unique_ptr<Constraint>(constraint1));

    // Give system to window for visualisation
    window.setSystem(std::move(system));

    // Execute update & draw loop
    window.run();

    return 0;
}
