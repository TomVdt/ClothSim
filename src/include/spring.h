#pragma once
#include "include/vector3d.h"

#include <vector>
#include <iostream>

class Masse;

class Spring {
private:
    /* Constante de raideur */
    double k;

    /* Longueur de repos */
    double l0;

    /* Masse de départ */
    Masse* mass1;

    /* Masse d'arrivée */
    Masse* mass2;

public:
    /* Constructeur
     * Initialise constante de raideur et longueur à vide
     * Les extremités peuvent être données 
     * Le ressort n'est pas propriétaire des masses */
    Spring(double k, double l0) : k(k), l0(l0), mass1(nullptr), mass2(nullptr) {}
    Spring(double k, double l0, Masse& mass1, Masse& mass2) : k(k), l0(l0), mass1(&mass1), mass2(&mass2) {}

    /* Pas de copie de ressorts
     * Comment / pourquoi copier des masses?
     * Le ressort devrait-il garder les mêmes masses? */
    Spring(const Spring&) = delete;

    /* Getter pour constante de raideur */
    double getK() const { return k; }

    /* Getter pour la longueur de repos */
    double getL0() const { return l0; }

    /* Retourne la force exercée par le ressort sur une masse */
    Vector3D springForce(Masse&) const;

    /* Rajoute des masses aux extrémités */
    void connect(Masse&, Masse&);

    /* Enlève les masses des extrémités  */
    void disconnect();

    /* test si cette masse est connectée */
    bool massConnected(Masse&);

    /* Le ressort est-il valide?
     * Un ressort valide est un ressort:
     * - Où les extrémités ne sont pas de `nullptr`
     * - Où les extrémités sont des masses différentes */
    bool valid() const;

    /* Représentation du ressort dans un flot */
    void display(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const Spring&);
