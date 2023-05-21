#pragma once
#include "include/constants.h"
#include "include/constraint.h"

#include <vector>

class Masse;
class Cloth;


class Integrator {
public:
    
    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Integrator() = default;
    /**
     * Fonctions pour intégrer pas définies dans la super classe
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
     * Intègre avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};



class NewmarkIntegrator: public Integrator {
private:
    double epsilon = 0.05;
public:
    NewmarkIntegrator(double epsilon): epsilon(epsilon) {}
    /**
     * Intègre avec les formules pour l'intégrateur de Newmark
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const override;
};
