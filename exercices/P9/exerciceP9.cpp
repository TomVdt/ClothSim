#include "include/cloth.h"
#include "include/eulercromerintegrator.h"
#include "include/mass.h"
#include "include/system.h"

#include <iostream>

// "Dessinable" -> common/include/drawable.h
// "SupportADessin" -> common/include/renderer.h
// "Systeme" -> common/include/system.h, common/system.cpp

int main() {
    EulerCromerIntegrator cromer;
    std::unique_ptr<Cloth> cloth(std::make_unique<Cloth>());
    System system;

    cloth->addMass(0.33, 0.3, Vector3D(0, -3, 0), Vector3D(0, 0, 0));
    cloth->addMass(1, 0.3, Vector3D(-0.5, 0, 0), Vector3D(0, 0, 0));
    cloth->addMass(1, 0.3, Vector3D(0.5, 0, 0), Vector3D(0, 0, 0));
    cloth->connect(0, 1, 0.6, 2.5);
    cloth->connect(0, 2, 0.6, 2.5);

    // Ajout d'un tissu au système (le système possède les tissus)
    system.addCloth(std::move(cloth));

    std::cout << system << "\n";

    return 0;
}
