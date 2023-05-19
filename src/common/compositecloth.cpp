#include "include/compositecloth.h"

CompositeCloth::CompositeCloth() {}

void CompositeCloth::linkCloth(std::unique_ptr<Cloth>&& newCloth) {
    if (cloths.empty()) {
        cloths.push_back(std::move(newCloth));
        return;
    }

    // Check if close enough
    bool connected = false;
    for (auto& cloth : cloths) {
        if (connectClothsConditional(*cloth, *newCloth)) {
            connected = true;
        }
    }
    
    if (not connected) {
        // TODO: exceptions
        throw "i hate myself";
    } else {
        cloths.push_back(std::move(newCloth));
    }
}

bool CompositeCloth::connectClothsConditional(Cloth& cloth1, Cloth& cloth2) {
    // bool hasConnected = false;
    // for (int i(0); i < cloth1.getMassCount(); ++i) {
    //     const Vector3D& pos(cloth1.getMassPos(i));
    //     std::vector<Masse*> masses(cloth2.getMassesInRange(pos, epsilon));
    //     std::unique_ptr<Spring> s(std::make_unique<Spring>(50.0, dist, *mass1, *mass2));
    //     mass1->connectSpring(*s);
    //     mass2->connectSpring(*s);
    //     springList.push_back(std::move(s));
    //     if (masses.size() > 0) {
    //         hasConnected = true;
    //     }
    // }

    // return hasConnected;
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
