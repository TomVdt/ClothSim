#pragma once
#include "include/drawable.h"
#include "include/constants.h"
#include "include/integrator.h"

#include <iostream>
#include <vector>
#include <memory>

class Tissu;

class System: public Drawable {
private:
    std::unique_ptr<Integrator> integrator;
    std::vector<std::unique_ptr<Tissu>> cloths;

public:
    System(): integrator(std::make_unique<Integrator>(EulerCromerIntegrator())), cloths() {}

    virtual ~System();

    void update(double dt = CONSTANTS::PHYSICS_DT);

    virtual void draw(Renderer& dest) override;

    void display(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const Tissu&);
