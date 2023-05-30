#pragma once
#include "include/constants.h"
#include "include/integrator.h"

class Mass;

class EulerCromerIntegrator: public Integrator {
public:
    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur d'Euleur Cromer
    */
    virtual void integrate(Mass&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};
