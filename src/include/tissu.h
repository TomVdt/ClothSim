#pragma once
#include "include/vector3d.h"
#include "include/spring.h"
#include "include/masse.h"
#include "integrator.h"
#include <vector>



typedef std::vector<Masse*> ManyMass;
typedef std::vector<Spring*> ManySpring;

class Tissu {
private:
    ManyMass massList;
    ManySpring springList;

public:
    /* constructeur prenant la liste des masses */
    Tissu(const ManyMass& init_mass);
    
    /* le destructeur libère tous les espaces mémoires alloués pour les ressorts */
    virtual ~Tissu();

    /* crée un ressort entre deux masses d'indices m1 et m2, de raideur k et longueur au repos l0 */
    void connect(size_t m1, size_t m2, double k = 0.1, double l0 = 1);

    /* vérifie pour tous les ressorts et toutes les masses que les connections sont valides */
    bool check() const;

    /* met à jour les forces sur les masses */
    void updateForce();

    void evolve(Integrator* integratator, double dt);

};