#include "include/integrator.h"
#include "include/mass.h"
#include "include/spring.h"
#include "include/vector3d.h"

#include <fstream>
#include <iostream>

/* définition d'un nouvel affichage pour un Vector3D avec un autre formatage */
void log(std::ostream& file, const Vector3D& vec) {
    file << vec.getX() << "," << vec.getY() << "," << vec.getZ();
}

void connectMassSpring(Mass& m1, Mass& m2, Spring& s) {
    m1.connectSpring(s);
    m2.connectSpring(s);
}

int main() {
    EulerCromerIntegrator grator;

    Mass mass1(0.33, 0.3, { 0, -3, 0 }, { 0, 0, 0 });
    Mass mass2(1, 0.3, { -0.5, 0, 0 }, { 0, 0, 0 });
    Mass mass3(1, 0.3, { 0.5, 0, 0 }, { 0, 0, 0 });
    Spring spring1(0.6, 2.5, mass1, mass2);
    connectMassSpring(mass1, mass2, spring1);
    Spring spring2(0.6, 2.5, mass1, mass3);
    connectMassSpring(mass1, mass3, spring2);

    std::ofstream file("output/testIntegrator3.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? std::cout : file);
    if (file.fail()) {
        std::cout << "# WARNING: le fichier n'a pas pu être ouvert." << std::endl;
    }

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << std::endl;

    // Le 201ème point n'est pas loggé
    for (int i(0); i < 201; ++i) {
        log(out, mass1.getPos());
        out << ",";
        log(out, mass2.getPos());
        out << ",";
        log(out, mass3.getPos());
        out << std::endl;
        mass1.updateForce();
        mass2.updateForce();
        mass3.updateForce();

        // fixe les masses 2 et 3
        mass2.addForce(-mass2.getForce());
        mass3.addForce(-mass3.getForce());

        grator.integrate(mass1, 0.1);
        grator.integrate(mass2, 0.1);
        grator.integrate(mass3, 0.1);
    }

    file.close();

    return 0;
}
