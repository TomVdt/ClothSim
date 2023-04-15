#include "include/system.h"
#include "include/cloth.h"
#include "include/renderer.h"
#include "include/exceptions.h"
#include "include/util.h"
#include "include/masse.h"
#include "include/vector3d.h"


void System::addCloth(std::unique_ptr<Cloth>& cloth) {
    cloths.push_back(std::move(cloth));
}

void System::step(Integrator& integrator, double dt) {
    for (auto& cloth : cloths) {
        cloth->updateForce();
        for (auto& constraint : manyConstraints) {
            if (constraint.attached) {
                constraint.masse.addForce(-constraint.masse.getForce());
            }
        }
        cloth->step(integrator, dt);
    }
}

void System::addConstraint(Masse& mass, bool attached) {
    manyConstraints.push_back(Constraint{mass, attached});
}

void System::draw(Renderer& dest) {
    dest.draw(*this);
}

void System::drawContents(Renderer& dest) const {
    for (auto& cloth : cloths) {
        cloth->draw(dest);
    }
}

void System::display(std::ostream& out, size_t level) const {
    unsigned int massCount(0);
    unsigned int springCount(0);

    out << indent(level) << "System " << this << " {" << std::endl
        << indent(level + 1) << "tissus: [" << std::endl;
    for (const auto& cloth : cloths) {
        cloth->display(out, level + 2);
        out << std::endl;
        massCount += cloth->getMassCount();
        springCount += cloth->getSpringCount();
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
