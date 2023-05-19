#pragma once
#include "include/vector3d.h"
#include "include/drawable.h"
#include "include/masse.h"

#include <vector>
#include <iostream>

class Masse;

class Spring: public Drawable {
private:
    /* Constante de raideur */
    double k;

    /* Longueur de repos */
    double l0;

    /* Masse de départ */
    const Masse& mass1;

    /* Masse d'arrivée */
    const Masse& mass2;

public:
    /* Constructeur
     * Initialise constante de raideur et longueur à vide
     * Les extremités doivent être données et ne peuvent pas etre modifiées après
     * Pour supprimer une connection, simplement supprimer la référence à cette connection */
    Spring(double k, double l0, const Masse& mass1, const Masse& mass2): k(k), l0(l0), mass1(mass1), mass2(mass2) {}

    /* Pas de copie de ressorts
     * Un autre ressort agissant sur les même masses n'a pas trop de sens */
    Spring(const Spring&) = delete;
    Spring& operator=(const Spring&) = delete;

    virtual ~Spring() = default;

    /* Getter pour constante de raideur */
    double getK() const { return k; }

    /* Getter pour la longueur de repos */
    double getL0() const { return l0; }

    const Vector3D& getStartPos() const { return mass1.getPos(); }

    const Vector3D& getEndPos() const { return mass2.getPos(); }

    /* Retourne la force exercée par le ressort sur une masse */
    Vector3D springForce(const Masse&) const;

    /**
     * Retourne la longueur du ressort (écart entre les masses)
    */
    double length() const;

    /* test si cette masse est connectée au ressort */
    bool massConnected(const Masse&) const;

    /* Le ressort est-il valide?
     * Un ressort valide est un ressort:
     * - Où les extrémités sont des masses différentes */
    bool valid() const;
    
    /* Vérifie que les extremités soient connectées au ressort */
    bool areEndsValid() const;

    /* Représentation du ressort dans un flot */
    void display(std::ostream& out, size_t level = 0) const;

    virtual void draw(Renderer& dest) override;
};

std::ostream& operator<<(std::ostream&, const Spring&);
