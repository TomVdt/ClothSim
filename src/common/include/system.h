#pragma once
#include "include/drawable.h"
#include "include/constants.h"
#include "include/integrator.h"
#include "include/cloth.h"
#include "include/constraint.h"

#include <iostream>
#include <vector>
#include <memory>

class System: public Drawable {
private:
    /**
     * Liste de pointeurs uniques vers des tissus: le système possède les tissus
    */
    std::vector<std::unique_ptr<Cloth>> cloths;

    /**
     * Liste de pointeurs uniques vers des contraintes: le système possède les contraintes
    */
    std::vector<std::unique_ptr<Constraint>> constraints;

    /**
     * Temps actuel du système
    */
    double time;

public:
    /**
     * Constructeur par défaut initialise le système vide avec un temps de 0
    */
    System(): cloths(), constraints(), time(0.0) {}

    /**
     * Pas de copie de systèmes, trop coûteux en mémoire et 
     * ses composants lui appartiennent uniquement
    */
    System(const System&) = delete;
    
    /**
     * Pas de copie de systèmes, trop coûteux en mémoire et 
     * ses composants lui appartiennent uniquement
    */
    System& operator=(const System&) = delete;

    /**
     * On peut déplacer des systèmes
    */
    System(System&&) = default;
    
    /**
     * On peut déplacer des systèmes
    */
    System& operator=(System&&) = default;

    /**
     * Destructeur par défaut suffisant car nous utilisons des `unique_ptr`
    */
    virtual ~System() = default;

    /**
     * Le temps actuel du système
    */
    double getTime() const { return time; };

    /**
     * L'énergie mécanique totale du système
    */
    double energy() const;

    /**
     * Rajoute un tissu au système
    */
    void addCloth(std::unique_ptr<Cloth>&&);

    /**
     * Rajoute une contrainte au système
    */
    void addConstraint(std::unique_ptr<Constraint>&& constraint);

    /**
     * Vide le système et réinitialise son temps
    */
    void clear();

    /**
     * Fait avancer le système d'un pas de temps donné avec l'intégrateur fourni
    */
    void step(Integrator const& integrator, double dt = CONSTANTS::PHYSICS_DT);

    /**
     * Dessine le système, surcharge de draw pour la classe Drawable
    */
    virtual void draw(Renderer& dest) override;
    
    /**
     * Dessine tous les éléments du système
    */
    void drawContents(Renderer& dest) const;

    /**
     * Affichage du système dans un flot
    */
    void display(std::ostream& out, size_t level = 0) const;
};

/**
 * Surcharge de l'opérateur << pour afficher des systèmes dans des flots
*/
std::ostream& operator<<(std::ostream&, const System&);
