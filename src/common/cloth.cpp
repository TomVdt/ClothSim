#include "include/cloth.h"
#include "include/exceptions.h"
#include "include/integrator.h"
#include "include/masse.h"
#include "include/renderer.h"
#include "include/spring.h"
#include "include/constraint.h"
#include "include/util.h"

#include <iostream>
#include <iomanip>

Cloth::Cloth(): masses(), springs() {}

const Vector3D& Cloth::getMassPos(size_t index) const {
    if (index >= masses.size()) {
        ERROR(IndexError, "Index out of range");
    }
    return masses[index]->getPos();
}

std::vector<int> Cloth::getMassIdsInRange(const Vector3D& pos, double radius) const {
    std::vector<int> out;
    for (auto& mass : masses) {
        if (Vector3D::dist(mass->getPos(), pos) < radius) {
            out.push_back(mass->getId());
        }
    }
    return out;
}

double Cloth::energy() const {
    double sum(0.0);
    for (const auto& mass : masses) {
        sum += mass->energy();
    }
    for (const auto& spring : springs) {
        sum += spring->energy();
    }
    return sum;
}

void Cloth::addMass(std::unique_ptr<Masse>&& mass) {
    masses.push_back(std::move(mass));
}

void Cloth::lootCorpse(std::vector<std::unique_ptr<Masse>>&& manyMass, std::vector<std::unique_ptr<Spring>>&& manySpring) {
    // Combine mass lists
    for (auto& mass : manyMass) {
        masses.push_back(std::move(mass));
    }
    // Combine spring lists
    for (auto& spring : manySpring) {
        springs.push_back(std::move(spring));
    }
}

void Cloth::giveGutsTo(Cloth& cloth) {
    cloth.lootCorpse(std::move(masses), std::move(springs));
    masses.clear();
    springs.clear();
}

void Cloth::connect(size_t m1, size_t m2, double k, double l0) {
    if (m1 == m2) {
        ERROR(ValueError, "Can't connect mass to itself");
    }
    const size_t taille(masses.size());
    if (m1 < taille and m2 < taille) {
        std::unique_ptr<Spring> s(std::make_unique<Spring>(k, l0, *masses[m1], *masses[m2]));
        masses[m1]->connectSpring(*s);
        masses[m2]->connectSpring(*s);
        springs.push_back(std::move(s));
    }
    else {
        ERROR(IndexError, "Index out of range");
    }
}

bool Cloth::check() const {
    for (auto& spring : springs) {
        if (not spring->areEndsValid()) return false;
    }
    return true;
}

void Cloth::updateForce() {
    for (auto& mass : masses) {
        mass->updateForce();
    }
}

void Cloth::addConstraint(const Constraint& constraint) {
    for (auto& mass : masses) {
        // todo: reference à la liste?
        mass->addConstraint(constraint);
    }
}

void Cloth::applyConstraint(const Constraint& constraint, double time) {
    for (auto& mass : masses) {
        mass->applyConstraint(constraint, time);
    }
}

void Cloth::applyConstraints(double time) {
    for (auto& mass : masses) {
        mass->applyConstraints(time);
    }
}

void Cloth::step(Integrator const& integratator, double dt, double time) {
    static unsigned int offset(1);
    const int N(getMassCount());
    for (int i(0); i < N; ++i) {
        Masse& mass(*masses[(i + offset) % N]);
        integratator.integrate(mass, dt, time);
    }
    offset += N / 6;
}

void Cloth::display(std::ostream& out, size_t level) const {
    out << indent(level) << "Cloth " << this << " {" << std::endl
        << indent(level + 1) << "masses (" << masses.size() << "): [" << std::endl;

    // Aucune masse ne peut etre un nullptr
    for (const auto& mass : masses) {
        mass->display(out, level + 2);
        out << std::endl;
    }
    out << indent(level + 1) << "]," << std::endl
        << indent(level + 1) << "ressorts (" << springs.size() << "): [" << std::endl;

    // Aucun spring ne peut etre un nullptr
    for (const auto& spring : springs) {
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
    for (auto& spring : springs) {
        spring->draw(dest);
    }

    for (auto& particle : masses) {
        particle->draw(dest);
    }
}

std::ostream& operator<<(std::ostream& out, const Cloth& cloth) {
    cloth.display(out);
    return out;
}
