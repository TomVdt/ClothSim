#pragma once
#include "include/masse.h"
#include "include/spring.h"
#include "include/constants.h"
#include "include/drawable.h"

#include <iostream>
#include <vector>
#include <memory>

class Integrator;
class Constraint;
class CompositeCloth;

class Cloth: public Drawable {
protected:
    // Pour nos soldats ManySpring et ManyMass parti trop tot :F:
    std::vector<std::unique_ptr<Masse>> masses;
    std::vector<std::unique_ptr<Spring>> springs;

    // Pourquoi un friend ici?
    //  - CompositeCloth à besoin d'acceder au masses du tissu qu'il connecte
    //  - Un getter protected ne fonctionne pas car on n'est pas dans la bonne portée
    //  - Un getter public n'est pas une bonne idée (fuite d'encapsulation)
    //  - Un tissu composé pourrait très bien être un tissu, mais cela ne rendrait plus les tissus "simples"
    //  - Un tissu composé est très proche d'un tissu simple, avec simplement une méthode pour
    //    connecter des tissus entre eux au lieu de masses
    //  - Les tissus complexes en général pourraient très simplement être des constructeurs spécifiques aux
    //    tissus simples, mais cela enlèverait de la "simplicité"
    friend CompositeCloth;

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
    virtual unsigned int getMassCount() const;

    /**
     *  Nombre de ressorts dans le tissu 
    */
    virtual unsigned int getSpringCount() const;
    
    virtual const Vector3D& getMassPos(size_t index) const;

    virtual std::vector<int> getMassIdsInRange(const Vector3D& pos, double radius) const;

    virtual double energy() const;

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

    /**
     * Rajoute une contrainte au tissu. Les masses concernées par les contraintes
     * auront ensuite une reference vers cette contrainte
    */
    virtual void addConstraint(const Constraint& constraint);

    /**
     * Applique une contrainte au tissu
    */
    virtual void applyConstraint(const Constraint& constraint, double time);

    /**
     * Applique les contraintes des masses du tissu
    */
    virtual void applyConstraints(double time);

    /**
     *  Utilise l'intégrateur pour mettre à jour les masses du tissu 
    */
    virtual void step(Integrator const& integratator, double dt = CONSTANTS::PHYSICS_DT, double time = 0);

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
