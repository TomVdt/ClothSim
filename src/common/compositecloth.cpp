#include "include/compositecloth.h"
#include "include/exceptions.h"
#include "include/util.h"

CompositeCloth::CompositeCloth() {}

void CompositeCloth::linkCloth(std::unique_ptr<Cloth>&& newCloth, double k) {
    // Base case for empty CompositeCloth
    bool connected(not masses.empty());
    for (auto& mass1 : masses) {
        for (auto& mass2 : newCloth->masses) {
            const double dist(Vector3D::dist(mass1->getPos(), mass2->getPos()));
            if (dist < epsilon) {
                // Les indices ne sont pas encore fixés, on ne peut donc pas utilser `connect`
                std::unique_ptr<Spring> s(std::make_unique<Spring>(k, dist, *mass1, *mass2));
                mass1->connectSpring(*s);
                mass2->connectSpring(*s);
                springs.push_back(std::move(s));
                connected = true;
            }
        }
    }
    
    if (not connected) {
        ERROR(ConnectionError, "Failed to connect cloths");
    }

    for (auto& mass : newCloth->masses) {
        masses.push_back(std::move(mass));
    }
    for (auto& spring : newCloth->springs) {
        springs.push_back(std::move(spring));
    }
    
    // newCloth peut être détruit, les masses et springs contenus ne sont plus utilisables
}
