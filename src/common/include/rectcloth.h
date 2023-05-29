#pragma once
#include "include/vector3d.h"
#include "include/cloth.h"

#include <vector>

class RectCloth: public Cloth {
public:
    /**
     * Constructeur de tissu rectangle prenant la masse des éléments, les largeur et hauteur du tissu et son point de départ,
     * le coefficient de frottement des masses, l'inverse du nombre de masses par bords, la constante de raideur des ressorts et leur longueur à vide
    */
    RectCloth(double mass, Vector3D width, Vector3D height, const Vector3D& origin, double lambda, double step, double k, double l0);

    /** 
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire 
    */
    RectCloth(const RectCloth&) = delete;
    
    /** 
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire 
    */
    RectCloth& operator=(const RectCloth&) = delete;
    
    /**
     * On peut (et doit!) déplacer les tissus 
    */
    RectCloth(RectCloth&&) = default;
    
    /**
     * On peut (et doit!) déplacer les tissus 
    */
    RectCloth& operator=(RectCloth&&) = default;

    /**
     * Destructeur par défaut suffisant car nous utilisons des `unique_ptr` 
    */
    virtual ~RectCloth() = default;
};
