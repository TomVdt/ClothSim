#pragma once
#include "include/constants.h"
#include "include/integrator.h"

class Mass;

class RK4Integrator: public Integrator {
public:
    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4
    */
    virtual void integrate(Mass&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};
