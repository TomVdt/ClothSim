#include "include/integrator.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/vector3d.h"

#include <vector>


void EulerCromerIntegrator::integrate(Masse& mass, double dt, double time) const {
    // Calcule le nouvel état
    const Vector3D vel(mass.getVel() + mass.acceleration() * dt);
    const Vector3D pos(mass.getPos() + vel * dt);

    // Met les nouvelles positions et vitesses
    mass.setPos(pos);
    mass.setVel(vel);
    
}

void EulerCromerIntegrator::integrate(Cloth& cloth, double dt, ManyConstraints const& constraints, double time) const {
    size_t S(cloth.getMassCount());
    cloth.updateForce();
    // Fonction à integrer (force + contraintes)
    for(auto& constraint : constraints) {
        cloth.applyConstraint(*constraint, time);
    }

    for(size_t i(0); i < S; ++i) {
        Masse& mass(cloth.getMass(i));
        // Integration de la fonction
        integrate(mass, dt, time);
    }
}




/*
void RK4Integrator::changeMass(Masse& mass, Vector3D const& posOrigin, Vector3D const& velOrigin, 
                                Vector3D const& k, Vector3D const& p, double dt, double time) {
    mass.setPos(posOrigin + dt*k);
    mass.setVel(velOrigin + dt*p);
    mass.updateForce();
    mass.applyConstraints(time + dt);
}


void RK4Integrator::integrate(Cloth& cloth, double dt, ManyConstraints constraints, double time) const {
    size_t S(cloth.getMassCount());

    std::vector<Vector3D&> K1;


    



    Vector3D posOrigin(mass.getPos());
    Vector3D velOrigin(mass.getVel());
    
    // Calcule les vecteurs intermédiaires nécessitant de modifier la masse
    Vector3D k1(velOrigin);
    Vector3D p1(mass.acceleration());
    Vector3D k2(velOrigin + (dt/2)*p1);

    changeMass(mass, posOrigin, velOrigin, k1, p1, dt/2, time);
    Vector3D p2(mass.acceleration());

    Vector3D k3(velOrigin + (dt/2)*p2);

    changeMass(mass, posOrigin, velOrigin, k2, p2, dt/2, time);
    Vector3D p3(mass.acceleration());

    Vector3D k4(velOrigin + dt*p3);

    changeMass(mass, posOrigin, velOrigin, k3, p3, dt, time);
    Vector3D p4(mass.acceleration());

    // Calcule les nouvelles position et vitesse et les enregistre pour les modifier dans move()
    const Vector3D pos(posOrigin + (dt/6)*(k1 + 2*k2 + 2*k3 + k4));
    const Vector3D vel(velOrigin + (dt/6)*(p1 + 2*p2 + 2*p3 + p4));

    newPos.push_back(std::make_pair(&mass, pos));
    newVel.push_back(std::make_pair(&mass, vel));


}
*/





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


