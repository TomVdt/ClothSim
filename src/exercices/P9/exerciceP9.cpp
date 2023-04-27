#include "include/masse.h"
#include "include/integrator.h"
#include "include/cloth.h"
#include "include/system.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    EulerCromerIntegrator cromer;
    System system(cromer);

    // Création d'un tissu
    Masse* mass1(new Masse(1, 0.3, { 0, 0, 0 }, { 0, 0, 0 }));
    Masse* mass2(new Masse(1, 0.3, { 2, 0, 0 }, { 0, 0, 0 }));
    Masse* mass3(new Masse(1, 0.3, { 0, 0, 2 }, { 0, 0, 0 }));
    
    std::unique_ptr<Cloth> cloth(new Cloth(ManyMass({ mass1, mass2, mass3 })));
    cloth->connect(0, 1, 9, 1.5);
    cloth->connect(0, 2, 1.9, 1.75);
    cloth->connect(1, 2, 5.5, 1.25);

    // Ajout d'un tissu au système (le système possède les tissus)
    system.addCloth(std::move(cloth));

    cout << system << endl;

    return 0;
}
