#pragma once
#include "include/vector3d.h"
#include "include/cloth.h"

#include <vector>
#include <memory>

class CompositeCloth: public Cloth {
private:
    static constexpr double epsilon = 0.5;

public:
    CompositeCloth();

    CompositeCloth(const CompositeCloth&) = delete;
    CompositeCloth& operator=(const CompositeCloth&) = delete;
    
    CompositeCloth(CompositeCloth&&) = default;
    CompositeCloth& operator=(CompositeCloth&&) = default;

    virtual ~CompositeCloth() = default;

    void linkCloth(std::unique_ptr<Cloth>&& cloth, double k);
};
