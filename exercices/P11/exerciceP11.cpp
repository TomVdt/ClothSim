#include "include/cloth.h"
#include "include/constraint.h"
#include "include/masse.h"
#include "include/system.h"
#include "include/vector3d.h"
#include "include/window.h"

// La majorité de l'implémentation pour l'exercice P11 se situe dans le repertoire "app/openglrenderer.[cpp,h]" et "app/window.[cpp,h]"
// Ceci est simplement une démo de l'exercice P10, en mode graphique

int main() {
    System system;
    
    Cloth* cloth(new Cloth());

    cloth->addMass(std::make_unique<Masse>(0.33, 0.3, Vector3D(0, -3, 0), Vector3D(0, 0, 0)));
    cloth->addMass(std::make_unique<Masse>(1, 0.3, Vector3D(-0.5, 0, 0), Vector3D(0, 0, 0)));
    cloth->addMass(std::make_unique<Masse>(1, 0.3, Vector3D(0.5, 0, 0), Vector3D(0, 0, 0)));
    cloth->connect(0, 1, 0.6, 2.5);
    cloth->connect(0, 2, 0.6, 2.5);

    system.addCloth(std::unique_ptr<Cloth>(cloth));

    system.addConstraint(std::make_unique<HookConstraint>(Vector3D(-0.5, 0, 0), 0.1));
    system.addConstraint(std::make_unique<HookConstraint>(Vector3D(0.5, 0, 0), 0.1));

    Window window(std::move(system));
    window.run();

    return 0;
}
