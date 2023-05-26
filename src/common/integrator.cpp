#include "include/integrator.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/vector3d.h"
#include "include/util.h"


void EulerCromerIntegrator::integrate(Masse& mass, double dt, double time) const {  
    UNUSED(time);  
    // Calcule le nouvel état
    const Vector3D vel(mass.getVel() + mass.acceleration() * dt);
    const Vector3D pos(mass.getPos() + vel * dt);

    // Met les nouvelles positions et vitesses
    mass.setPos(pos);
    mass.setVel(vel);
}




void RK4Integrator::integrate(Masse& mass, double dt, double time) const {    
    Vector3D OGPos(mass.getPos());
    Vector3D v1(mass.getVel());
    Vector3D a1(mass.acceleration());

    Vector3D v2(v1 + (dt/2)*a1);
    Vector3D a2(mass.acceleration(time + dt/2, OGPos + (dt/2)*v1, v1 + (dt/2)*a1));

    Vector3D v3(v1 + (dt/2)*a2);
    Vector3D a3(mass.acceleration(time + dt/2, OGPos + (dt/2)*v2, v1 + (dt/2)*a2));

    Vector3D v4(v1 + dt*a3);
    Vector3D a4(mass.acceleration(time + dt, OGPos + dt*v3, v1 + dt*a3));

    mass.setPos(OGPos + (dt/6)*(v1 + 2*v2 + 2*v3 + v4));
    mass.setVel(v1 + (dt/6)*(a1 + 2*a2 + 2*a3 + a4));

}




void NewmarkIntegrator::integrate(Masse& mass, double dt, double time) const {
    const Vector3D OGPos(mass.getPos());
    const Vector3D OGVel(mass.getVel());
    Vector3D pos(OGPos);
    Vector3D vel(OGVel);
    Vector3D s(mass.acceleration());
    Vector3D q;

    do {
        q = pos;
        Vector3D r(mass.acceleration(time + dt, pos, vel));
        vel = OGVel + (dt/2)*(r + s);
        pos = OGPos + dt*OGVel + (dt*dt/3)*(0.5*r + s);

    } while(Vector3D::dist(pos, q) >= epsilon);

    mass.setPos(pos);
    mass.setVel(vel);
}


