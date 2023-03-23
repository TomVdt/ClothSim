#include "include/vector3d.h"
#include "include/masse.h"
#include "include/integrator.h"
#include "include/test.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

int main() {
    EuleurCromerIntegrator grator;
    Masse mass1(1, 0, {0, 0, 0}, {1, 0, 0});
    std::ofstream file("testIntegrator1.txt", std::ofstream::out | std::ofstream::trunc);
    
    if (file.fail()) {
        cout << "# WARNING: le fichier n'a pas pu être ouvert." << endl;
        return 1;
    }

    // "Header" du txt
    file << "# x, y, z" << endl;

    for (int i(0); i < 42; ++i) {
        cout << mass1 << endl;
        Vector3D pos(mass1.getPos());
        file << pos.getX() << "," << pos.getY() << "," << pos.getZ() << endl;
        mass1.updateForce();
        grator.integrate(&mass1, 0.1);
    }

    cout << mass1 << endl;
    Vector3D pos(mass1.getPos());
    file << pos.getX() << "," << pos.getY() << "," << pos.getZ() << endl;
        
    file.close();

    return 0;
}
