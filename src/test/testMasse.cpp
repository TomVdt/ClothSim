#include <iostream>
#include "include/test.h"
#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"

using std::cout;
using std::endl;

int main() {
    cout << "===== Test affichage =====" << endl;
    Masse m1(12.2);
    cout << m1;
    Masse m2(4.5, 2.3, {1.0, 1.0, 1.0}, {2.0, 2.0, 2.0});
    Spring s1(1.0, 1.0);
    Spring s2(2.0, 2.0);
    m2.connectSpring(&s1);
    m2.connectSpring(&s2);
    cout << m2;

    cout << endl << endl;
    cout << "===== Tests getters =====" << endl; 
    SHOW_TEST("getter masse", m1.getMass(), 12.2);
    SHOW_TEST("getter lambda", m2.getLambda(), 2.3);
    SHOW_TEST("getter position", m2.getPos(), Vector3D(1.0, 1.0, 1.0));
    SHOW_TEST("getter vitesse", m2.getVel(), Vector3D(2.0, 2.0, 2.0));
    SHOW_TEST("getter force", m2.getForce(), Vector3D(0.0, -9.81 * 4.5, 0));

    cout << endl << endl;
    cout << "===== Tests setters =====" << endl;
    m1.setPos(Vector3D(3.0, 3.0, 3.0));
    SHOW_TEST("setter position", m1.getPos(), Vector3D(3.0, 3.0, 3.0));
    m1.setVel(Vector3D(1.0, 2.0, 3.0));
    SHOW_TEST("setetr vitesse", m1.getVel(), Vector3D(1.0, 2.0, 3.0));

    cout << endl << endl;
    cout << "===== accélération et force =====" << endl;
    SHOW_TEST("accélération", m2.acceleration(), Vector3D(0.0, -9.81, 0.0));
    m2.addForce(Vector3D(1.0, 1.0, 1.0));
    SHOW_TEST("add force", m2.getForce(), Vector3D(1.0, -9.81*4.5 + 1.0, 1.0));
    m2.updateForce();
    SHOW_TEST("maj force", m2.getForce(), Vector3D(-2.3 * 2.0, -9.81*4.5 - 2.3*2.0, -2.3*2.0));

    cout << endl << endl;
    cout << "===== connections aux ressorts =====" << endl;
    m1.connectSpring(&s1);
    m1.connectSpring(&s2);
    m1.connectSpring(&s1);
    cout << "affiche : " << m1 << endl;
    cout << "devait afficher pour les ressorts: " << &s1 << " et " << &s2 << endl;
    m1.disconnectSpring(&s1);
    cout << "affiche : " << m1 << endl;
    cout << "devait afficher pour les ressorts: " << &s2 << endl;
    m2.disconnect();
    cout << "affiche: " << m2 << endl;
    cout << "ne devait rien afficher pour les ressorts";
    



    return 0;
}