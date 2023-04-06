#pragma once
#include "include/vector3d.h"

#include <vector>
#include <iostream>

class Mass;

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
     * Si des masses (optionnelles) sont données, vérifie la configuration
     * avant de connecter le ressort aux masses */
    Spring(double k, double l0, Masse* mass1 = nullptr, Masse* mass2 = nullptr);

    /* Destructeur par défaut virtuel
     * Virtuel  */
    virtual ~Spring() = default;

    /* Pas de copie de ressorts
     * Comment / pourquoi copier des masses?
     * Le ressort devrait-il garder les mêmes masses? */
    Spring(const Spring&) = delete;

    /* Getter pour constante de raideur */
    double getK() const { return k; }

    /* Getter pour la longueur de repos */
    double getL0() const { return l0; }

    /* Retourne la force exercée par le ressort sur une masse */
    Vector3D springForce(Masse*) const;

    /* Rajoute des masses aux extrémités
     * Connecte le ressort aux masses si la configuration est valide */
    void connect(Masse* mass1, Masse* mass2);

    /* Enlève les masses des extrémités
     * Déconnecte le ressort des masses si la configuration est valide */
    void disconnect();

    /*test si cette masse est connectée*/
    bool massConnected(Masse* mass);

    /* Le ressort est-il valide?
     * Un ressort valide est un ressort:
     * - Où les extrémités ne sont pas de `nullptr`
     * - Où les extrémités sont des masses différentes */
    bool valid() const;

    /* Représentation du ressort dans un flot */
    void display(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const Spring&);
