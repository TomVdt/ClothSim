#pragma once
#include "include/vector3d.h"

#include <vector>
#include <iostream>

class Spring;

class Masse {
private:
    typedef std::vector<Spring*> ManySprings;
    double mass;
    double lambda;
    Vector3D pos;
    Vector3D vel;
    Vector3D force;
    ManySprings springList;


public:

    /* constructeur masse nécesssaire ensuite lambda, pos et vel peuvent etre par defaut
     * N'est pas propriétaire des springs */
    Masse(double mass, double lambda = 0.0, const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D());
    
    /* Pas de copie de masse: à quels ressorts connecter? */
    Masse(const Masse&) = delete;

    /* Position */
    Vector3D getPos() const { return pos; }

    /* Vitesse */
    Vector3D getVel() const { return vel; }
    
    /* Force */
    Vector3D getForce() const { return force; }
    
    /* Masse */
    double getMass() const { return mass; }
    
    /* Coefficient de frottement */
    double getLambda() const { return lambda; }

    /* Set postion */
    void setPos(const Vector3D& vec) { pos = vec; }
    
    /* Set vitesse*/
    void setVel(const Vector3D& vec) { vel = vec; }

    /* Acceleration de la masse */
    Vector3D acceleration() const;


    /* Rajoute une force à cette masse */
    void addForce(const Vector3D& df);

    /* Met à jour la force sur la masse avec
     * mg, -lambda*v et la somme des forces de rappel */
    void updateForce();

    /* Connecte un nouveau ressort à la masse en vérifiant
     * s'il est valide ou s'il n'est pas déjà connecté */
    void connectSpring(Spring& spring);

    /* Déconnecte la masse du ressort donné */
    void disconnectSpring(const Spring& spring);
    
    /* Déconnecte tous les ressorts */
    void disconnect();

    /* Vérifie si le ressort est connecté */
    bool springConnected(const Spring& spring) const;

    /* Alloue dynamiquement une copie de la masse ne contenant *pas* les ressorts */
    Masse* copy() const;

    /* Représentation de la masse dans un flot */
    void display(std::ostream& out, size_t level = 0) const;
};

/* surcharge externe de l'opérateur << pour les masses */
std::ostream& operator<<(std::ostream& out, const Masse& mass);