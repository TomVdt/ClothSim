#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/integrator.h"
#include "include/test.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

int main() {
    EuleurCromerIntegrator grator;
    Masse mass1(1, 0.3, {0, 0, 0}, {0, 0, 0});
    Masse mass2(1, 0.3, {2, 0, 0}, {0, 0, 0});
    Masse mass3(1, 0.3, {0, 0, 2}, {0, 0, 0});
    Spring spring1(9, 1.5, &mass1, &mass2);
    Spring spring2(1.9, 1.75, &mass1, &mass3);
    Spring spring3(5.5, 1.25, &mass2, &mass3);
    std::ofstream file("testIntegrator2.txt", std::ofstream::out | std::ofstream::trunc);
    
    if (file.fail()) {
        cout << "# WARNING: le fichier n'a pas pu être ouvert." << endl;
        return 1;
    }

    // "Header" du txt
    file << "# x, y, z" << endl;

    for (int i(0); i < 200; ++i) {
        cout << mass1 << endl;
        Vector3D pos1(mass1.getPos());
        Vector3D pos2(mass2.getPos());
        Vector3D pos3(mass3.getPos());
        file << pos1.getX() << "," << pos1.getY() << "," << pos1.getZ() << ","
             << pos2.getX() << "," << pos2.getY() << "," << pos2.getZ() << ","
             << pos3.getX() << "," << pos3.getY() << "," << pos3.getZ() << endl;
        mass1.updateForce();
        mass2.updateForce();
        mass3.updateForce();

        double y(mass1.getForce().getY());
        mass1.addForce({0, -y, 0});
        y = mass2.getForce().getY();
        mass2.addForce({0, -y, 0});
        y = mass3.getForce().getY();
        mass3.addForce({0, -y, 0});

        grator.integrate(&mass1, 0.1);
        grator.integrate(&mass2, 0.1);
        grator.integrate(&mass3, 0.1);
    }

    cout << mass1 << endl;
    Vector3D pos1(mass1.getPos());
    Vector3D pos2(mass2.getPos());
    Vector3D pos3(mass3.getPos());
    file << pos1.getX() << "," << pos1.getY() << "," << pos1.getZ() << ","
            << pos2.getX() << "," << pos2.getY() << "," << pos2.getZ() << ","
            << pos3.getX() << "," << pos3.getY() << "," << pos3.getZ() << endl;
    
    file.close();

    return 0;
}
