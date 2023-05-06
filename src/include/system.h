#pragma once
#include "include/drawable.h"
#include "include/constants.h"
#include "include/integrator.h"
#include "include/cloth.h"
#include "include/constraint.h"

#include <iostream>
#include <vector>
#include <memory>

class System: public Drawable {
private:
    std::vector<std::unique_ptr<Cloth>> cloths;
    std::vector<std::unique_ptr<Constraint>> constraints;
    double time;

public:
    System(): cloths(), constraints(), time(0.0) {}

    double getTime() const;

    void addCloth(std::unique_ptr<Cloth>&&);

    void step(Integrator& integrator, double dt = CONSTANTS::PHYSICS_DT);

    void addConstraint(std::unique_ptr<Constraint>&& constraint);

    virtual void draw(Renderer& dest) override;
    
    void drawContents(Renderer& dest) const;

    void display(std::ostream& out, size_t level = 0) const;
};

std::ostream& operator<<(std::ostream&, const System&);
