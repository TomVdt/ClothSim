#pragma once
#include "include/vector3d.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/drawable.h"
#include "include/renderer.h"

#include <vector>
#include <iostream>

class Constraint: public Drawable {
private:
    Vector3D pos;
    double radius;

public:
    Constraint(const Vector3D& pos, double radius);

    virtual ~Constraint() = default;

    const Vector3D& getPos() const { return pos; }

    double getRadius() const { return radius; }

    virtual bool isApplicable(const Masse& mass, double time) const;

    void apply(Cloth& cloth, double time) const;

    virtual void apply(Masse& mass, double time) const = 0;

    virtual void draw(Renderer& dest) override;

    virtual void display(std::ostream& out, size_t level = 0) const;
};

std::ostream& operator<<(std::ostream& out, const Constraint& constraint);

class HookConstraint: public Constraint {
public:
    HookConstraint(const Vector3D& pos, double radius): Constraint(pos, radius) {}
    
    virtual ~HookConstraint() = default;

    virtual void apply(Masse& mass, double time) const override;

    virtual void display(std::ostream& out, size_t level = 0) const override;
};

class ImpulsionConstraint: public Constraint {
private:
    std::vector<int> massIds;

    bool isInList(const Masse& mass) const;

    bool isInTime(double time) const;

protected:
    double startTime;
    double endTime;
    Vector3D force;

public:
    ImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, std::vector<Cloth*> targetCloths);

    virtual bool isApplicable(const Masse& mass, double time) const override;

    virtual void apply(Masse& mass, double time) const override;

    virtual void display(std::ostream& out, size_t level = 0) const override;
};

class SineImpulsionConstraint : public ImpulsionConstraint {
private:
    double frequency;

public:
    SineImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, double frequency, std::vector<Cloth*> targetCloths);

    virtual void apply(Masse& mass, double time) const override;

    virtual void display(std::ostream& out, size_t level = 0) const override;
};

class AttractionConstraint: public Constraint {
private:
    double intensity;
    double innerRadius;

public:
    AttractionConstraint(const Vector3D& pos, double spherOfInfluence, double intensity, double innerRadius);

    virtual void apply(Masse& mass, double time) const override;

    virtual void display(std::ostream& out, size_t level = 0) const override;
};
