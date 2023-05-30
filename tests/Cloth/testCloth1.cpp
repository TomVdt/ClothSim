#include "include/cloth.h"
#include "include/impulsionconstraint.h"
#include "include/integrator.h"
#include "include/mass.h"
#include "include/spring.h"
#include "include/test.h"
#include "include/vector3d.h"

#include <fstream>
#include <iostream>
#include <memory>

/* définition d'un nouvel affichage pour un Vector3D avec un autre formatage */
void log(std::ostream& file, const Vector3D& vec) {
    file << vec.getX() << "," << vec.getY() << "," << vec.getZ();
}

int main() {
    EulerCromerIntegrator integrator;
    Cloth cloth;

    cloth.addMass(1, 0.3, Vector3D(0, 0, 0), Vector3D(0, 0, 0));
    cloth.addMass(1, 0.3, Vector3D(2, 0, 0), Vector3D(0, 0, 0));
    cloth.addMass(1, 0.3, Vector3D(0, 0, 2), Vector3D(0, 0, 0));

    cloth.connect(0, 1, 9, 1.5);
    cloth.connect(0, 2, 1.9, 1.75);
    cloth.connect(1, 2, 5.5, 1.25);

    // La contrainte annule le poids
    ImpulsionConstraint constraint(Vector3D(), 10, 0, 100, Vector3D(), { &cloth });
    cloth.addConstraint(constraint);

    assertmsg("Tissu valide", cloth.check(), true);

    std::ofstream file("output/testCloth1.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? std::cout : file);
    if (file.fail()) {
        std::cout << "# WARNING: le fichier n'a pas pu être ouvert." << std::endl;
    }

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << std::endl;

    for (int i(0); i < 201; ++i) {
        log(out, cloth.getMassPos(0));
        out << ",";
        log(out, cloth.getMassPos(1));
        out << ",";
        log(out, cloth.getMassPos(2));
        out << std::endl;

        cloth.updateForce();
        cloth.applyConstraints(0.1 * i);

        cloth.step(integrator, 0.1);
    }

    file.close();

    return 0;
}
