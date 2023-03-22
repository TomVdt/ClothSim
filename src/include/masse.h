#pragma once
#include "include/vector3d.h"

#include <vector>
#include <iostream>

class Spring;

typedef std::vector<Spring*> ManySprings; 

class Masse {                                       // a faire: fichier tests
private:
    double mass;
    double lambda;
    Vector3D pos;
    Vector3D vel;
    Vector3D force;
    ManySprings springList;


public:
    Masse(double mass, double lambda = 0.0, const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D());

    Vector3D getPos() const {return pos;}
    Vector3D getVel() const {return vel;}
    Vector3D getForce() const {return force;}
    double getMass() const {return mass;}
    double getLambda() const {return lambda;}

    void setPos(const Vector3D& vec) { pos = vec; }
    void setVel(const Vector3D& vec) { vel = vec; }

    Vector3D acceleration() const;

    void connectSpring(Spring* spring);
    void disconnectSpring(Spring* spring);
    void disconnect();

    void addForce(const Vector3D& df);

    void updateForce();

    void display(std::ostream&) const;
};


std::ostream& operator<<(std::ostream& out, const Masse & mass);