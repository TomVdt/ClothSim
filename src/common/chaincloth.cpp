#include "include/chaincloth.h"
#include "include/exceptions.h"
#include "include/vector3d.h"

#include <memory>
#include <vector>

ChainCloth::ChainCloth(double mass, double lambda, double k, double l0, std::vector<Vector3D> pos) {
    // Add mass
    for (const auto& p : pos) {
        addMass(mass, lambda, p);
    }

    // Connect them
    for (size_t i(0); i < masses.size() - 1; ++i) {
        if (masses[i]->getPos() == masses[i + 1]->getPos()) {
            ERROR(ValueError, "Connected masses may not have the same position");
        }
        connect(i, i + 1, k, l0);
    }
}
