#include <iostream>
#include "include/vector3d.h"
#include "include/test.h"

using std::cout;
using std::endl;

int main() {
    Vector3D vec1(1.0, 2.0, -0.1);
    Vector3D vec2(2.6, 3.5, 4.1);
    Vector3D zero(0.0, 0.0, 0.0);
    Vector3D random(1.0, 2.0, 3.0);
    Vector3D tobeset(6.9, 4.2, 6.0);

    cout << "=== Sanity check ===" << endl;
    SHOW_TEST("Coords", vec1.getX(), 1.0);
    SHOW_TEST("Coords", vec1.getY(), 2.0);
    SHOW_TEST("Coords", vec1.getZ(), -0.1);
    SHOW_TEST("Setter", {tobeset.setX(42.0); tobeset.getX();}, 42.0);
    SHOW_TEST("Affichage", vec1, vec1);  // auto-pass (arbitrary)
    SHOW_TEST("Constructeur 1", Vector3D(), zero);
    SHOW_TEST("Constructeur 2", Vector3D(1, 2.0, 3), random);
    SHOW_TEST("Copie", Vector3D(vec1), vec1);

    cout << "=== Interface ===" << endl;
    Vector3D threezerozero(3.0, 0.0, 0.0);
    SHOW_TEST("Norme", threezerozero.norm(), 3.0);
    SHOW_TEST("Norme2", vec1.normSq(), 5.01);  // eq on double
    SHOW_TEST("Norme2", vec2.normSq(), 35.82);  // eq on double
    SHOW_TEST("Unitaire", threezerozero.normalized(), Vector3D(1.0, 0.0, 0.0));
    SHOW_TEST("Unitaire", Vector3D(1.0, 0.0, 0.0).normalized(), Vector3D(1.0, 0.0, 0.0));
    SHOW_TEST("Scalaire", vec1.dot(vec2), 9.19);
    SHOW_TEST("Scalaire commutatif", vec2.dot(vec1), 9.19);
    SHOW_TEST("Vectoriel", vec1.cross(vec2), Vector3D(8.55, -4.36, -1.7));
    SHOW_TEST("Vectoriel anticommutatif", vec2.cross(vec1), Vector3D(-8.55, 4.36, 1.7));

    cout << "=== Opérateurs ===" << endl;
    SHOW_TEST("Affichage", vec1, vec1);  // auto-pass (arbitrary)
    SHOW_TEST("Affichage", vec2, vec2);  // auto-pass (arbitrary)
    SHOW_TEST("Addition", vec1 + vec2, Vector3D(3.6, 5.5, 4));
    SHOW_TEST("Addition commutative", vec2 + vec1, Vector3D(3.6, 5.5, 4));
    SHOW_TEST("Addition zero", vec2 + Vector3D(), Vector3D(2.6, 3.5, 4.1));
    SHOW_TEST("Addition oppose", vec1 + (-vec2), Vector3D(-1.6, -1.5, -4.2));
    SHOW_TEST("Soustraction", vec1 - vec2, Vector3D(-1.6, -1.5, -4.2));
    SHOW_TEST("Soustraction self", vec1 - vec1, zero);
    SHOW_TEST("Oppose", -vec1, Vector3D(-1, -2, 0.1));
    SHOW_TEST("Multiplication entier", vec1 * 2, Vector3D(2, 4, 0.2));
    SHOW_TEST("Multiplication", vec1 * 2.0, Vector3D(2, 4, 0.2));
    SHOW_TEST("Multiplication commutative", 2.0 * vec1, Vector3D(2, 4, 0.2));
    SHOW_TEST("Division entier", vec1 / 2, Vector3D(0.5, 1, 0.05));
    SHOW_TEST("Division", vec1 / 2.0, Vector3D(0.5, 1, 0.05));

    SHOW_TEST("Scalaire", vec1 * vec2, 9.19);
    SHOW_TEST("Vectoriel", vec1 ^ vec2, Vector3D(8.55, -4.36, -1.7));
    
    SHOW_TEST("Egalite", vec1 == vec1, true);
    SHOW_TEST("Egalite", vec1 == vec2, false);
    SHOW_TEST("Different", vec1 != vec1, false);
    SHOW_TEST("Different", vec1 != vec2, true);

    cout << "=== Opérateurs en place ===" << endl;
    cout << "! affichage faux, tests corrects !" << endl;
    Vector3D changeme1(1.0, 2.0, 3.0);
    Vector3D changeme2(2.0, 4.0, 6.0);
    Vector3D changeme3(4.0, 8.0, 12.0);
    Vector3D changeme4(1.0, 2.0, 3.0);
    SHOW_TEST("+=", changeme1 += changeme1, changeme2);
    SHOW_TEST("*=", changeme2 *= 2.0, changeme3);
    SHOW_TEST("/=", changeme3 /= 4.0, changeme4);
    SHOW_TEST("-=", changeme4 -= changeme4, zero);

    return 0;
}
