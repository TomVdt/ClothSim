#pragma once
#include "include/cloth.h"
#include "include/mass.h"
#include "include/spring.h"
#include "include/vector3d.h"

#include <vector>
#include <memory>

class CompositeCloth: public Cloth {
private:
    /**
     * Constante de raideur des ressorts qui relieront les tissus entre eux
    */
    double k;

    /**
     * Distance maximale entre deux masses pour qu'elles soient connectées lors du lien enter deux tissus
    */
    double delta;

    static constexpr double DELTA = 0.5;

protected:
    /**
     * Récupère les masses et ressorts passés en argument et relie les masses situées à la bonne distance
     * afin de coudre les tissus entre eux
    */
    virtual void lootCorpse(std::vector<std::unique_ptr<Mass>>&& manyMass, std::vector<std::unique_ptr<Spring>>&& manySpring) override;

public:
    /**
     * Constructeur d'un tissu composé vide prenant la constante de raideur des ressorts utilisés pour connecter les tissus
     * et la distance maximale entre deux masses pour les connecter lors du lien entre deux tissus
    */
    CompositeCloth(double k, double delta = DELTA): k(k), delta(delta) {}

    /**
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire
    */
    CompositeCloth(const CompositeCloth&) = delete;

    /**
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire
    */
    CompositeCloth& operator=(const CompositeCloth&) = delete;

    /**
     * On peut (et doit!) déplacer les tissus
    */
    CompositeCloth(CompositeCloth&&) = default;

    /**
     * On peut (et doit!) déplacer les tissus
    */
    CompositeCloth& operator=(CompositeCloth&&) = default;

    /**
     * Destructeur par défaut suffisant car nous utilisons des `unique_ptr`
    */
    virtual ~CompositeCloth() = default;

    /**
     * Récupère un tissu et le place dans le tissu composé en faisant les liens nécessaires
    */
    void linkCloth(std::unique_ptr<Cloth>&& cloth);
};
