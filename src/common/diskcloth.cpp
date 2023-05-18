#include "include/diskcloth.h"
#include "include/exceptions.h"

DiskCloth::DiskCloth(double mass, const Vector3D& center, const Vector3D& radius, double radialStep, double lambda, double k, double angularStep) {
    if (radialStep <= 0.0) {
        ERROR(ValueError, "Radial step must be strictly positive");
    }
    
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

    const int diskCount(std::ceil(totalRadius / radialStep));
    const int countPerDisk(2 * M_PI / angularStep);
    
    for (int i(0); i < countPerDisk; i++) {
        while (currentRadius < totalRadius) {
            Vector3D pos(center + current * currentRadius);

            addMass(std::make_unique<Masse>(mass, lambda, pos));

            currentRadius += radialStep;
        }
        currentRadius = radialStep;
        current.rotate(angularStep, normal);
    }

    for (int a(0); a < countPerDisk; ++a) {
        for (int r(1); r < diskCount; ++r) {
            // Weird because 1st circle has a single mass... and I wanted to do this in a single loop
            int index(a * (diskCount - 1) + r);
            
            // Horrendous index math because of the layout...
            // complete circle then increase in radius would be easier to work with
            int right(index + diskCount - 1);
            if (right > massList.size() - 1) {
                right = (right % massList.size()) + 1;
            }
            double dist(
                Vector3D::dist(
                    massList[index]->getPos(), massList[right]->getPos()
                )
            );
            connect(index, right, k, dist);
            
            int inner(index - 1);
            if ((index - 1) % (diskCount - 1) == 0) {
                inner = 0;
            }
            dist = Vector3D::dist(
                massList[index]->getPos(), massList[inner]->getPos()
            );
            connect(index, inner, k, dist);
        }
    }
}