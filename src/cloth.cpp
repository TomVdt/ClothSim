#include "include/cloth.h"
#include "include/exceptions.h"
#include "include/integrator.h"
#include "include/masse.h"
#include "include/renderer.h"
#include "include/spring.h"
#include "include/util.h"

#include <iostream>
#include <iomanip>

Cloth::Cloth(const ManyMass& init_mass): massList(init_mass), springList() {}

Cloth::Cloth(const ManyMass& init_mass, const std::vector<std::pair<size_t, size_t>>& connections): massList(init_mass), springList() {
    for (const auto& conn : connections) {
        connect(conn.first, conn.second);
    }
}

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
        if (not spring->valid()) return false;
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
    return new Cloth(newMass);
}

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
