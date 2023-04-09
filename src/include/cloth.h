#pragma once
#include "include/constants.h"
#include "include/drawable.h"

#include <iostream>
#include <vector>

class Masse;
class Spring;
class Integrator;

typedef std::vector<Masse*> ManyMass;
typedef std::vector<Spring*> ManySpring;

class Cloth: public Drawable {
private:
    ManyMass massList;
    ManySpring springList;

public:
    /* constructeur prenant la liste des masses */
    Cloth(const ManyMass& init_mass);

    Cloth(const ManyMass& init_mass, const std::vector<std::pair<size_t, size_t>>& connections);

    /* le destructeur libère tous les espaces mémoires alloués pour les ressorts et masses */
    virtual ~Cloth();

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

    /* Alloue dynamiquement une copie du tissu contenant *que* les masses non connectées*/
    Cloth* copy() const;

    virtual void draw(Renderer& dest) override;

    void display(std::ostream&, size_t level = 0) const;
};

std::ostream& operator<<(std::ostream&, const Cloth&);
