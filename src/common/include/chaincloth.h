#pragma once
#include "include/cloth.h"
#include "include/vector3d.h"

#include <vector>

class ChainCloth: public Cloth {
public:
    /**
     * Nouveau constructeur pour les tissus chaînes prenant les caractéristiques des masses
     * et leurs positions dans l'ordre afin de les relier une par une
    */
    ChainCloth(double mass, double lambda, double k, double l0, std::vector<Vector3D> pos);

    /**
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire
    */
    ChainCloth(const ChainCloth&) = delete;

    /**
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire
    */
    ChainCloth& operator=(const ChainCloth&) = delete;

    /**
     * On peut (et doit!) déplacer les tissus
    */
    ChainCloth(ChainCloth&&) = default;

    /**
     * On peut (et doit!) déplacer les tissus
    */
    ChainCloth& operator=(ChainCloth&&) = default;

    /**
     * Destructeur par défaut suffisant car nous utilisons des `unique_ptr`
    */
    virtual ~ChainCloth() = default;
};
