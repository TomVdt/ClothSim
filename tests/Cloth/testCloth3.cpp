#include "include/cloth.h"
#include "include/exceptions.h"
#include "include/integrator.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/test.h"
#include "include/vector3d.h"

#include <iostream>
#include <memory>

int main() {
    EulerCromerIntegrator integrator;
    Cloth cloth;

    std::cout << "==== Tissu vide ====\n";
    std::cout << cloth << "\n";

    std::cout << "\n==== Ajout de masses ====\n";
    Masse* mass1(new Masse(1, 0.3, Vector3D(0, 0, 0), Vector3D(0, 0, 0)));
    Masse* mass2(new Masse(1, 0.3, Vector3D(2, 0, 0), Vector3D(0, 0, 0)));
    Masse* mass3(new Masse(1, 0.3, Vector3D(0, 0, 2), Vector3D(0, 0, 0)));
    // Ok de créer des unique_ptr, le tissu vit aussi longtemps que les masses
    cloth.addMass(std::unique_ptr<Masse>(mass1));
    cloth.addMass(std::unique_ptr<Masse>(mass2));
    cloth.addMass(std::unique_ptr<Masse>(mass3));

    assertmsg("Nombre de masses", cloth.getMassCount(), 3u);
    assertmsg("Nombre de ressorts", cloth.getSpringCount(), 0u);

    std::cout << "\n==== Connection des masses ====\n";
    cloth.connect(0, 1, 9, 1.5);
    cloth.connect(0, 2, 1.9, 1.75);
    cloth.connect(1, 2, 5.5, 1.25);

    assertmsg("Nombre de masses", cloth.getMassCount(), 3u);
    assertmsg("Nombre de ressorts", cloth.getSpringCount(), 3u);
    assertmsg("Valide", cloth.check(), true);

    std::cout << "\n==== Mise a jour des forces et step ====\n";
    cloth.updateForce();
    cloth.step(integrator);
    std::cout << cloth << "\n";

    std::cout << "\n==== Exceptions ====\n";
    assertexception("Position d'une masse pas dans le tissu", cloth.getMassPos(42), IndexError);
    assertexception("Connection de masses pas dans le tissu", cloth.connect(42, 69), IndexError);
    assertexception("Connection d'une masse à elle même", cloth.connect(0, 0), ValueError);

    std::cout << "\n==== Suicide de tissu ====\n";
    Cloth tmpCloth;
    cloth.giveGutsTo(tmpCloth);
    std::cout << cloth << "\n";
    std::cout << tmpCloth << "\n";
    assertmsg("Nombre de masses", cloth.getMassCount(), 0u);
    assertmsg("Nombre de ressorts", cloth.getSpringCount(), 0u);
    assertmsg("Nombre de masses transmises", tmpCloth.getMassCount(), 3u);
    assertmsg("Nombre de ressorts transmis", tmpCloth.getSpringCount(), 3u);

    return 0;
}
