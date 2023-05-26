#pragma once
#include "include/vector3d.h"
#include "include/cloth.h"

#include <vector>
#include <memory>

class CompositeCloth: public Cloth {
private:
    double k;
    double delta;

public:
    CompositeCloth(double k, double delta = 0.5): k(k), delta(delta) {}

    CompositeCloth(const CompositeCloth&) = delete;
    CompositeCloth& operator=(const CompositeCloth&) = delete;
    
    CompositeCloth(CompositeCloth&&) = default;
    CompositeCloth& operator=(CompositeCloth&&) = default;

    virtual ~CompositeCloth() = default;

    void linkCloth(std::unique_ptr<Cloth>&& cloth);
};
