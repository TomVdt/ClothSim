#pragma once
#include "include/vector3d.h"
#include "include/cloth.h"

#include <vector>
#include <cmath>

class DiskCloth: public Cloth {
public:
    DiskCloth(double mass, const Vector3D& center, const Vector3D& radius, double radialStep, double lambda, double k, double angularStep = M_PI / 9.0);

    DiskCloth(const DiskCloth&) = delete;
    DiskCloth& operator=(const DiskCloth&) = delete;
    
    DiskCloth(DiskCloth&&) = default;
    DiskCloth& operator=(DiskCloth&&) = default;

    virtual ~DiskCloth() = default;

    // TODO: draw, display
};
