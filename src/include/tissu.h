#pragma once
#include "include/constants.h"
#include "include/drawable.h"

#include <iostream>
#include <vector>

class Masse;
class Spring;
class Integrator;

class Tissu : public Drawable {
private:
    typedef std::vector<Masse*> ManyMass;
    typedef std::vector<Spring*> ManySpring;
    ManyMass massList;
    ManySpring springList;

public:
    /* constructeur prenant la liste des masses */
    Tissu(const ManyMass& init_mass);
    
    /* le destructeur libère tous les espaces mémoires alloués pour les ressorts */
    virtual ~Tissu();

    /* Nombre de masses dans le tissu */
    unsigned int getMassCount() const;

    /* Nombre de ressorts dans le tissu */
    unsigned int getSpringCount() const;

    /* crée un ressort entre deux masses d'indices m1 et m2, de raideur k et longueur au repos l0 */
    void connect(size_t m1, size_t m2, double k = 0.1, double l0 = 1);

    /* vérifie pour tous les ressorts et toutes les masses que les connections sont valides */
    bool check() const;

    /* met à jour les forces sur les masses */
    void updateForce();

    /* utilise l'intégrateur pour mettre à jour les masses du tissu */
    void evolve(const Integrator& integratator, double dt = CONSTANTS::PHYSICS_DT);

    void display(std::ostream&) const;
};

std::ostream& operator<<(std::ostream, const Tissu&);
