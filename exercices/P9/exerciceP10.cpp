#include "include/vector3d.h"
#include "include/masse.h"
#include "include/spring.h"
#include "include/integrator.h"
#include "include/textviewer.h"
#include "include/system.h"
#include "include/cloth.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

/* définition d'un nouvel affichage pour un Vector3D avec un autre formatage */
void log(std::ostream& file, const Vector3D& vec) {
    file << vec.getX() << "," << vec.getY() << "," << vec.getZ();
}

void connectMassSpring(Masse& m1, Masse& m2, Spring& s) {
    m1.connectSpring(s);
    m2.connectSpring(s);
}

int main() {
    EulerCromerIntegrator grator;

    Masse mass1(0.33, 0.3, { 0, -3, 0 }, { 0, 0, 0 });
    Masse mass2(1, 0.3, { -2, 0, 0 }, { 0, 0, 0 });
    Masse mass3(1, 0.3, { 0.5, 0, 0 }, { 0, 0, 0 });
    std::unique_ptr<Cloth> Tissu(new Cloth(ManyMass{&mass1, &mass2, &mass3}));
    Tissu->connect(0, 1, 0.6, 2.5);
    Tissu->connect(0, 2, 0.6, 2.5);

    System S(grator);

    S.addCloth(Tissu);

    S.addConstraint(mass2);
    S.addConstraint(mass3);


    std::ofstream file("exerciceP10.txt", std::ofstream::out | std::ofstream::trunc);

    std::ostream& out(file.fail() ? cout : file);
    if (file.fail()) {
        cout << "# WARNING: le fichier n'a pas pu être ouvert." << endl;
    }

    TextViewer fileviewer(out);
    TextViewer coutviewer(cout);

    // "Header" du txt
    out << "# x1, y1, z1, x2, y2, z2, x3, y3, z3" << endl;

    // Le 201ème point n'est pas loggé
    for (int i(0); i < 201; ++i) {
        if (i==0 or i==100 or i==200) {
            cout << "instance " << i << " du système:" << endl;
            coutviewer.draw(S);
            cout << endl;
        }
        log(out, mass1.getPos());
        out << ",";
        log(out, mass2.getPos());
        out << ",";
        log(out, mass3.getPos());
        out << endl;

        S.update();

    }

    file.close();

    return 0;
}
