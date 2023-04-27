#pragma once
#include "include/drawable.h"
#include "include/constants.h"
#include "include/integrator.h"

#include <iostream>
#include <vector>
#include <memory>

class Cloth;

struct Constraint {
    Masse& masse;
    bool attached;
};

class System: public Drawable {
private:
    Integrator& integrator;
    std::vector<std::unique_ptr<Cloth>> cloths;
    std::vector<Constraint> manyConstraints;

public:
    System(Integrator& integrator): integrator(integrator), cloths() {}

    void addCloth(std::unique_ptr<Cloth>&);

    void update(double dt = CONSTANTS::PHYSICS_DT);

    void addConstraint (Masse& mass, bool attached = true);

    virtual void draw(Renderer& dest) override;

    void display(std::ostream& out, size_t level = 0) const;
};

std::ostream& operator<<(std::ostream&, const System&);
