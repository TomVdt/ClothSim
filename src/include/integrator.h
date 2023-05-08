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
     * Fonction pour intégrer pas définie dans la super classe, toujours faire un appel a move()
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) = 0;
    /**
     * Déplace les masses et leur affecte la bonne vitesse
    */
    void move();
};


class EulerCromerIntegrator: public Integrator {
public:
    /**
     * Intègre avec les formules pour l'intégrateur d'Euleur Cromer, toujours faire un appel a move()
    */
    virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) override;
};


class RK4Integrator: public Integrator {
private:
    void changeMass(Masse& mass, Vector3D const& posOrigin, Vector3D const& velOrigin, Vector3D const& k, Vector3D const& p, double dt, double time);
public:
    /**
     * Intègre avec les formules pour l'intégrateur de Runge-Kutta d'ordre 4, toujours faire un appel a move()
    */
  virtual void integrate(Masse&, double dt = CONSTANTS::PHYSICS_DT, double time = 0) override;
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

