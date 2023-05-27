#pragma once
#include "include/constants.h"

class Masse;

class Integrator {
public:
    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Integrator() = default;

    /**
     * Fonction pour intégrer pas définie dans la super classe
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const = 0;
};


class EulerCromerIntegrator: public Integrator {
public:
    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur d'Euleur Cromer
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};


class RK4Integrator: public Integrator {
public:
    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};



class NewmarkIntegrator: public Integrator {
private:
    /**
     * Attribut définissant le critère de convergence de la boucle dans l'intégrateur de Newmark
    */
    double epsilon;

public:
    /**
     * Constructeur d'un intégrateur de Newmark prenant le critère de convergence utilisé par celui-ci
    */
    NewmarkIntegrator(double epsilon = CONSTANTS::PHYSICS_DPOS): epsilon(epsilon) {}

    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur de Newmark
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};
