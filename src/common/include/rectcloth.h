#pragma once
#include "include/vector3d.h"
#include "include/cloth.h"

#include <vector>

class RectCloth: public Cloth {
public:
    RectCloth(double mass, Vector3D width, Vector3D height, const Vector3D& origin, double lambda, double step, double k, double l0);

    RectCloth(const RectCloth&) = delete;
    RectCloth& operator=(const RectCloth&) = delete;
    
    RectCloth(RectCloth&&) = default;
    RectCloth& operator=(RectCloth&&) = default;

    virtual ~RectCloth() = default;
};
