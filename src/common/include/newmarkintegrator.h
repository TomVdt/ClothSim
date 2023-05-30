#pragma once
#include "include/constants.h"
#include "include/integrator.h"

class Mass;

class NewmarkIntegrator: public Integrator {
private:
    /**
     * Attribut définissant le critère de convergence de la boucle dans l'intégrateur de Newmark
    */
    double epsilon;

    /**
     * Distance par défaut
    */
    static constexpr double EPSILON = 0.05;

public:
    /**
     * Constructeur d'un intégrateur de Newmark prenant le critère de convergence utilisé par celui-ci
    */
    NewmarkIntegrator(double epsilon = EPSILON): epsilon(epsilon) {}

    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur de Newmark
    */
    virtual void integrate(Mass&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};
