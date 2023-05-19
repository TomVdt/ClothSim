#pragma once
#include "include/constants.h"
#include "include/constraint.h"

class Masse;
class Cloth;
typedef std::vector<std::unique_ptr<Constraint>> ManyConstraints;   // TODO



class Integrator {
public:
    
    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Integrator() = default;
    // TODO: integrer sur les masses ET les tissus: 2 méthodes abstraites
    /**
     * Fonction pour intégrer pas définie dans la super classe
    */
    virtual void integrate(Cloth&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const = 0;
};


class EulerCromerIntegrator: public Integrator {
public:
    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur d'Euleur Cromer
    */
    void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) const;
    /**
     * Intègre le tissu en intégrant les masses une par une 
    */
    virtual void integrate(Cloth&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const override;
};

/*
class RK4Integrator: public Integrator {
private:
    void changeMass(Masse& mass, Vector3D const& posOrigin, Vector3D const& velOrigin, Vector3D const& k, Vector3D const& p, double dt, double time);
public: */
    /**
     * Intègre avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4
    */
  /*virtual void integrate(Cloth&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const override;
};

*/


/*class NewmarkIntegrator: public Integrator {
    public: 
    */
    /**
     * Intègre avec les formules pour l'intégrateur de Newmark
    */
/*   virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) override;
};
*/

