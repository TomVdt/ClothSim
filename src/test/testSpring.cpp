#include <iostream>

#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/test.h"

using std::cout;
using std::endl;

void connectMassSpring(Masse& m1, Masse& m2, Spring& s) {
    m1.connectSpring(s);
    m2.connectSpring(s);
}

int main() {
    Masse mass1(1, 0, { 0, 0, 0 });
    Masse mass2(1, 0, { 1, 0, 0 });
    Spring spring1(1, 1, mass1, mass2);

    cout << "=== Pre-connection ===" << endl;
    cout << spring1 << endl;

    connectMassSpring(mass1, mass2, spring1);

    cout << endl << "=== Post-connection ===" << endl;
    cout << spring1 << endl;

    cout << endl << "=== Forces ressorts ===" << endl;
    Spring spring2(1, 2, mass1, mass2);
    Spring spring3(1, 0.5, mass1, mass2);
    connectMassSpring(mass1, mass2, spring2);
    connectMassSpring(mass1, mass2, spring3);

    SHOW_TEST("Ressort 1 stable", spring1.springForce(mass1), Vector3D());
    SHOW_TEST("Ressort 1 stable", spring1.springForce(mass2), Vector3D());
    SHOW_TEST("Ressort 2 compressé", spring2.springForce(mass1), Vector3D(-1, 0, 0));
    SHOW_TEST("Ressort 2 compressé", spring2.springForce(mass2), Vector3D(1, 0, 0));
    SHOW_TEST("Ressort 3 étendu", spring3.springForce(mass1), Vector3D(0.5, 0, 0));
    SHOW_TEST("Ressort 3 étendu", spring3.springForce(mass2), Vector3D(-0.5, 0, 0));

    Masse mass3(1, 0, { 4, 3, 0 });
    Spring spring4(1, 10, mass1, mass3);
    connectMassSpring(mass1, mass3, spring4);
    SHOW_TEST("Ressort 4 diagonal", spring4.springForce(mass1), Vector3D(-4, -3, 0));
    SHOW_TEST("Ressort 4 diagonal", spring4.springForce(mass3), Vector3D(4, 3, 0));

    Masse mass4(1, 0, { 0.000001, 0, 0 });
    Spring spring5(1, 10, mass1, mass4);
    connectMassSpring(mass1, mass4, spring5);
    SHOW_TEST("Surcompression", spring5.springForce(mass1), Vector3D(-9.999999, 0, 0));

    cout << endl << "=== Springs malformés ===" << endl;
    // On utilise des références, on est donc garanti d'avoir 2 masses connectées
    Spring spring6(1, 1, mass1, mass1);
    SHOW_TEST("2 masses identiques", spring6.valid(), false);
    SHOW_TEST("Ressort correct", spring1.valid(), true);

    cout << endl << "=== Changement des masses (pos, vel, etc) ===" << endl;
    Masse mass5(1.0);
    Masse mass6(2.0);
    Spring spring7(1, 1, mass5, mass6);
    connectMassSpring(mass5, mass6, spring7);

    cout << "Avant changement: " << spring7 << endl;

    mass5.setPos({ 69, 42, 6 });
    mass6.setVel({ 420, 420, 420 });

    cout << "Après changement: " << spring7 << endl;

    cout << endl << "=== Effets sur les masses ===" << endl;

    cout << "Masse 1: " << mass1 << endl;

    cout << endl << "=== Methodes d'aide ===" << endl;

    Spring spring8(1, 1, mass5, mass6);
    SHOW_TEST("Connection incomplete", spring8.areEndsValid(), false);
    connectMassSpring(mass5, mass5, spring8);
    SHOW_TEST("Connection complete fausse", spring8.areEndsValid(), false);
    connectMassSpring(mass5, mass6, spring8);
    SHOW_TEST("Connection complete", spring8.areEndsValid(), true);

    return 0;
}
