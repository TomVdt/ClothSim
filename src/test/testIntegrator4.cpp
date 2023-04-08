#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/integrator.h"
#include "include/test.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/* définition d'un nouvel affichage pour un Vector3D avec un autre formatage */
void log(std::ostream& file, const Vector3D& vec) {
    file << vec.getX() << "," << vec.getY() << "," << vec.getZ();
}

void connectMassSpring(Masse& m1, Masse& m2, Spring& s) {
    s.connect(m1, m2);
    m1.connectSpring(s);
    m2.connectSpring(s);
}

int main() {
    EulerCromerIntegrator grator;

    // rotation autour d'un point
    Masse mass1(1, 0.3, {0, 0, 0}, {0, 0, 0});
    Masse mass2(1, 0.3, {2, 0, 0}, {0, 0, -1});
    Spring spring1(0.6, 3);
    connectMassSpring(mass1, mass2, spring1);
    
    std::ofstream file("testIntegrator4.txt", std::ofstream::out | std::ofstream::trunc);
    
    std::ostream& out(file.fail() ? cout : file);

    if (file.fail()) {
        cout << "# WARNING: le fichier n'a pas pu être ouvert." << endl;
    }

    // "Header" du txt
    out << "# x, y, z, x2, y2, z2" << endl;

    for (int i(0); i < 201; ++i) {
        log(out, mass1.getPos());
        out << ",";
        log(out, mass2.getPos());
        out << endl;
        mass1.updateForce();
        mass2.updateForce();

        // fixe la masse 1
        mass1.addForce(-mass1.getForce());

        grator.integrate(mass1, 0.1);
        grator.integrate(mass2, 0.1);
    }
    
    file.close();

    return 0;
}
