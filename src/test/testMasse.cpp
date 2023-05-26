#include <iostream>
#include "include/test.h"
#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/exceptions.h"

using std::cout;

int main() {
    cout << "===== Test affichage =====\n";
    Masse m1(12.2);
    cout << m1 << "\n";

    // Les deux ressorts crée sont inactifs (les deux extrémités sur la même masse)
    // ils servent juste à vérifier le bon fonctionnement de l'affichage
    Masse m2(4.5, 2.3, { 1.0, 1.0, 1.0 }, { 2.0, 2.0, 2.0 });
    Spring s1(1.0, 1.0, m2, m2);
    Spring s2(2.0, 2.0, m2, m2);
    m2.connectSpring(s1);
    m2.connectSpring(s2);
    cout << m2 << "\n";

    cout << "\n===== Tests getters =====\n";
    assertmsg("getter masse", m1.getMass(), 12.2);
    assertmsg("getter lambda", m2.getLambda(), 2.3);
    assertmsg("getter position", m2.getPos(), Vector3D(1.0, 1.0, 1.0));
    assertmsg("getter vitesse", m2.getVel(), Vector3D(2.0, 2.0, 2.0));
    assertmsg("getter force", m2.getForce(), Vector3D(0.0, -9.81 * 4.5, 0));

    cout << "\n===== Tests setters =====\n";
    m1.setPos(Vector3D(3.0, 3.0, 3.0));
    assertmsg("setter position", m1.getPos(), Vector3D(3.0, 3.0, 3.0));
    m1.setVel(Vector3D(1.0, 2.0, 3.0));
    assertmsg("setter vitesse", m1.getVel(), Vector3D(1.0, 2.0, 3.0));

    cout << "\n===== accélération et force =====\n";
    assertmsg("acceleration", m2.acceleration(), Vector3D(0.0, -9.81, 0.0));
    m2.addForce(Vector3D(1.0, 1.0, 1.0));
    assertmsg("add force", m2.getForce(), Vector3D(1.0, -9.81 * 4.5 + 1.0, 1.0));
    m2.updateForce();
    assertmsg("maj force", m2.getForce(), Vector3D(-2.3 * 2.0, -9.81 * 4.5 - 2.3 * 2.0, -2.3 * 2.0));

    cout << "\n===== connections aux ressorts =====\n";
    m1.connectSpring(s1);
    m1.connectSpring(s2);
    m1.connectSpring(s1);
    assertmsg("connections", m1.springConnected(s1), true);
    assertmsg("connections", m1.springConnected(s2), true);
    cout << "affiche : " << m1 << "\n";
    cout << "devait afficher pour les ressorts: " << &s1 << " et " << &s2 << "\n";
    
    m1.disconnectSpring(s1);
    assertmsg("connections", m1.springConnected(s1), false);
    assertmsg("connections", m1.springConnected(s2), true);
    cout << "affiche : " << m1 << "\n";
    cout << "devait afficher pour les ressorts: " << &s2 << "\n";
    
    m2.disconnect();
    assertmsg("connections", m2.springConnected(s1), false);
    assertmsg("connections", m2.springConnected(s2), false);
    cout << "affiche: " << m2 << "\n";
    cout << "ne devait rien afficher pour les ressorts" << "\n";

    cout << "\n===== Exceptions =====\n";
    assertexception("Masse négative", Masse(-1), ValueError);
    assertexception("Masse nulle", Masse(0), ValueError);
    assertexception("Friction négative", Masse(1, -42), ValueError);

    return 0;
}