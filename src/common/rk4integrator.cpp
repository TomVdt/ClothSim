#include "include/rk4integrator.h"
#include "include/mass.h"
#include "include/vector3d.h"

void RK4Integrator::integrate(Mass& mass, double dt, double time) const {
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
