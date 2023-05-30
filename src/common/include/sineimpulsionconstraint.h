#pragma once
#include "include/impulsionconstraint.h"

#include <iostream>
#include <vector>

class Cloth;
class Mass;
class Vector3D;

class SineImpulsionConstraint : public ImpulsionConstraint {
private:
    /**
     * Fréquence de l'impulsion sinusoïdale
    */
    double frequency;

public:
    /**
     * Constructeur prenant la position et le rayon d'action de la contrainte, ses temps de début et de fin, sa force caractéristique,
     * sa fréquence et tous les tissus concernés afin de trouver dans ces tissus toutes les masse concernées
    */
    SineImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, double frequency, std::vector<Cloth*> targetCloths);

    /**
     * Applique l'impulsion en annulant le poids de la masse et en appliquant une force
     * de norme dépendante du temps selon une fonction sinusoïdale
    */
    virtual void apply(Mass& mass, double time) const override;

    /**
     * Affichage spécifique à une `SineImpulsionConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};
