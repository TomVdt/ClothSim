#include "include/constants.h"
#include "include/masse.h"
#include <iostream>

using CONSTANTS::g;
using std::endl;

// constructeur masse nécesssaire ensuite lambda, pos et vel peuvent etre par defaut
Masse::Masse(double mass, double lambda = 0.0, const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D())
    : mass(mass),
    lambda(lambda),
    pos(pos),
    vel(vel),
    force(mass * g),
    springList()             // TODO initialiser les springs lol fun
{}


// ajoute df à la force du vecteur
void Masse::addForce(const Vector3D& df) {
    force += df;
}


// renvoie l'acceleration
Vector3D Masse::acceleration() const {
    return force/mass;
}


// met à jour la force sur la masse avec mg, -lambda*v et la somme des forces de rappel
void Masse::updateForce() {
    Vector3D springForce;
    for (const auto& spring : springList) {
        springForce += spring->springForce(this);
    }

    force = mass*g - lambda*vel + springForce;

}


// surcharge externe de << pour les masses
std::ostream& operator<<(std::ostream & out, const Masse & mass) {
    out << "masse: " << mass.getMass() << endl
        << "lambda: " << mass.getLambda() << endl
        << "position: " << mass.getPos() << endl 
        << "vitesse: " << mass.getVel() << endl
        << "force: " << mass.getForce() << endl;
    return out;
}
