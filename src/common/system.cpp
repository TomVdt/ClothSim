#include "include/cloth.h"
#include "include/exceptions.h"
#include "include/renderer.h"
#include "include/system.h"
#include "include/util.h"
#include "include/vector3d.h"

void System::addCloth(std::unique_ptr<Cloth>&& cloth) {
    cloths.push_back(std::move(cloth));
}

double System::energy() const {
    double sum(0.0);
    for (const auto& cloth : cloths) {
        sum += cloth->energy();
    }
    return sum;
}

void System::step(const Integrator& integrator, double dt) {
    for (auto& cloth : cloths) {
        cloth->updateForce();
        cloth->applyConstraints(time);
        // TODO: revoir ca
        cloth->step(integrator, dt, time);
    }
    time += dt;
}

void System::addConstraint(std::unique_ptr<Constraint>&& constraint) {
    constraints.push_back(std::move(constraint));
    for (auto& cloth : cloths) {
        cloth->addConstraint(*constraints.back());
    }
}

void System::clear() {
    cloths.clear();
    constraints.clear();
    time = 0.0;
}

void System::draw(Renderer& dest) {
    dest.draw(*this);
}

void System::drawContents(Renderer& dest) const {
    for (auto& cloth : cloths) {
        cloth->draw(dest);
    }

    for (auto& constraint : constraints) {
        constraint->draw(dest);
    }
}

void System::display(std::ostream& out, size_t level) const {
    unsigned int massCount(0);
    unsigned int springCount(0);

    out << indent(level) << "System " << this << " {" << std::endl
        << indent(level + 1) << "temps: " << time << std::endl
        << indent(level + 1) << "tissus: [" << std::endl;
    for (const auto& cloth : cloths) {
        cloth->display(out, level + 2);
        out << std::endl;
        massCount += cloth->getMassCount();
        springCount += cloth->getSpringCount();
    }
    out << indent(level + 1) << "]," << std::endl
        << indent(level + 1) << "contraintes: [" << std::endl;
    for (const auto& constraint : constraints) {
        constraint->display(out, level + 2);
        out << std::endl;
    }
    out << indent(level + 1) << "]," << std::endl
        << indent(level + 1) << "masses: " << massCount << "," << std::endl
        << indent(level + 1) << "ressorts: " << springCount << std::endl
        << indent(level) << "}";
}

std::ostream& operator<<(std::ostream& out, const System& system) {
    system.display(out);
    return out;
}
