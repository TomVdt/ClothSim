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
protected:
    // Pour nos soldats ManySpring et ManyMass parti trop tot :F:
    std::vector<std::unique_ptr<Masse>> massList;
    std::vector<std::unique_ptr<Spring>> springList;

public:
    /** 
     * Constructeur par défaut
    */
    Cloth();

    /** 
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire 
    */
    Cloth(const Cloth&) = delete;

    /** 
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire 
    */
    Cloth& operator=(const Cloth&) = delete;

    /**
     *  On peut (et doit!) déplacer les tissus 
    */
    Cloth(Cloth&&) = default;

    /**
     *  On peut (et doit!) déplacer les tissus 
    */
    Cloth& operator=(Cloth&&) = default;

    /**
     *  Destructeur par defaut suffisant car nous utilisons des `unique_ptr` 
    */
    virtual ~Cloth() = default;

    /**
     *  Nombre de masses dans le tissu 
    */
    unsigned int getMassCount() const;

    /**
     *  Nombre de ressorts dans le tissu 
    */
    unsigned int getSpringCount() const;
    
    // TODO: why tho
    /**
     * WARNING WARNING WARNING
     * WARNING WARNING WARNING
     * WARNING WARNING WARNING
     * WARNING WARNING WARNING
     * WARNING WARNING WARNING
    */
    const std::vector<std::unique_ptr<Masse>>& getMasses() const;

    std::vector<Masse*> getMassesInRange(const Vector3D& pos, double radius) const;

    /**
     * Rajoute une masse dans le tissu
    */
    void addMass(std::unique_ptr<Masse>&&);

    /**
     *  Crée un ressort entre deux masses d'indices m1 et m2, de raideur k et longueur au repos l0 
    */
    void connect(size_t m1, size_t m2, double k = 0.1, double l0 = 1);

    /**
     *  Vérifie pour tous les ressorts et toutes les masses que les connections sont valides 
    */
    virtual bool check() const;

    /**
     *  Met à jour les forces sur les masses 
    */
    virtual void updateForce();

    virtual void applyConstraint(Constraint const& constraint, double time);

    /**
     *  Utilise l'intégrateur pour mettre à jour les masses du tissu 
    */
    virtual void step(Integrator& integratator, double dt = CONSTANTS::PHYSICS_DT);

    /**
     * Dessine le tissu
    */
    virtual void draw(Renderer& dest) override;

    /**
     * Dessine les masses du tissu
    */
    virtual void drawParticles(Renderer& dest) const;

    /**
     * Affichage dans un flot
    */
    virtual void display(std::ostream&, size_t level = 0) const;
};

/**
 * Surcharge de << pour afficher des Cloth dans un flot
*/
std::ostream& operator<<(std::ostream&, const Cloth&);
