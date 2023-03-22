#pragma once
#include "include/vector3d.h"
#include "include/spring.h"
#include <vector>
#include <memory>
#include <iostream>

typedef std::vector<Spring*> ManySprings; 


class Masse {                                       // a faire: fichier tests
private:
    Vector3D pos;
    Vector3D vel;
    double mass;
    double lambda;
    Vector3D force;
    ManySprings springList;


public:
    Masse(double mass, double lambda, const Vector3D& pos, const Vector3D& vel);


    Vector3D getPos() const {return pos;};
    Vector3D getVel() const {return vel;};
    Vector3D getForce() const {return force;};
    double getMass() const {return mass;};
    double getLambda() const {return lambda};

    Vector3D acceleration() const;


    void addForce(const Vector3D& df);

    void updateForce();

};


std::ostream& operator<<(std::ostream& out, const Masse & mass);