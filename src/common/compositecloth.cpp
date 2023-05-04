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
    bool tmp = false;
    for (auto& mass1 : cloth1.getMasses()) {
        for (auto& mass2 : cloth2.getMasses()) {
            const double dist(Vector3D::dist(mass1->getPos(), mass2->getPos()));
            if (dist < epsilon) {                
                std::unique_ptr<Spring> s(std::make_unique<Spring>(50.0, dist, *mass1, *mass2));
                mass1->connectSpring(*s);
                mass2->connectSpring(*s);
                springList.push_back(std::move(s));
                tmp = true;
            }
        }
    }

    return tmp;
}

void CompositeCloth::updateForce() {
    for (auto& cloth : cloths) {
        cloth->updateForce();
    }
}

void CompositeCloth::step(const Integrator& integrator, double dt) {
    for (auto& cloth : cloths) {
        cloth->step(integrator, dt);
    }
}

void CompositeCloth::drawParticles(Renderer& dest) const {
    for (const auto& cloth : cloths) {
        cloth->drawParticles(dest);
    }

    Cloth::drawParticles(dest);
}
