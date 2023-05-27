#pragma once
#include "include/cloth.h"
#include "include/vector3d.h"

#include <cmath>

class DiskCloth: public Cloth {
public:
    /**
     * Constructeur de tissus circulaires qui prend la masse des éléments du tissu, la position du centre, le vecteur normal,
     * l'écart entre deux cercles concentriques, le coefficient de frottement des masses, la constante de raideur des ressorts
     * et l'écart angulaire entre les masses sur un même cercle
    */
    DiskCloth(double mass, const Vector3D& center, const Vector3D& radius, double radialStep, double lambda, double k, double angularStep = M_PI / 9.0);

    /** 
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire 
    */
    DiskCloth(const DiskCloth&) = delete;
    
    /** 
     * Pas de copie de tissu: complexe de refaire toutes les connections et nécessite beaucoup de mémoire 
    */
    DiskCloth& operator=(const DiskCloth&) = delete;
    
    /**
     * On peut (et doit!) déplacer les tissus 
    */
    DiskCloth(DiskCloth&&) = default;
    
    /**
     * On peut (et doit!) déplacer les tissus 
    */
    DiskCloth& operator=(DiskCloth&&) = default;

    /**
     * Destructeur par défaut suffisant car nous utilisons des `unique_ptr` 
    */
    virtual ~DiskCloth() = default;
};
