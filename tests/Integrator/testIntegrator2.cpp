#include "include/eulercromerintegrator.h"
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

    Mass mass1(1, 0.3, { 0, 0, 0 }, { 0, 0, 0 });
    Mass mass2(1, 0.3, { 2, 0, 0 }, { 0, 0, 0 });
    Mass mass3(1, 0.3, { 0, 0, 2 }, { 0, 0, 0 });
    Spring spring1(9, 1.5, mass1, mass2);
    connectMassSpring(mass1, mass2, spring1);
    Spring spring2(1.9, 1.75, mass1, mass3);
    connectMassSpring(mass1, mass3, spring2);
    Spring spring3(5.5, 1.25, mass2, mass3);
    connectMassSpring(mass2, mass3, spring3);

    std::ofstream file("output/testIntegrator2.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? std::cout : file);
    if (file.fail()) {
        std::cout << "# WARNING: le fichier n'a pas pu être ouvert." << std::endl;
    }

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << std::endl;

    for (int i(0); i < 10; ++i) {
        log(out, mass1.getPos());
        out << ",";
        log(out, mass2.getPos());
        out << ",";
        log(out, mass3.getPos());
        out << std::endl;
        mass1.updateForce();
        mass2.updateForce();
        mass3.updateForce();

        double y(mass1.getForce().getY());
        mass1.addForce({ 0, -y, 0 });
        y = mass2.getForce().getY();
        mass2.addForce({ 0, -y, 0 });
        y = mass3.getForce().getY();
        mass3.addForce({ 0, -y, 0 });

        grator.integrate(mass1, 0.1);
        grator.integrate(mass2, 0.1);
        grator.integrate(mass3, 0.1);
    }

    file.close();

    return 0;
}
