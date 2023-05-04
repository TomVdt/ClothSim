#include "include/diskcloth.h"

DiskCloth::DiskCloth(double mass, const Vector3D& center, const Vector3D& radius, double radialStep, double lambda, double k, double angularStep) {
    // TODO: exceptions
    if (radialStep < 0.0) {
        return;
    }
    
    addMass(std::make_unique<Masse>(mass, lambda, center, Vector3D(), true));

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

    // std::cout << diskCount << ", " << countPerDisk << ", " << massList.size() << "\n";
    for (int a(0); a < countPerDisk; ++a) {
        for (int r(1); r < diskCount; ++r) {
            // Weird because 1st circle has a single mass
            int index(a * (diskCount - 1) + r);
            
            // Horrendous index math because of the layout...
            // complete circle then increase in radius would be easier to work with
            int right(index + diskCount - 1);
            if (right > massList.size() - 1) {
                right = (right % massList.size()) + 1;
            }
            // std::cout << "right: " << index << ", " << right << "\n";
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
            // std::cout << "inner: " << index << ", " << inner << "\n";
            dist = Vector3D::dist(
                massList[index]->getPos(), massList[inner]->getPos()
            );
            connect(index, inner, k, dist);
        }
    }
}