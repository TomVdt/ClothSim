#pragma once
#include "include/vector3d.h"
#include "include/cloth.h"

#include <vector>
#include <memory>

class CompositeCloth: public Cloth {
private:
    std::vector<std::unique_ptr<Cloth>> cloths;

    bool connectClothsConditional(Cloth& cloth1, Cloth& cloth2);

    static constexpr double epsilon = 0.5;

public:
    CompositeCloth();

    CompositeCloth(const CompositeCloth&) = delete;
    CompositeCloth& operator=(const CompositeCloth&) = delete;
    
    CompositeCloth(CompositeCloth&&) = default;
    CompositeCloth& operator=(CompositeCloth&&) = default;

    virtual ~CompositeCloth() = default;

    void linkCloth(std::unique_ptr<Cloth>&&);

    virtual void updateForce() override;

    virtual void step(Integrator& integrator, double dt) override;

    // virtual void draw(Renderer& dest) override;

    virtual void drawParticles(Renderer& dest) const override;

    // TODO: draw, display, redo cloth-methods (count mostly)
};
