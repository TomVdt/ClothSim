#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/tissu.h"
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

int main() {
    EuleurCromerIntegrator grator;

    Masse mass1(1, 0.3, {0, 0, 0}, {0, 0, 0});
    Masse mass2(1, 0.3, {2, 0, 0}, {0, 0, 0});
    Masse mass3(1, 0.3, {0, 0, 2}, {0, 0, 0});
    // Masse mass4(1, 0.3, {2, 0, 2}, {0, 0, 0});

    ManyMass init_mass({&mass1, &mass2, &mass3});
    Tissu T1(init_mass);

    T1.connect(0, 1, 9, 1.5);
    T1.connect(0, 2, 1.9, 1.75);
    T1.connect(1, 2, 5.5, 1.25);
    // T1.connect(1, 3, 2.3, 1.45);
    // T1.connect(2, 3, 4.2, 1.65);
    

    std::ofstream file("testTissu1.txt", std::ofstream::out | std::ofstream::trunc);
    
    std::ostream& out(file.fail() ? cout : file);
    if (file.fail()) {
        cout << "# WARNING: le fichier n'a pas pu être ouvert." << endl;
    }

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << endl;

    for (int i(0); i < 201; ++i) {
        log(out, mass1.getPos());
        out << ",";
        log(out, mass2.getPos());
        out << ",";
        log(out, mass3.getPos());
        out << endl;

        T1.updateForce();

        double y(mass1.getForce().getY());
        mass1.addForce({0, -y, 0});
        y = mass2.getForce().getY();
        mass2.addForce({0, -y, 0});
        y = mass3.getForce().getY();
        mass3.addForce({0, -y, 0});

        T1.evolve(&grator, 0.1);
    }

    file.close();

    return 0;
}
