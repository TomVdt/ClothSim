#include "include/cloth.h"
#include "include/exceptions.h"
#include "include/integrator.h"
#include "include/masse.h"
#include "include/renderer.h"
#include "include/spring.h"
#include "include/util.h"

#include <iostream>
#include <iomanip>

Cloth::Cloth(): massList(), springList() {}

unsigned int Cloth::getMassCount() const {
    return massList.size();
}

unsigned int Cloth::getSpringCount() const {
    return springList.size();
}

const std::vector<std::unique_ptr<Masse>>& Cloth::getMasses() const {
    return massList;
}


void Cloth::addMass(std::unique_ptr<Masse>&& mass) {
    massList.push_back(std::move(mass));
}

void Cloth::connect(size_t m1, size_t m2, double k, double l0) {
    const size_t taille(massList.size());
    if (m1 < taille and m2 < taille) {
        std::unique_ptr<Spring> s(std::make_unique<Spring>(k, l0, *massList[m1], *massList[m2]));
        massList[m1]->connectSpring(*s);
        massList[m2]->connectSpring(*s);
        springList.push_back(std::move(s));
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

void Cloth::step(const Integrator& integratator, double dt) {
    for (auto& mass : massList) {
        integratator.integrate(*mass, dt);
    }
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

void Cloth::draw(Renderer& dest) {
    dest.draw(*this);
}

void Cloth::drawParticles(Renderer& dest) const {
    for (auto& particle : massList) {
        particle->draw(dest);
    }

    for (auto& spring : springList) {
        spring->draw(dest);
    }
}

std::ostream& operator<<(std::ostream& out, const Cloth& cloth) {
    cloth.display(out);
    return out;
}
