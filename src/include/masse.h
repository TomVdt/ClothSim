#pragma once
#include "include/vector3d.h"
#include <vector>
#include <iostream>


class Spring;

typedef std::vector<Spring*> ManySprings; 


class Masse {
private:
    double mass;
    double lambda;
    Vector3D pos;
    Vector3D vel;
    Vector3D force;
    ManySprings springList;


public:

    /* constructeur masse nécesssaire ensuite lambda, pos et vel peuvent etre par defaut */
    Masse(double mass, double lambda = 0.0, const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D());
    virtual ~Masse() = default;


    /* getters de la masse */
    Vector3D getPos() const {return pos;}
    Vector3D getVel() const {return vel;}
    Vector3D getForce() const {return force;}
    double getMass() const {return mass;}
    double getLambda() const {return lambda;}

    /* setters de la masse */
    void setPos(const Vector3D& vec) { pos = vec; }
    void setVel(const Vector3D& vec) { vel = vec; }

    /* renvoie l'acceleration de la masse */
    Vector3D acceleration() const;


    /* rajoute une force à cette masse */
    void addForce(const Vector3D& df);

    /* met à jour la force sur la masse avec 
    mg, -lambda*v et la somme des forces de rappel */
    void updateForce();


    /* affichage chaque attribut de la masse et des pointeurs vers les ressorts*/
    void display(std::ostream&) const;

    /* connecte un nouveau ressort à la masse en vérifiant 
    s'il est valide ou s'il n'est pas déjà connecté */
    void connectSpring(Spring* spring);
    /* trouve le ressort et le déconnecte */
    void disconnectSpring(Spring* spring);
    /* déconnecte tous les ressorts */
    void disconnect();

};

/* surcharge externe de l'opérateur << pour les masses */
std::ostream& operator<<(std::ostream& out, const Masse & mass);