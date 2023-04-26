#pragma once
#include "include/vector3d.h"

namespace CONSTANTS {
    // Comparaison double
    inline constexpr double EPSILON(1e-10);
    
    // Physique
    inline constexpr Vector3D g(0.0, -9.81, 0.0);
    inline constexpr double PHYSICS_DT(0.1);

    // Camera
    // 60deg
    inline constexpr double CAMERA_FOV(1.047197551);
    inline constexpr double CAMERA_RATIO(1.0);
    inline constexpr double CAMERA_NEAR(0.1);
    inline constexpr double CAMERA_FAR(1000.0);
};
