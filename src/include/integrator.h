#pragma once
#include "include/constants.h"

// #include <iostream>


class Masse;

class Integrator {
public:
    virtual ~Integrator() = default;
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) const = 0;
    // TODO: besoin d'affichage?
    // virtual void display(std::ostream&) const = 0;
};

class EulerCromerIntegrator: public Integrator {
public:
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) const override;
};
