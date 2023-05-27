#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/integrator.h"
#include "include/test.h"
#include "include/cloth.h"

#include <iostream>
#include <memory>
#include <fstream>

using std::cout;
using std::endl;

/* définition d'un nouvel affichage pour un Vector3D avec un autre formatage */
void log(std::ostream& file, const Vector3D& vec) {
    file << vec.getX() << "," << vec.getY() << "," << vec.getZ();
}

int main() {
    EulerCromerIntegrator integrator;
    Cloth cloth;

    Masse* mass1(new Masse(1, 0.3, Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
    Masse* mass2(new Masse(1, 0.3, Vector3D(2, 0, 0), Vector3D(0, 0, 0)));
    Masse* mass3(new Masse(1, 0.3, Vector3D(0, 0, 2), Vector3D(0, 0, 0)));

    // Ok de créer des unique_ptr, le tissu vit aussi longtemps que les masses
    cloth.addMass(std::unique_ptr<Masse>(mass1));
    cloth.addMass(std::unique_ptr<Masse>(mass2));
    cloth.addMass(std::unique_ptr<Masse>(mass3));

    cloth.connect(0, 1, 9, 1.5);
    cloth.connect(0, 2, 1.9, 1.75);
    cloth.connect(1, 2, 5.5, 1.25);

    std::ofstream file("output/testCloth1.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? cout : file);
    if (file.fail()) {
        cout << "# WARNING: le fichier n'a pas pu être ouvert." << endl;
    }

    if (cloth.check()) {
        out << "# le tissu est cohérent yey" << endl;
    }
    else {
        out << "# problème notre tissu a transcendé la réalité pour atteindre de nouveaux plans d'existence" << endl;
        file.close();
        return 1;
    }

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << endl;

    for (int i(0); i < 201; ++i) {
        log(out, mass1->getPos());
        out << ",";
        log(out, mass2->getPos());
        out << ",";
        log(out, mass3->getPos());
        out << endl;

        cloth.updateForce();

        double y(mass1->getForce().getY());
        mass1->addForce({ 0, -y, 0 });
        y = mass2->getForce().getY();
        mass2->addForce({ 0, -y, 0 });
        y = mass3->getForce().getY();
        mass3->addForce({ 0, -y, 0 });

        cloth.step(integrator, 0.1);
    }

    file.close();

    return 0;
}