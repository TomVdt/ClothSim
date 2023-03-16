#pragma once
#include "include/vector3d.h"
#include "include/masse.h"

#include <vector>
#include <iostream>

class Spring {
private:
    // évite les références circulaires
    Masse* mass1;
    Masse* mass2;
    double k;
    double l0;

public:
    Spring(double k, double l0) : k(k), l0(l0) {}
    virtual ~Spring() = default;
    Spring(const Spring&) = delete;
    // use default move
    // Spring(Spring&&) = default;

    double getK() const { return k; }
    double getL0() const { return l0; }
    const Masse const* getMass1() const { return mass1; }
    const Masse const* getMass2() const { return mass2; }

    Vector3D springForce(Masse*) const;
};

std::ostream& operator<<(std::ostream&, const Spring&);
