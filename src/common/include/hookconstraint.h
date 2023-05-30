#pragma once
#include "include/constraint.h"

#include <iostream>

class Mass;
class Vector3D;

class HookConstraint: public Constraint {
public:
    /**
     * Constructeur d'une contrainte "crochet" prenant sa position et son rayon d'action
    */
    HookConstraint(const Vector3D& pos, double radius): Constraint(pos, radius) {}

    /**
     * Destructeur par défaut suffisant pour une contrainte "crochet"
    */
    virtual ~HookConstraint() = default;

    /**
     * Arrête la masse et mets sa force à 0
    */
    virtual void apply(Mass& mass, double time) const override;

    /**
     * Affichage spécifique à une `HookConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};
