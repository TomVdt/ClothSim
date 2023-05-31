#pragma once
#include "include/drawable.h"
#include "include/vector3d.h"

#include <iostream>

class Mass;
class Cloth;
class Renderer;

class Constraint: public Drawable {
private:
    /**
     * Position où la contrainte doit s'appliquer
    */
    Vector3D pos;

    /**
     * Rayon d'action de la contrainte
    */
    double radius;

public:
    /**
     * Constructeur prenant la position d'application de la contrainte et son rayon d'action
    */
    Constraint(const Vector3D& pos, double radius);

    /**
     * Destructeur par défaut, virtuel pour l'héritage
    */
    virtual ~Constraint() = default;

    /**
     * Getter sur la position d'application de la contrainte
    */
    const Vector3D& getPos() const { return pos; }

    /**
     * Getter sur le rayon d'action de la contrainte
    */
    double getRadius() const { return radius; }

    /**
     * Retourne un booléen indiquant si la masse fournie est concernée par la contrainte ou non
    */
    virtual bool isInRange(const Mass& mass) const;

    /**
     * Applique sur toutes les masses d'un tissu cette contrainte
    */
    void apply(Cloth& cloth, double time) const;

    /**
     * Applique cette contrainte à la masse fournie
    */
    virtual void apply(Mass& mass, double time) const = 0;

    /**
     * Dessine cette contrainte dans le `Renderer` fourni
    */
    virtual void draw(Renderer& dest) override;

    /**
     * Affiche cette contrainte dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const;
};

/**
 * Surcharge de l'opérateur << afin d'afficher une contrainte dans un flot
*/
std::ostream& operator<<(std::ostream& out, const Constraint& constraint);
