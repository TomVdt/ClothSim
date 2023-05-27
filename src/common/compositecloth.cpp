#include "include/compositecloth.h"
#include "include/exceptions.h"
#include "include/util.h"

#include <memory>
#include <utility>
#include <vector>

void CompositeCloth::linkCloth(std::unique_ptr<Cloth>&& newCloth) {
    newCloth->giveGutsTo(*this);
}

void CompositeCloth::lootCorpse(std::vector<std::unique_ptr<Masse>>&& manyMass, std::vector<std::unique_ptr<Spring>>&& manySpring) {
    std::vector<std::pair<size_t, size_t>> toConnect;
    for (size_t i(0); i < getMassCount(); ++i) {
        for (size_t j(0); j < manyMass.size(); ++j) {
            const double dist(
                Vector3D::dist(
                    masses[i]->getPos(), manyMass[j]->getPos()
                )
            );
            if (dist < delta) {
                // Offset j by current mass count to take into account the merging of the lists
                toConnect.emplace_back(i, getMassCount() + j);
            }
        }
    }

    // Raise an error if unable to make any connections, but don't if the composite cloth is empty
    if (toConnect.empty() and not masses.empty()) {
        ERROR(ConnectionError, "Failed to connect cloths");
    }

    // Combine lists
    Cloth::lootCorpse(std::move(manyMass), std::move(manySpring));

    // Make the pending connections
    for (auto& pair : toConnect) {
        const double dist(
            Vector3D::dist(
                masses[pair.first]->getPos(), masses[pair.second]->getPos()
            )
        );
        connect(pair.first, pair.second, k, dist);
    }
}
