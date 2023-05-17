#pragma once
#include "include/vector3d.h"

namespace CONSTANTS {
    // Comparaison double
    inline constexpr double EPSILON(1e-10);
    
    // Physique
    inline constexpr Vector3D g(0.0, -9.81, 0.0);
    inline constexpr double PHYSICS_DT(0.01);
    inline constexpr double PHYSICS_DPOS(0.1);
}
