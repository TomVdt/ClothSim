#pragma once
#include "include/constants.h"

#include <vector>


class Masse;
typedef std::vector<std::pair<Masse*, Vector3D>> pairMassVector;

class Integrator {
protected:
    pairMassVector newPos;
    pairMassVector newVel;

public:
    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Integrator() = default;
    /**
     * Fonction pour intégrer pas définie dans la super classe
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) = 0;
    /**
     * Déplace les masses et leur affecte la bonne vitesse
    */
    void move();
};


class EulerCromerIntegrator: public Integrator {
public:
    /**
     * Intègre avec les formules pour l'intégrateur d'Euleur Cromer 
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) override;
};


/*class RK4Integrator: public Integrator {
public:*/
    /**
     * Intègre avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4
    */
  /*virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) override;
};*/




/*class NewmarkIntegrator: public Integrator {
    public: 
    */
    /**
     * Intègre avec les formules pour l'intégrateur de Newmark
    */
/*   virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) override;
};
*/

