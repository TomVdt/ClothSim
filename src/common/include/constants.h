#pragma once
#include "include/vector3d.h"

namespace CONSTANTS {
    /**
     * Comparaison entre double
    */
    inline constexpr double EPSILON(1e-10);

    // Physique
    /**
     * Vecteur du champ de pesanteur terrestre
    */
    inline constexpr Vector3D g(0.0, -9.81, 0.0);

    /**
     * Pas de temps par défaut
    */
    inline constexpr double PHYSICS_DT(0.01);
}
