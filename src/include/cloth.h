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

class Cloth: public Drawable {
protected:
    /**
     * Liste de unique_ptr sur les masses, le tissu stocke les masses
    */
    std::vector<std::unique_ptr<Masse>> masses;
    
    /**
     * Liste de unique_ptr sur les ressorts, le tissu stocke les ressorts
    */
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
    //  - Le suicide, c'est mal
    // friend CompositeCloth;

public:
    /** 
     * Constructeur par défaut, initialise les listes des composants du tissu à des listes vides
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
    ~Cloth() = default;

    /**
     *  Nombre de masses dans le tissu 
    */
    unsigned int getMassCount() const;

    /**
     *  Nombre de ressorts dans le tissu 
    */
    unsigned int getSpringCount() const;
    
    /**
     * Retourne la position de la masse d'indice fourni dans la liste de masses
    */
    const Vector3D& getMassPos(size_t index) const;

    /**
     * Retourne une liste de toutes les ID des masses de ce tissu dans un rayon autour du vecteur fourni
    */
    std::vector<int> getMassIdsInRange(const Vector3D& pos, double radius) const;

    /**
     * Retourne l'énergie du tissu en additionant les énergies de toutes les masses et tous les ressorts
    */
    double energy() const;

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
    bool check() const;

    /**
     * Prend possession des masses et ressorts du tissu
     * @warning Rend le tissu invalide, ne devrait pas être réutilisé
    */
    std::pair<std::vector<std::unique_ptr<Masse>>, std::vector<std::unique_ptr<Spring>>> lootCorpse();

    /**
     *  Met à jour les forces sur les masses 
    */
    void updateForce();

    /**
     * Rajoute une contrainte au tissu en donnant à toutes les masses une références à cette contrainte
    */
    void addConstraint(const Constraint& constraint);

    /**
     * Applique une contrainte au tissu
    */
    void applyConstraint(const Constraint& constraint, double time);

    /**
     * Applique toutes les contraintes des masses du tissu
    */
    void applyConstraints(double time);

    /**
     *  Utilise l'intégrateur pour mettre à jour les masses du tissu 
    */
    void step(Integrator const& integratator, double dt = CONSTANTS::PHYSICS_DT, double time = 0);

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

/**
 * Surcharge de << pour afficher des Cloth dans un flot
*/
std::ostream& operator<<(std::ostream&, const Cloth&);
