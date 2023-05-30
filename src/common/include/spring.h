#pragma once
#include "include/drawable.h"
#include "include/vector3d.h"

#include <iostream>
#include <vector>

class Mass;

class Spring: public Drawable {
private:
    /**
     * Constante de raideur du ressort
    */
    double k;

    /**
     * Longueur de repos du ressort
    */
    double l0;

    /**
     * Masse de départ
    */
    const Mass& mass1;

    /**
     * Masse d'arrivée
    */
    const Mass& mass2;

    /**
     * Identificateur unique du ressort à partir de la variable de classe COUNT
    */
    int id;

    /**
     * Variable de classe permettant de donner des identificateurs uniques aux ressorts 
     * en comptant le nombre de ressorts crées
    */
    static int COUNT;

public:
    /** 
     * Constructeur de ressort
     * Initialise la constante de raideur et la longueur à vide
     * Les masses des extremités doivent être données et ne peuvent pas etre modifiées après
     * Pour supprimer une connection, simplement supprimer la référence à cette connection 
    */
    Spring(double k, double l0, const Mass& mass1, const Mass& mass2): k(k), l0(l0), mass1(mass1), mass2(mass2), id(COUNT++) {}

    /**
     * Pas de copie de ressorts
     * Un autre ressort agissant sur les même masses n'a pas trop de sens 
    */
    Spring(const Spring&) = delete;

    /**
     * Pas de copie de ressorts
     * Un autre ressort agissant sur les même masses n'a pas trop de sens 
    */
    Spring& operator=(const Spring&) = delete;

    /**
     * Destructeur par défaut suffisant
    */
    virtual ~Spring() = default;

    /**
     * Constante de raideur k 
    */
    double getK() const { return k; }

    /**
     * Longueur de repos l0
    */
    double getL0() const { return l0; }

    /**
     * Id unique du ressort
    */
    int getId() const { return id; }

    /**
     * Retourne la position de la masse de départ
    */
    const Vector3D& getStartPos() const { return mass1.getPos(); }

    /**
     * Retourne la position de la masse d'arrivée
    */
    const Vector3D& getEndPos() const { return mass2.getPos(); }

    /**
     * Retourne la force exercée par le ressort sur une masse
    */
    Vector3D springForce(const Mass&) const;

    /**
     * Retourne l'énergie potentielle du ressort
    */
    double energy() const;

    /**
     * Retourne la longueur du ressort (écart entre les masses)
    */
    double length() const;

    /**
     * Test si la masse fournie est connectée au ressort
    */
    bool massConnected(const Mass&) const;

    /**
     * Test si le ressort est valide, c'est-à-dire si ses extrêmités sont différentes
    */
    bool valid() const;
    
    /**
     * Vérifie que les extremités soient connectées au ressort
    */
    bool areEndsValid() const;

    /**
     * Représentation du ressort dans un flot
    */
    void display(std::ostream& out, size_t level = 0) const;

    /**
     * Dessine le ressort sur le support fourni
    */
    virtual void draw(Renderer& dest) override;
};

/**
 * Surcharge de l'opérateur << pour afficher un ressort dans un flot
*/
std::ostream& operator<<(std::ostream&, const Spring&);
