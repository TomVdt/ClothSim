#include "include/integrator.h"
#include "include/masse.h"
#include "include/vector3d.h"


void EulerCromerIntegrator::integrate(Masse* mass, double dt) const {
    // Calcule le nouvel état
    const Vector3D vel(mass->getVel() + mass->acceleration() * dt);
    const Vector3D pos(mass->getPos() + vel * dt);

    // Met à jour la masse
    mass->setVel(vel);
    mass->setPos(pos);
}
