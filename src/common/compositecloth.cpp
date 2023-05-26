#include "include/compositecloth.h"
#include "include/exceptions.h"
#include "include/util.h"

void CompositeCloth::linkCloth(std::unique_ptr<Cloth>&& newCloth) {
    // Mama, just killed a man
    // Put a gun against his head, pulled my trigger, now he's dead
    auto pair(newCloth->lootCorpse());
    // Mama, life had just begun
    auto& newMasses(pair.first);
    // But now I've gone and thrown it all away
    auto& newSprings(pair.second);

    // Mama, ooh, didn't mean to make you cry
    bool connected(masses.empty());
    for (auto& mass1 : masses) {
        for (auto& mass2 : newMasses) {
            const double dist(Vector3D::dist(mass1->getPos(), mass2->getPos()));
            if (dist < delta) {
                // Les indices ne sont pas encore fixés, on ne peut donc pas utilser `connect`
                std::unique_ptr<Spring> s(std::make_unique<Spring>(k, dist, *mass1, *mass2));
                mass1->connectSpring(*s);
                mass2->connectSpring(*s);
                springs.push_back(std::move(s));
                connected = true;
            }
        }
    }
    
    // If I'm not back again this time tomorrow
    if (not connected) {
        ERROR(ConnectionError, "Failed to connect cloths");
    }

    // Carry on, carry on as if nothing really matters
    for (auto& mass : newMasses) {
        masses.push_back(std::move(mass));
    }
    for (auto& spring : newSprings) {
        springs.push_back(std::move(spring));
    }
}
