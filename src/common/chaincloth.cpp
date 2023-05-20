#include "include/chaincloth.h"
#include "include/renderer.h"

#include <memory>

ChainCloth::ChainCloth(double mass, double lambda, double k, double l0, std::vector<Vector3D> pos) {
    // Add mass
    for (const auto& p : pos) {
        addMass(std::make_unique<Masse>(mass, lambda, p));
    }

    // Connect them
    for (size_t i(0); i < masses.size() - 1; ++i) {
        connect(i, i + 1, k, l0);
    }
}
