#pragma once
#include "include/constants.h"

class Mass;

class Integrator {
public:
    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Integrator() = default;

    /**
     * Fonction pour intégrer pas définie dans la super classe
    */
    virtual void integrate(Mass&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const = 0;
};
