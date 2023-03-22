#include <iostream>

#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/test.h"

using std::cout;
using std::endl;

int main() {
    Spring spring1(1, 1);
    Masse mass1(1, 0, {0, 0, 0});
    Masse mass2(1, 0, {1, 0, 0});

    cout << "=== Pre-connection ===" << endl;
    cout << spring1 << endl;

    spring1.connect(&mass1, &mass2);

    cout << "=== Post-connection ===" << endl;
    cout << spring1 << endl;

    cout << "=== Forces ressorts ===" << endl;
    Spring spring2(1, 2);
    Spring spring3(1, 0.5);
    spring2.connect(&mass1, &mass2);
    spring3.connect(&mass1, &mass2);

    SHOW_TEST("Ressort 1 stable", spring1.springForce(&mass1), Vector3D());
    SHOW_TEST("Ressort 1 stable", spring1.springForce(&mass2), Vector3D());
    SHOW_TEST("Ressort 2 etendu", spring2.springForce(&mass1), Vector3D(1, 0, 0));
    SHOW_TEST("Ressort 2 etendu", spring2.springForce(&mass2), Vector3D(-1, 0, 0));
    SHOW_TEST("Ressort 3 compresse", spring3.springForce(&mass1), Vector3D(-0.5, 0, 0));
    SHOW_TEST("Ressort 3 compresse", spring3.springForce(&mass2), Vector3D(0.5, 0, 0));

    Spring spring4(1, 10);
    Masse mass3(1, 0, {4, 3, 0});
    spring4.connect(&mass1, &mass3);
    SHOW_TEST("Ressort 4 diagonal", spring4.springForce(&mass1), Vector3D(4, 3, 0));
    SHOW_TEST("Ressort 4 diagonal", spring4.springForce(&mass3), Vector3D(-4, -3, 0));
    
    Spring spring5(1, 10);
    Masse mass4(1, 0, {0.000001, 0, 0});
    spring5.connect(&mass1, &mass4);
    SHOW_TEST("Surcompression", spring5.springForce(&mass1), Vector3D(9.999999, 0, 0));

    cout << "=== Springs malformés ===" << endl;
    Spring spring6(1, 1);
    SHOW_TEST("Pas de masses", spring6.valid(), false);
    spring6.connect(&mass1, nullptr);
    SHOW_TEST("1 masse", spring6.valid(), false);
    spring6.connect(&mass1, &mass1);
    SHOW_TEST("2 masses identiques", spring6.valid(), false);
    SHOW_TEST("Ressort correct", spring1.valid(), true);

    cout << "=== Changement des masses (pos, vel, etc) ===" << endl;
    Spring spring7(1, 1);
    Masse mass5(1.0);
    Masse mass6(2.0);
    spring7.connect(&mass5, &mass6);

    cout << "Avant changement: " << spring7;

    mass5.setPos({69, 42, 6});
    mass6.setVel({420, 420, 420});

    cout << "Après changement: " << spring7;

    cout << "=== Effets sur les masses ===" << endl;

    cout << "Masse 1: " << mass1 << endl;

    return 0;
}
