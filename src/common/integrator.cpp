#include "include/integrator.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/vector3d.h"


void EulerCromerIntegrator::integrate(Masse& mass, double dt, ManyConstraints const& constraints, double time) const {    

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

    for(auto& constraint : constraints) {
        cloth.applyConstraint(*constraint, time);
    }

    for(size_t i(0); i < S; ++i) {
        Masse& mass(cloth.getMass(i));
        // Integration de la fonction
        integrate(mass, dt, constraints, time);
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
*/

/*
void RK4Integrator::integrate(Masse& mass, double dt, ManyConstraints const& constraints, double time) const {    

}
*/


void RK4Integrator::integrate(Cloth& cloth, double dt, ManyConstraints const& constraints, double time) const {
    size_t S(cloth.getMassCount());


    IntermediateVectors OGPositions;


    IntermediateVectors V1;
    IntermediateVectors A1;
    for(size_t i(0); i < S; ++i) {
        Masse& mass(cloth.getMass(i));

        OGPositions.push_back(mass.getPos());
        V1.push_back(mass.getVel());
        A1.push_back(mass.acceleration());
    }

    IntermediateVectors V2;
    IntermediateVectors A2;
    for(size_t i(0); i < S; ++i) {
        Masse& mass(cloth.getMass(i));

        mass.setPos(OGPositions[i] + (dt/2)*V1[i]);
        mass.setVel(V1[i] + (dt/2)*A1[i]);

        mass.updateForce();
        for(auto& constraint : constraints) {
            (*constraint).apply(mass, time + dt/2);
        }

        V2.push_back(mass.getVel());
        A2.push_back(mass.acceleration());

        // remets la masse à la position avant cette étape pour éviter les effets de bords sur les autres masses dans le calcul des accélérations
        mass.setPos(OGPositions[i]);
    }
    // mets les masses à la position correspondante à la fin de cette étape
    for(size_t i(0); i < S; ++i) {
        cloth.getMass(i).setPos(OGPositions[i] + (dt/2)*V1[i]);
    }
    

    IntermediateVectors V3;
    IntermediateVectors A3;
    for(size_t i(0); i < S; ++i) {
        Masse& mass(cloth.getMass(i));

        mass.setPos(OGPositions[i] + (dt/2)*V2[i]);
        mass.setVel(V1[i] + (dt/2)*A2[i]);

        mass.updateForce();
        for(auto& constraint : constraints) {
            (*constraint).apply(mass, time + dt/2);
        }

        V3.push_back(mass.getVel());
        A3.push_back(mass.acceleration());

        // remets la masse à la position avant cette étape pour éviter les effets de bords sur les autres masses
        mass.setPos(OGPositions[i] + (dt/2)*V1[i]);
    }
    // mets les masses à la position correspondante à la fin de cette étape
    for(size_t i(0); i < S; ++i) {
        cloth.getMass(i).setPos(OGPositions[i] + (dt/2)*V2[i]);
    }


    IntermediateVectors V4;
    IntermediateVectors A4;
    for(size_t i(0); i < S; ++i) {
        Masse& mass(cloth.getMass(i));

        mass.setPos(OGPositions[i] + dt*V3[i]);
        mass.setVel(V1[i] + dt*A3[i]);

        mass.updateForce();
        for(auto& constraint : constraints) {
            (*constraint).apply(mass, time + dt);
        }

        V4.push_back(mass.getVel());
        A4.push_back(mass.acceleration());

        // remets la masse à la position avant cette étape pour éviter les effets de bords sur les autres masses
        mass.setPos(OGPositions[i] + (dt/2)*V2[i]);
    }



    for(size_t i(0); i < S; ++i) {
        Masse& mass(cloth.getMass(i));

        mass.setPos(OGPositions[i] + (dt/6) * (V1[i] + 2*(V2[i]) + 2*(V3[i]) + V4[i]));
        mass.setVel(V1[i] + (dt/6) * (A1[i] + 2*(A2[i]) + 2*(A3[i]) + A4[i]));
    }

}






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


