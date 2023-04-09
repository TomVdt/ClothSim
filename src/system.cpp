#include "include/system.h"
#include "include/cloth.h"
#include "include/renderer.h"
#include "include/exceptions.h"
#include "include/util.h"


void System::addCloth(std::unique_ptr<Cloth> cloth) {
    cloths.push_back(std::move(cloth));
}

// void System::createCloth()

void System::update(double dt) {
    for (auto& cloth : cloths) {
        cloth->updateForce();
        cloth->evolve(integrator, dt);
    }
}

void System::draw(Renderer& dest) {
    dest.draw(*this);
    // throw NoRendererException("No usable renderer was given");
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
