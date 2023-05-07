#include "include/integrator.h"
#include "include/masse.h"
#include "include/vector3d.h"


void Integrator::move() {
    for (const auto& pos : newPos) {
        pos.first->setPos(pos.second);
    }
    newPos.clear();

    for (const auto& vel : newVel) {
        vel.first->setVel(vel.second);
    }
    newVel.clear();
}


void EulerCromerIntegrator::integrate(Masse& mass, double dt) {
    // Calcule le nouvel état
    const Vector3D vel(mass.getVel() + mass.acceleration() * dt);
    const Vector3D pos(mass.getPos() + vel * dt);

    // Rajoute les nouvelles positions et vitesses
    newPos.push_back(std::make_pair(&mass, pos));
    newVel.push_back(std::make_pair(&mass, vel));

}


/*void RK4Integrator::integrate(Masse& mass, double dt) {
    Vector3D posOrigin(mass.getPos());
    
    Vector3D k1(mass.getVel());
    Vector3D p1(mass.acceleration());
    Vector3D k2(k1 + (dt/2)*p1);

    Vector3D p2;




}*/






/*void NewmarkIntegrator::integrate(Masse& mass, double dt) {

    Vector3D vel0(mass.getVel());
    Vector3D pos0(mass.getPos());
    Vector3D acc0(mass.acceleration());

    Vector3D q;
    Vector3D pos(pos0);

    do {
        q = pos;
        mass.setVel(vel);
        mass.setPos(pos);

        // r

        Vector3D acc1(mass.acceleration());
        pos = 

    } while

    mass.setVel(vel);
    mass.setPos(pos);

}
*/


