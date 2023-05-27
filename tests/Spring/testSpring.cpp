#include "include/masse.h"
#include "include/spring.h"
#include "include/test.h"
#include "include/vector3d.h"

#include <iostream>

int main() {
    Masse mass1(1, 0, { 0, 0, 0 });
    Masse mass2(1, 0, { 1, 0, 0 });
    Spring spring1(1, 1, mass1, mass2);

    std::cout << "==== Pre-connection ====\n";
    std::cout << "Spring 1: " << spring1 << "\n";

    mass1.connectSpring(spring1);
    mass2.connectSpring(spring1);

    std::cout << "\n==== Post-connection ====\n";
    std::cout << "Spring 1: " << spring1 << "\n";

    std::cout << "\n==== Forces ressorts ====\n";
    Spring spring2(1, 2, mass1, mass2);
    Spring spring3(1, 0.5, mass1, mass2);
    mass1.connectSpring(spring2);
    mass2.connectSpring(spring2);
    mass1.connectSpring(spring3);
    mass2.connectSpring(spring3);

    assertmsg("Ressort 1 stable", spring1.springForce(mass1), Vector3D());
    assertmsg("Ressort 1 stable", spring1.springForce(mass2), Vector3D());
    assertmsg("Ressort 2 compressé", spring2.springForce(mass1), Vector3D(-1, 0, 0));
    assertmsg("Ressort 2 compressé", spring2.springForce(mass2), Vector3D(1, 0, 0));
    assertmsg("Ressort 3 étendu", spring3.springForce(mass1), Vector3D(0.5, 0, 0));
    assertmsg("Ressort 3 étendu", spring3.springForce(mass2), Vector3D(-0.5, 0, 0));

    Masse mass3(1, 0, { 4, 3, 0 });
    Spring spring4(1, 10, mass1, mass3);
    mass1.connectSpring(spring4);
    mass3.connectSpring(spring4);
    assertmsg("Ressort 4 diagonal", spring4.springForce(mass1), Vector3D(-4, -3, 0));
    assertmsg("Ressort 4 diagonal", spring4.springForce(mass3), Vector3D(4, 3, 0));

    Masse mass4(1, 0, { 0.000001, 0, 0 });
    Spring spring5(1, 10, mass1, mass4);
    mass1.connectSpring(spring5);
    mass4.connectSpring(spring5);
    assertmsg("Surcompression", spring5.springForce(mass1), Vector3D(-9.999999, 0, 0));

    std::cout << "\n==== Springs malformés ====\n" << "\n";
    Spring spring6(1, 1, mass1, mass1);
    assertmsg("2 masses identiques", spring6.valid(), false);
    assertmsg("Ressort correct", spring1.valid(), true);

    std::cout << "\n==== Changement des masses (pos, vel, etc) ====\n";
    Masse mass5(1.0);
    Masse mass6(2.0);
    Spring spring7(1, 1, mass5, mass6);
    mass5.connectSpring(spring7);
    mass6.connectSpring(spring7);

    std::cout << "Avant changement Spring 7: " << spring7 << "\n";
    mass5.setPos({ 69, 42, 6 });
    mass6.setVel({ 420, 420, 420 });
    std::cout << "Après changement Spring 7: " << spring7 << "\n";

    std::cout << "\n==== Methodes d'aide ====\n";
    Spring spring8(1, 1, mass5, mass6);
    mass5.connectSpring(spring8);
    assertmsg("Connection complete fausse", spring8.areEndsValid(), false);
    mass6.connectSpring(spring8);
    assertmsg("Connection complete", spring8.areEndsValid(), true);

    return 0;
}
