#pragma once
#include "include/constants.h"

// #include <iostream>


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
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) const = 0;
};

class EulerCromerIntegrator: public Integrator {
public:
    /**
     * Intègre avec les formules pour l'intégrateur d'Euleur Cromer 
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) const override;
};



/*class RK4Integrator: public Integrator {
public: */
    /**
     * Intègre avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4
    */
/*   virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) const override;
};
*/


/*class NewmarkIntegrator: public Integrator {
    public: 
    */
    /**
     * Intègre avec les formules pour l'intégrateur de Newmark
    */
/*   virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) const override;
};
*/

