#pragma once
#include "include/vector3d.h"

#include <vector>
#include <iostream>

class Mass;

class Spring {
private:
    double k;
    double l0;
    Masse* mass1;
    Masse* mass2;

public:
    Spring(double k, double l0, Masse* mass1 = nullptr, Masse* mass2 = nullptr);
    virtual ~Spring() = default;

    // No copying of springs
    // Does it make sense to copy the wights?
    // Should it keep the same weights?
    Spring(const Spring&) = delete;

    // Getters
    double getK() const { return k; }
    double getL0() const { return l0; }

    // Get force applying to given mass
    Vector3D springForce(Masse*) const;

    // Add masses to spring extremities
    // Side-effect: spring auto-added to masses
    void connect(Masse* mass1, Masse* mass2);

    // Disconnect spring from masses
    // Removes pointers to those masses
    void disconnect();

    // Does spring have valid data?
    bool valid() const;

    // "String" representation
    void display(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const Spring&);
