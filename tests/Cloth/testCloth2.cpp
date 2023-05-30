#include "include/cloth.h"
#include "include/constraint.h"
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

    cloth.addMass(0.33, 0.3, Vector3D(0, -3, 0), Vector3D(0, 0, 0));
    cloth.addMass(1, 0.3, Vector3D(-0.5, 0, 0), Vector3D(0, 0, 0));
    cloth.addMass(1, 0.3, Vector3D(0.5, 0, 0), Vector3D(0, 0, 0));

    cloth.connect(0, 1, 0.6, 2.5);
    cloth.connect(0, 2, 0.6, 2.5);

    HookConstraint constraint1(Vector3D(-0.5, 0, 0), 0.1);
    HookConstraint constraint2(Vector3D(0.5, 0, 0), 0.1);
    cloth.addConstraint(constraint1);
    cloth.addConstraint(constraint2);

    assertmsg("Tissu valide", cloth.check(), true);

    std::ofstream file("output/testCloth2.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? std::cout : file);
    if (file.fail()) {
        std::cout << "# WARNING: le fichier n'a pas pu être ouvert." << std::endl;
    }

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << std::endl;

    // Le 201ème point n'est pas loggé
    for (int i(0); i < 201; ++i) {
        // Pour faciliter le traitement des données après, on utilise getMassPos au lieu de cout << cloth
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
