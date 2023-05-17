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

    virtual unsigned int getMassCount() const override;

    virtual unsigned int getSpringCount() const override;    

    virtual Masse& getMass(size_t index) const override;

    virtual std::vector<Masse*> getMassesInRange(const Vector3D& pos, double radius) const override;

    virtual bool check() const override;

    virtual void updateForce() override;

    void linkCloth(std::unique_ptr<Cloth>&&);

    virtual void step(const Integrator& integrator, double dt = CONSTANTS::PHYSICS_DT, double time = 0) override;

    virtual void drawParticles(Renderer& dest) const override;

    virtual void display(std::ostream&, size_t level = 0) const override;
};
