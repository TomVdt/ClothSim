#include "include/newmarkintegrator.h"
#include "include/mass.h"
#include "include/vector3d.h"

void NewmarkIntegrator::integrate(Mass& mass, double dt, double time) const {
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
