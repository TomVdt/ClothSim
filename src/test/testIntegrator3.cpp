#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/integrator.h"
#include "include/test.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

void log(std::ostream& file, const Vector3D& vec) {
    file << vec.getX() << "," << vec.getY() << "," << vec.getZ();
}

int main() {
    EuleurCromerIntegrator grator;

    Masse mass1(0.33, 0.3, {0, -3, 0}, {0, 0, 0});
    Masse mass2(1, 0.3, {-2, 0, 0}, {0, 0, 0});
    Masse mass3(1, 0.3, {0.5, 0, 0}, {0, 0, 0});
    Spring spring1(0.6, 2.5, &mass1, &mass2);
    Spring spring2(0.6, 2.5, &mass1, &mass3);
    
    std::ofstream file("testIntegrator3.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? cout : file);
    if (file.fail()) {
        cout << "# WARNING: le fichier n'a pas pu être ouvert." << endl;
    }

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << endl;

    // Le 201ème point n'est pas loggé
    for (int i(0); i < 201; ++i) {
        log(out, mass1.getPos());
        out << ",";
        log(out, mass2.getPos());
        out << ",";
        log(out, mass3.getPos());
        out << endl;
        mass1.updateForce();
        mass2.updateForce();
        mass3.updateForce();

        // fixe les masses 2 et 3
        mass2.addForce(-mass2.getForce());
        mass3.addForce(-mass3.getForce());

        grator.integrate(&mass1, 0.1);
        grator.integrate(&mass2, 0.1);
        grator.integrate(&mass3, 0.1);
    }

    file.close();

    return 0;
}
