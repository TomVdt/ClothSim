#include "include/cloth.h"
#include "include/exceptions.h"
#include "include/integrator.h"
#include "include/masse.h"
#include "include/renderer.h"
#include "include/spring.h"
#include "include/util.h"

#include <iostream>
#include <iomanip>


/* les deux premiers constructeurs servent à tester le bon fonctionnement du tissu
* normalement il ne revient pas à l'utilisateur de créer les masses */
Cloth::Cloth(const ManyMass& init_mass): massList(init_mass), springList() {}

Cloth::Cloth(const ManyMass& init_mass, const std::vector<std::pair<size_t, size_t>>& connections): massList(init_mass), springList() {
    for (const auto& conn : connections) {
        connect(conn.first, conn.second);
    }
}


Cloth::Cloth(ShapeCloth shape, double mass, double distance, int number_width, int number_height, Connections connections): massList(), springList() {
    if (number_height <= 0 or number_width <= 0) {
        throw InvalidValueException("des nombres positifs stp pour les lignes et les colonnes");
    }
    
    if (shape == square) {
        number_height = number_width;
    }

    if (shape == rectangle or shape == square) {
        // crée toutes les masses du rectangle ligne par ligne
        for (int line(0); line < number_height; ++line) {
            for (int column(0); column < number_width; ++column) {
                massList.push_back(new Masse( mass, 0.0, Vector3D(column * distance, line * distance, 0) ));
            }
        }

        /* fait les liens entre les masses dans la même colonne et dans la même ligne,
        * entre n masses alignées il y a n-1 ressorts */
        for (int line(0); line < number_height-1; ++line) {
            for (int column(0); column < number_width-1; ++column) {
                int current(line * number_width + column);
                connect(current, current + 1);
                connect(current, current + number_width);
                // fait les liens en diagonale si nécessaire
                if (connections == diagonals) {
                    connect(current, current + number_width + 1);
                }
            }
            connect((line + 1) * number_width - 1, (line + 2) * number_width - 1 );
        }
        for (int column(0); column < number_width-1; ++column) {
            int current((number_height-1) * number_width + column);
            connect(current, current + 1);
        }
    }
}                                   // TODO: dans la deuxieme et 3e grosse boucle for on utilise des int comme des size_t oupsi


Cloth::~Cloth() {
    for (const auto& mass : massList) {
        delete mass;
    }
    for (const auto& spring : springList) {
        delete spring;
    }
}

unsigned int Cloth::getMassCount() const { return massList.size(); }

unsigned int Cloth::getSpringCount() const { return springList.size(); }

void Cloth::connect(size_t m1, size_t m2, double k, double l0) {
    const size_t taille(massList.size());
    if (m1 < taille and m2 < taille) {
        Spring* s(new Spring(k, l0, *massList[m1], *massList[m2]));
        massList[m1]->connectSpring(*s);
        massList[m2]->connectSpring(*s);
        springList.push_back(s);
    }
    else {
        throw OutOfBoundsException("y a pas autant de masses dans le tissu je tiens à mon cpu");
    }
}

bool Cloth::check() const {
    for (auto& spring : springList) {
        if (not spring->areEndsValid()) return false;
    }
    return true;
}

void Cloth::updateForce() {
    for (auto& mass : massList) {
        mass->updateForce();
    }
}

void Cloth::evolve(const Integrator& integratator, double dt) {
    for (auto& mass : massList) {
        integratator.integrate(*mass, dt);
    }
}

Cloth* Cloth::copy() const {
    ManyMass newMass;
    for (const auto& mass : massList) {
        newMass.push_back(mass->copy());
    }
    // les espaces mémoires alloués pour les masses seront libérés par le destructeur du nouveau tissu
    return new Cloth(newMass);
    // TODO: c'est vraiment une bonne idée d'allouer dynamiquement dans un return comme ca? faut que l'utilisateur face un delete du coup
}


//void Cloth::trou(size_t mass) {}



void Cloth::display(std::ostream& out, size_t level) const {
    out << indent(level) << "Cloth " << this << " {" << std::endl
        << indent(level + 1) << "masses (" << massList.size() << "): [" << std::endl;

    // Aucune masse ne peut etre un nullptr
    for (const auto& mass : massList) {
        mass->display(out, level + 2);
        out << std::endl;
    }
    out << indent(level + 1) << "]," << std::endl
        << indent(level + 1) << "ressorts (" << springList.size() << "): [" << std::endl;

    // Aucun spring ne peut etre un nullptr
    for (const auto& spring : springList) {
        spring->display(out, level + 2);
        out << std::endl;
    }
    out << indent(level + 1) << "]" << std::endl
        << indent(level) << "}";
}

void Cloth::draw(Renderer& dest) { dest.draw(*this); }


std::ostream& operator<<(std::ostream& out, const Cloth& cloth) {
    cloth.display(out);
    return out;
}
