#include "include/integrator.h"
#include "include/mass.h"
#include "include/vector3d.h"

#include <fstream>
#include <iostream>

/* définition d'un nouvel affichage pour un Vector3D avec un autre formatage */
void log(std::ostream& file, const Vector3D& vec) {
    file << vec.getX() << "," << vec.getY() << "," << vec.getZ();
}

int main() {
    NewmarkIntegrator grator;

    // chute libre: vitesse initiale, vitesse initiale nulle, uniquement vers le haut, λ non nul
    Mass mass1(0.127, 0, { 0, 1, 0 }, { 1, 2, 0 });
    Mass mass2(0.127, 0, { 0, 1, 0 }, { 0, 0, 0 });
    Mass mass3(0.127, 0, { 0, 1, 0 }, { 0, 2, 0 });
    Mass mass4(0.127, 0.3, { 0, 1, 0 }, { 1, 2, 0 });

    std::ofstream file("output/testNewmarkIntegrator.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? std::cout : file);
    if (file.fail()) {
        std::cout << "# WARNING: le fichier n'a pas pu être ouvert." << std::endl;
    }

    // "Header" du txt
    out << "# x, y, z" << std::endl;

    for (int i(0); i < 70; ++i) {
        log(out, mass1.getPos());
        out << ",";
        log(out, mass2.getPos());
        out << ",";
        log(out, mass3.getPos());
        out << ",";
        log(out, mass4.getPos());
        out << std::endl;
        mass1.updateForce();
        mass2.updateForce();
        mass3.updateForce();
        mass4.updateForce();
        grator.integrate(mass1, 0.01);
        grator.integrate(mass2, 0.01);
        grator.integrate(mass3, 0.01);
        grator.integrate(mass4, 0.01);
    }

    file.close();

    return 0;
}
