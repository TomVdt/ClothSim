#include "include/exceptions.h"
#include "include/mass.h"
#include "include/spring.h"
#include "include/test.h"
#include "include/vector3d.h"

#include <iostream>

int main() {
    std::cout << "===== Test affichage =====\n";
    Mass m1(12.2);
    std::cout << m1 << "\n";

    // Les deux ressorts crée sont inactifs (les deux extrémités sur la même masse)
    // ils servent juste à vérifier le bon fonctionnement de l'affichage
    Mass m2(4.5, 2.3, { 1.0, 1.0, 1.0 }, { 2.0, 2.0, 2.0 });
    Spring s1(1.0, 1.0, m2, m2);
    Spring s2(2.0, 2.0, m2, m2);
    m2.connectSpring(s1);
    m2.connectSpring(s2);
    std::cout << m2 << "\n";

    std::cout << "\n===== Tests getters =====\n";
    assertmsg("getter masse", m1.getMass(), 12.2);
    assertmsg("getter lambda", m2.getLambda(), 2.3);
    assertmsg("getter position", m2.getPos(), Vector3D(1.0, 1.0, 1.0));
    assertmsg("getter vitesse", m2.getVel(), Vector3D(2.0, 2.0, 2.0));
    assertmsg("getter force", m2.getForce(), Vector3D(0.0, -9.81 * 4.5, 0));

    std::cout << "\n===== Tests setters =====\n";
    m1.setPos(Vector3D(3.0, 3.0, 3.0));
    assertmsg("setter position", m1.getPos(), Vector3D(3.0, 3.0, 3.0));
    m1.setVel(Vector3D(1.0, 2.0, 3.0));
    assertmsg("setter vitesse", m1.getVel(), Vector3D(1.0, 2.0, 3.0));

    std::cout << "\n===== accélération et force =====\n";
    assertmsg("acceleration", m2.acceleration(), Vector3D(0.0, -9.81, 0.0));
    m2.addForce(Vector3D(1.0, 1.0, 1.0));
    assertmsg("add force", m2.getForce(), Vector3D(1.0, -9.81 * 4.5 + 1.0, 1.0));
    m2.updateForce();
    assertmsg("maj force", m2.getForce(), Vector3D(-2.3 * 2.0, -9.81 * 4.5 - 2.3 * 2.0, -2.3 * 2.0));

    std::cout << "\n===== connections aux ressorts =====\n";
    m1.connectSpring(s1);
    m1.connectSpring(s2);
    m1.connectSpring(s1);
    assertmsg("connections", m1.springConnected(s1), true);
    assertmsg("connections", m1.springConnected(s2), true);
    std::cout << "affiche : " << m1 << "\n";
    std::cout << "devait afficher pour les ressorts: " << &s1 << " et " << &s2 << "\n";
    
    m1.disconnectSpring(s1);
    assertmsg("connections", m1.springConnected(s1), false);
    assertmsg("connections", m1.springConnected(s2), true);
    std::cout << "affiche : " << m1 << "\n";
    std::cout << "devait afficher pour les ressorts: " << &s2 << "\n";
    
    m2.disconnect();
    assertmsg("connections", m2.springConnected(s1), false);
    assertmsg("connections", m2.springConnected(s2), false);
    std::cout << "affiche: " << m2 << "\n";
    std::cout << "ne devait rien afficher pour les ressorts" << "\n";

    std::cout << "\n===== Exceptions =====\n";
    assertexception("Masse négative", Mass(-1), ValueError);
    assertexception("Masse nulle", Mass(0), ValueError);
    assertexception("Friction négative", Mass(1, -42), ValueError);

    return 0;
}