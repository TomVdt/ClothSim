#include "include/eulercromerintegrator.h"
#include "include/mass.h"
#include "include/util.h"
#include "include/vector3d.h"

void EulerCromerIntegrator::integrate(Mass& mass, double dt, double time) const {
    UNUSED(time);
    // Calcule le nouvel état
    const Vector3D vel(mass.getVel() + mass.acceleration() * dt);
    const Vector3D pos(mass.getPos() + vel * dt);

    // Met les nouvelles positions et vitesses
    mass.setPos(pos);
    mass.setVel(vel);
}



