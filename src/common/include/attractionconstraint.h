#pragma once
#include "include/constraint.h"

#include <iostream>

class Mass;
class Vector3D;

class AttractionConstraint: public Constraint {
private:
    /**
     * Intensité de l'attraction de cette contrainte
    */
    double intensity;

    /**
     * Rayon intérieur où la contrainte a toujours la même intensité
    */
    double innerRadius;

public:
    /**
     * Constructeur qui prend la position du centre d'attraction, le rayon de la sphère où la contrainte s'applique,
     * l'intensité de l'attraction et le rayon intérieur où l'attraction est uniforme
    */
    AttractionConstraint(const Vector3D& pos, double spherOfInfluence, double intensity, double innerRadius);

    /**
     * Applique à la masse l'attraction correspondante à sa position
    */
    virtual void apply(Mass& mass, double time) const override;

    /**
     * Affichage spécifique à une `AttractionConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};
