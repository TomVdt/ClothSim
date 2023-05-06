#pragma once
#include "include/vector3d.h"
#include "include/masse.h"
#include "include/cloth.h"

#include <vector>

class Constraint {
private:
    Vector3D pos;
    double radius;

protected:
    bool isInRange(const Masse& masse) const;

public:
    Constraint(const Vector3D& pos, double radius);

    virtual ~Constraint() = default;

    void apply(Cloth& cloth, double time) const;

    virtual void apply(Masse& mass, double time) const = 0;
};

class HookConstraint: public Constraint {
public:
    HookConstraint(const Vector3D& pos, double radius);
    
    virtual ~HookConstraint() = default;

    virtual void apply(Masse& mass, double time) const override;
};

class ImpulsionConstraint: public Constraint {
private:
    std::vector<Masse*> masses;

protected:
    double startTime;
    double endTime;
    Vector3D force;

    bool isInList(const Masse& mass) const;

    bool isInTime(double time) const;

public:
    ImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, std::vector<Cloth*> targetCloths);

    virtual void apply(Masse& mass, double time) const override;
};

class SineImpulsionConstraint : public ImpulsionConstraint {
private:
    double frequency;

public:
    SineImpulsionConstraint(const Vector3D& pos, double radius, double start, double end, const Vector3D& force, double frequency, std::vector<Cloth*> targetCloths);

    virtual void apply(Masse& mass, double time) const override;
};
