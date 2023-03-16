#include "include/constants.h"
#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"

using CONSTANTS::g;


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
        springForce += spring->springForce(this)
    }

    force = mass*g - lambda*vel + springForce

}
