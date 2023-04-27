#pragma once
#include "include/masse.h"
#include "include/spring.h"
#include "include/constants.h"
#include "include/drawable.h"

#include <iostream>
#include <vector>
#include <memory>

class Integrator;

class Cloth: public Drawable {
private:
    // Pour nos soldats ManySpring et ManyMass parti trop tot :F:
    std::vector<std::unique_ptr<Masse>> massList;
    std::vector<std::unique_ptr<Spring>> springList;

public:
    /* constructeur prenant la liste des masses */
    Cloth();

    /* Pas de copie de tissu: complexe de refaire toutes les connections et necessite beaucoup de mémoire */
    Cloth(const Cloth&) = delete;
    Cloth& operator=(const Cloth&) = delete;

    /* On peut (et doit!) déplacer les tissus */
    Cloth(Cloth&&) = default;
    Cloth& operator=(Cloth&&) = default;

    /* Destructeur par defaut suffisant car nous utilisons des `unique_ptr` */
    virtual ~Cloth() = default;

    /* Nombre de masses dans le tissu */
    unsigned int getMassCount() const;

    /* Nombre de ressorts dans le tissu */
    unsigned int getSpringCount() const;
    
    void addMass(std::unique_ptr<Masse>&&);

    /* crée un ressort entre deux masses d'indices m1 et m2, de raideur k et longueur au repos l0 */
    void connect(size_t m1, size_t m2, double k = 0.1, double l0 = 1);

    /* vérifie pour tous les ressorts et toutes les masses que les connections sont valides */
    bool check() const;

    /* met à jour les forces sur les masses */
    void updateForce();

    /* utilise l'intégrateur pour mettre à jour les masses du tissu */
    void step(const Integrator& integratator, double dt = CONSTANTS::PHYSICS_DT);

    /**
     * Dessine le tissu
    */

    virtual void draw(Renderer& dest) override;

    /**
     * Dessine les masses du tissu
    */

    void drawParticles(Renderer& dest) const;

    /**
     * Affichage dans un flot
    */

    void display(std::ostream&, size_t level = 0) const;
};

std::ostream& operator<<(std::ostream&, const Cloth&);
