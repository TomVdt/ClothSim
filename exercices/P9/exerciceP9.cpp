#include "include/masse.h"
#include "include/integrator.h"
#include "include/cloth.h"
#include "include/system.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    EulerCromerIntegrator cromer;
    std::unique_ptr<Cloth> cloth(std::make_unique<Cloth>());
    System system;

    cloth->addMass(std::make_unique<Masse>(1, 0.3, Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
    cloth->addMass(std::make_unique<Masse>(1, 0.3, Vector3D(2, 0, 0), Vector3D(0, 0, 0)));
    cloth->addMass(std::make_unique<Masse>(1, 0.3, Vector3D(0, 0, 2), Vector3D(0, 0, 0)));
        
    cloth->connect(0, 1, 9, 1.5);
    cloth->connect(0, 2, 1.9, 1.75);
    cloth->connect(1, 2, 5.5, 1.25);

    // Ajout d'un tissu au système (le système possède les tissus)
    system.addCloth(std::move(cloth));

    cout << system << endl;

    return 0;
}
