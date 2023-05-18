#include "include/compositecloth.h"
#include "include/exceptions.h"
#include "include/util.h"

CompositeCloth::CompositeCloth() {}

unsigned int CompositeCloth::getMassCount() const {
    unsigned int sum(0);
    for (const auto& cloth : cloths) {
        sum += cloth->getMassCount();
    }
    return sum;
}

unsigned int CompositeCloth::getSpringCount() const {
    unsigned int sum(0);
    for (const auto& cloth : cloths) {
        sum += cloth->getSpringCount();
    }
    return sum;
}

Masse& CompositeCloth::getMass(size_t index) const {
    if (index >= getMassCount()) {
        ERROR(IndexError, "Index out of range");
    }

    // Find in which cloth the mass could be
    unsigned int sum(0);
    for (const auto& cloth : cloths) {
        unsigned int size(cloth->getMassCount());
        if (index < sum + size) {
            return cloth->getMass(index - sum);
        }
        sum += index;
    }

    ERROR(UnreachableError, "This code should not get reached");
}

std::vector<Masse*> CompositeCloth::getMassesInRange(const Vector3D& pos, double radius) const {
    std::vector<Masse*> out;
    for (const auto& cloth : cloths) {
        auto masses(cloth->getMassesInRange(pos, radius));
        out.insert(out.end(), masses.begin(), masses.end());
    }
    return out;
}

bool CompositeCloth::check() const {
    for (const auto& cloth : cloths) {
        if (not cloth->check()) {
            return false;
        }
    }
    return true;
}

void CompositeCloth::linkCloth(std::unique_ptr<Cloth>&& newCloth, double k) {
    if (cloths.empty()) {
        cloths.push_back(std::move(newCloth));
        return;
    }

    // Check if close enough
    bool connected = false;
    for (auto& cloth : cloths) {
        if (connectClothsConditional(*cloth, *newCloth, k)) {
            connected = true;
        }
    }
    
    if (not connected) {
        ERROR(ConnectionError, "Failed to connect cloths");
    } else {
        cloths.push_back(std::move(newCloth));
    }
}

bool CompositeCloth::connectClothsConditional(Cloth& cloth1, Cloth& cloth2, double k) {
    bool hazConnected = false;
    for (int i(0); i < cloth1.getMassCount(); ++i) {
        for (int j(0); j < cloth2.getMassCount(); ++j) {
            Masse& mass1(cloth1.getMass(i));
            Masse& mass2(cloth2.getMass(j));
            const double dist(Vector3D::dist(mass1.getPos(), mass2.getPos()));
            if (dist < epsilon) {
                std::unique_ptr<Spring> s(std::make_unique<Spring>(k, dist, mass1, mass2));
                mass1.connectSpring(*s);
                mass2.connectSpring(*s);
                springList.push_back(std::move(s));
                hazConnected = true;
            }
        }
    }

    return hazConnected;
}

void CompositeCloth::updateForce() {
    for (auto& cloth : cloths) {
        cloth->updateForce();
    }
}

void CompositeCloth::step(Integrator const& integrator, double dt, std::vector<std::unique_ptr<Constraint>> const& constraints, double time) {
    for (auto& cloth : cloths) {
        cloth->step(integrator, dt, constraints, time);
    }
}

void CompositeCloth::drawParticles(Renderer& dest) const {
    for (const auto& cloth : cloths) {
        cloth->drawParticles(dest);
    }

    Cloth::drawParticles(dest);
}

void CompositeCloth::display(std::ostream& out, size_t level) const {
    out << indent(level) << "CompositeCloth " << this << " {\n";
    for (const auto& cloth : cloths) {
        cloth->display(out, level + 1);
        out << ",\n";
    }
    out << indent(level) << "}";
}
