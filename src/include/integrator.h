#pragma once
#include "include/constants.h"
#include "include/constraint.h"

#include <vector>

class Masse;
class Cloth;
typedef std::vector<std::unique_ptr<Constraint>> ManyConstraints;   // TODO



class Integrator {
public:
    
    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Integrator() = default;
    /**
     * Fonctions pour intégrer pas définies dans la super classe
    */
   virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const = 0;
   virtual void integrate(Cloth&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const = 0;
};


class EulerCromerIntegrator: public Integrator {
public:
    /**
     * Intègre les masses individuelles avec les formules pour l'intégrateur d'Euleur Cromer
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const override;
    /**
     * Intègre le tissu en intégrant les masses une par une 
    */
    virtual void integrate(Cloth&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const override;
};


class RK4Integrator: public Integrator {
private:
    typedef std::vector<Vector3D> IntermediateVectors;
    //void changeMass(Masse& mass, Vector3D const& posOrigin, Vector3D const& velOrigin, Vector3D const& k, Vector3D const& p, double dt, double time);
public:
    /**
     * Intègre avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4
    */
   virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const override {}
   virtual void integrate(Cloth&, double dt = CONSTANTS::PHYSICS_DT, ManyConstraints const& constraints = {}, double time = 0) const override;
};



/*class NewmarkIntegrator: public Integrator {
    public: 
    */
    /**
     * Intègre avec les formules pour l'intégrateur de Newmark
    */
/*   virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT) override;
};
*/

