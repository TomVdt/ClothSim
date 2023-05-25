#pragma once
#include "include/vector3d.h"
#include "include/cloth.h"

#include <vector>

class ChainCloth: public Cloth {
public:
    ChainCloth(double mass, double lambda, double k, double l0, std::vector<Vector3D> pos);

    ChainCloth(const ChainCloth&) = delete;
    ChainCloth& operator=(const ChainCloth&) = delete;
    
    ChainCloth(ChainCloth&&) = default;
    ChainCloth& operator=(ChainCloth&&) = default;

    virtual ~ChainCloth() = default;
};
