#include "include/diskcloth.h"
#include "include/exceptions.h"

#include <cmath>

DiskCloth::DiskCloth(double mass, const Vector3D& center, const Vector3D& radius, double radialStep, double lambda, double k, double angularStep) {
    if (radialStep < CONSTANTS::EPSILON) {
        ERROR(ValueError, "Radial step must be strictly positive");
    }

    if (angularStep < -M_PI or angularStep > M_PI) {
        ERROR(ValueError, "Angular step must be between -π and π");
    }

    if (std::abs(angularStep) < CONSTANTS::EPSILON) {
        ERROR(ValueError, "Angular step must not be 0");
    }
    
    // Central mass
    addMass(std::make_unique<Masse>(mass, lambda, center));

    const double totalRadius(radius.norm());
    double currentRadius(radialStep);

    Vector3D normal(radius.normalized());
    Vector3D current;
    if (normal == Vector3D(1.0, 0.0, 0.0)) {
        current = Vector3D(0.0, 1.0, 0.0);
    } else {
        current = Vector3D(0, -normal.getZ(), normal.getY());
    }

    // Number of rings
    const unsigned int diskCount(std::floor(totalRadius / radialStep));
    // Number of masses per ring
    const unsigned int countPerDisk(std::abs(2.0 * M_PI / angularStep));

    for (unsigned int i(0); i < countPerDisk; ++i) {
        for (unsigned int j(0); j < diskCount; ++j) {
            Vector3D pos(center + current * currentRadius);

            addMass(std::make_unique<Masse>(mass, lambda, pos));

            currentRadius += radialStep;
        }
        currentRadius = radialStep;
        current.rotate(angularStep, normal);
    }

    for (unsigned int a(0); a < countPerDisk; ++a) {
        for (unsigned int r(0); r < diskCount; ++r) {
            // Weird because 1st circle has a single mass.
            unsigned int index(1 + a * diskCount + r);
            
            unsigned int right(index + diskCount);
            // Edge case
            if (right > masses.size() - 1) {
                right = right % masses.size() + 1;
            }
            double dist(
                Vector3D::dist(
                    masses[index]->getPos(), masses[right]->getPos()
                )
            );
            connect(index, right, k, dist);
            
            unsigned int inner(index - 1);
            // Inner ring
            if (index % diskCount == 1) {
                inner = 0;
            }
            dist = Vector3D::dist(
                masses[index]->getPos(), masses[inner]->getPos()
            );
            connect(index, inner, k, dist);
        }
    }
}