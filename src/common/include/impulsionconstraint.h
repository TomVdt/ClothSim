#pragma once
#include "include/constraint.h"

#include <vector>
#include <iostream>

class Cloth;
class Mass;
class Vector3D;

class ImpulsionConstraint: public Constraint {
private:
    /**
     * Liste de tous les identificateurs uniques des masses concernées par cette contrainte
    */
    std::vector<int> massIds;

protected:
    /**
     * Détermine si une masse est dans la liste des masses concernées par cette contrainte
    */
    bool isInList(const Mass& mass) const;

    /**
     * Détermine si le temps fourni est inclu dans l'intervalle de temps où cette contrainte doit s'appliquer
    */
    bool isInTime(double time) const;

    /**
     * Temps de début d'application de la contrainte
    */
    double startTime;

    /**
     * Temps de fin d'application de la contrainte
    */
    double endTime;

    /**
     * Force appliquée par la contrainte
    */
    Vector3D force;

public:
    /**
     * Constructeur prenant la position et le rayon d'action de la contrainte, ses temps de début et de fin,
     * sa force caractéristique et tous les tissus concernés afin de trouver dans ces tissus toutes les masse concernées
    */
    ImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, std::vector<Cloth*> targetCloths);

    /**
     * Annule le poids de la masse fournie et lui applique la force caractéristique de la contrainte
    */
    virtual void apply(Mass& mass, double time) const override;

    /**
     * Affichage spécifique à une `ImpulsionConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};
