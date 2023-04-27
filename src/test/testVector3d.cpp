#include <iostream>
#include "include/vector3d.h"
#include "include/test.h"

using std::cout;

int main() {
    const Vector3D vec1(1.0, 2.0, -0.1);
    const Vector3D vec2(2.6, 3.5, 4.1);
    const Vector3D zero(0.0, 0.0, 0.0);
    const Vector3D random(1.0, 2.0, 3.0);
    Vector3D tobeset(6.9, 4.2, 6.0);

    cout << "==== Affichage ====\n";
    cout << "Vec1: " << vec1 << "\n";

    cout << "\n==== Sanity check ====\n";
    assertmsg("Coords", vec1.getX(), 1.0);
    assertmsg("Coords", vec1.getY(), 2.0);
    assertmsg("Coords", vec1.getZ(), -0.1);
    tobeset.setX(42.0);
    assertmsg("Setter", tobeset.getX(), 42.0);
    tobeset.setY(42.0);
    assertmsg("Setter", tobeset.getY(), 42.0);
    tobeset.setZ(42.0);
    assertmsg("Setter", tobeset.getZ(), 42.0);
    assertmsg("Constructeur 1", Vector3D(), zero);
    assertmsg("Constructeur 2", Vector3D(1, 2.0, 3), random);
    assertmsg("Copie", Vector3D(vec1), vec1);

    cout << "\n==== Interface ====\n";
    const Vector3D threezerozero(3.0, 0.0, 0.0);
    Vector3D zerofivezero_to_mod(0.0, 5.0, 0.0);
    assertmsg("Norme", threezerozero.norm(), 3.0);
    assertmsg("Norme2", vec1.normSq(), 5.01);
    assertmsg("Norme2", vec2.normSq(), 35.82);
    assertmsg("Unitaire", threezerozero.normalized(), Vector3D(1.0, 0.0, 0.0));
    assertmsg("Unitaire en-place", zerofivezero_to_mod.normalize(), Vector3D(0.0, 1.0, 0.0));
    assertmsg("Scalaire", vec1.dot(vec2), 9.19);
    assertmsg("Scalaire commutatif", vec2.dot(vec1), 9.19);
    assertmsg("Vectoriel", vec1.cross(vec2), Vector3D(8.55, -4.36, -1.7));
    assertmsg("Vectoriel anticommutatif", vec2.cross(vec1), Vector3D(-8.55, 4.36, 1.7));

    cout << "\n==== Opérateurs ====\n";
    assertmsg("Addition", vec1 + vec2, Vector3D(3.6, 5.5, 4));
    assertmsg("Addition commutative", vec2 + vec1, Vector3D(3.6, 5.5, 4));
    assertmsg("Addition zero", vec2 + Vector3D(), Vector3D(2.6, 3.5, 4.1));
    assertmsg("Addition oppose", vec1 + (-vec2), Vector3D(-1.6, -1.5, -4.2));
    assertmsg("Soustraction", vec1 - vec2, Vector3D(-1.6, -1.5, -4.2));
    assertmsg("Soustraction self", vec1 - vec1, zero);
    assertmsg("Oppose", -vec1, Vector3D(-1, -2, 0.1));
    assertmsg("Multiplication entier", vec1 * 2, Vector3D(2, 4, -0.2));
    assertmsg("Multiplication", vec1 * 2.0, Vector3D(2, 4, -0.2));
    assertmsg("Multiplication commutative", 2.0 * vec1, Vector3D(2, 4, -0.2));
    assertmsg("Division entier", vec1 / 2, Vector3D(0.5, 1, -0.05));
    assertmsg("Division", vec1 / 2.0, Vector3D(0.5, 1, -0.05));

    assertmsg("Scalaire", vec1* vec2, 9.19);
    assertmsg("Vectoriel", vec1^ vec2, Vector3D(8.55, -4.36, -1.7));
    assertmsg("Unitaire", ~threezerozero, Vector3D(1.0, 0.0, 0.0));

    Vector3D presqueZero(0.01, 0.0, 0.0);
    assertmsg("Egalite", vec1 == vec1, true);
    assertmsg("Egalite", vec1 == vec2, false);
    assertmsg("Egalite proche", zero == presqueZero, false);
    assertmsg("Different", vec1 != vec1, false);
    assertmsg("Different", vec1 != vec2, true);

    cout << "\n==== Opérateurs en place ====\n";
    Vector3D changeme1(1.0, 2.0, 3.0);
    Vector3D changeme2(2.0, 4.0, 6.0);
    Vector3D changeme3(4.0, 8.0, 12.0);
    Vector3D changeme4(1.0, 2.0, 3.0);
    assertmsg("+=", changeme1 += changeme1, changeme2);
    assertmsg("*=", changeme2 *= 2.0, changeme3);
    assertmsg("/=", changeme3 /= 4.0, changeme4);
    assertmsg("-=", changeme4 -= changeme4, zero);

    return 0;
}
