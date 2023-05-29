#pragma once
#include "include/vector3d.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/drawable.h"
#include "include/renderer.h"

#include <vector>
#include <iostream>

class Constraint: public Drawable {
private:
    /**
     * Position où la contrainte doit s'appliquer
    */
    Vector3D pos;

    /**
     * Rayon d'action de la contrainte
    */
    double radius;

public:
    /**
     * Constructeur prenant la position d'application de la contrainte et son rayon d'action
    */
    Constraint(const Vector3D& pos, double radius);

    /**
     * Destructeur par défaut, virtuel pour l'héritage
    */
    virtual ~Constraint() = default;

    /**
     * Getter sur la position d'application de la contrainte
    */
    const Vector3D& getPos() const { return pos; }

    /**
     * Getter sur le rayon d'action de la contrainte
    */
    double getRadius() const { return radius; }

    /**
     * Retourne un booléen indiquant si la masse fournie est concernée par la contrainte ou non
    */
    virtual bool isApplicable(const Masse& mass, double time) const;

    /**
     * Applique sur toutes les masses d'un tissu cette contrainte
    */
    void apply(Cloth& cloth, double time) const;

    /**
     * Applique cette contrainte à la masse fournie
    */
    virtual void apply(Masse& mass, double time) const = 0;

    /**
     * Dessine cette contrainte dans le `Renderer` fourni
    */
    virtual void draw(Renderer& dest) override;

    /**
     * Affiche cette contrainte dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const;
};

/**
 * Surcharge de l'opérateur << afin d'afficher une contrainte dans un flot
*/
std::ostream& operator<<(std::ostream& out, const Constraint& constraint);


class HookConstraint: public Constraint {
public:
    /**
     * Constructeur d'une contrainte "crochet" prenant sa position et son rayon d'action
    */
    HookConstraint(const Vector3D& pos, double radius): Constraint(pos, radius) {}
    
    /**
     * Destructeur par défaut suffisant pour une contrainte "crochet"
    */
    virtual ~HookConstraint() = default;

    /**
     * Arrête la masse et mets sa force à 0
    */
    virtual void apply(Masse& mass, double time) const override;

    /**
     * Affichage spécifique à une `HookConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};


class ImpulsionConstraint: public Constraint {
private:
    /**
     * Liste de tous les identificateurs uniques des masses concernées par cette contrainte
    */
    std::vector<int> massIds;

    /**
     * Détermine si une masse est dans la liste des masses concernées par cette contrainte
    */
    bool isInList(const Masse& mass) const;

    /**
     * Détermine si le temps fourni est inclu dans l'intervalle de temps où cette contrainte doit s'appliquer
    */
    bool isInTime(double time) const;

protected:
    /**
     * Temps de début d'application de la contrainte
    */
    double startTime;

    /**
     * Temps de fin d'application de la contrainte
    */
    double endTime;

    /**
     * Force appliquée par la contrainte
    */
    Vector3D force;

public:
    /**
     * Constructeur prenant la position et le rayon d'action de la contrainte, ses temps de début et de fin,
     * sa force caractéristique et tous les tissus concernés afin de trouver dans ces tissus toutes les masse concernées
    */
    ImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, std::vector<Cloth*> targetCloths);

    /**
     * Détermine si la contrainte est applicable à la masse fournie à l'instant indiqué
    */
    virtual bool isApplicable(const Masse& mass, double time) const override;

    /**
     * Annule le poids de la masse fournie et lui applique la force caractéristique de la contrainte
    */
    virtual void apply(Masse& mass, double time) const override;

    /**
     * Affichage spécifique à une `ImpulsionConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};


class SineImpulsionConstraint : public ImpulsionConstraint {
private:
    /**
     * Fréquence de l'impulsion sinusoïdale
    */
    double frequency;

public:
    /**
     * Constructeur prenant la position et le rayon d'action de la contrainte, ses temps de début et de fin, sa force caractéristique,
     * sa fréquence et tous les tissus concernés afin de trouver dans ces tissus toutes les masse concernées
    */
    SineImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, double frequency, std::vector<Cloth*> targetCloths);

    /**
     * Applique l'impulsion en annulant le poids de la masse et en appliquant une force
     * de norme dépendante du temps selon une fonction sinusoïdale
    */
    virtual void apply(Masse& mass, double time) const override;

    /**
     * Affichage spécifique à une `SineImpulsionConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};


class AttractionConstraint: public Constraint {
private:
    /**
     * Intensité de l'attraction de cette contrainte
    */
    double intensity;

    /**
     * Rayon intérieur où la contrainte a toujours la même intensité
    */
    double innerRadius;

public:
    /**
     * Constructeur qui prend la position du centre d'attraction, le rayon de la sphère où la contrainte s'applique,
     * l'intensité de l'attraction et le rayon intérieur où l'attraction est uniforme
    */
    AttractionConstraint(const Vector3D& pos, double spherOfInfluence, double intensity, double innerRadius);

    /**
     * Applique à la masse l'attraction correspondante à sa position
    */
    virtual void apply(Masse& mass, double time) const override;

    /**
     * Affichage spécifique à une `AttractionConstraint` dans un flot
    */
    virtual void display(std::ostream& out, size_t level = 0) const override;
};
