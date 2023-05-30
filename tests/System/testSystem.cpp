#include "include/cloth.h"
#include "include/integrator.h"
#include "include/mass.h"
#include "include/system.h"

#include <iostream>
#include <memory>

int main() {
    EulerCromerIntegrator cromer;
    std::unique_ptr<Cloth> cloth(std::make_unique<Cloth>());
    System system;

    std::cout << "=== Système vide ===\n";
    std::cout << system << "\n";

    cloth->addMass(0.33, 0.3, Vector3D(0, -3, 0), Vector3D(0, 0, 0));
    cloth->addMass(1, 0.3, Vector3D(-0.5, 0, 0), Vector3D(0, 0, 0));
    cloth->addMass(1, 0.3, Vector3D(0.5, 0, 0), Vector3D(0, 0, 0));
    cloth->connect(0, 1, 0.6, 2.5);
    cloth->connect(0, 2, 0.6, 2.5);

    // Ajout d'un tissu au système (le système possède les tissus)
    system.addCloth(std::move(cloth));

    std::cout << "=== Systeme avec tissu ===\n";
    std::cout << system << "\n";
    std::cout << "Energie du système: " << system.energy() << "\n";

    std::cout << "=== Avancement d'un pas de temps ===\n";
    system.step(cromer);
    std::cout << system << "\n";
    std::cout << "Energie du système: " << system.energy() << "\n";

    std::cout << "=== Energie du système après 5 sec ===\n";
    for (int i(0); i < 500; ++i) system.step(cromer, 0.01);
    std::cout << system << "\n";
    std::cout << "Energie du système: " << system.energy() << "\n";

    return 0;
}
