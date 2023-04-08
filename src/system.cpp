#include "include/system.h"
#include "include/tissu.h"
#include "include/renderer.h"
#include "include/exceptions.h"


System::~System() {}

void System::update(double dt = CONSTANTS::PHYSICS_DT) {
    for (auto& cloth : cloths) {
        cloth->updateForce();
        cloth->evolve(*integrator, dt);
    }
}

void System::draw(Renderer& dest) {
    dest.draw(*this);
    // throw NoRendererException("No usable renderer was given");
}

void System::display(std::ostream& out) const {
    out << "System " << this << " {" << std::endl
        << "  cloths: [" << std::endl;
    unsigned int massCount(0);
    unsigned int springCount(0);
    for (const auto& cloth : cloths) {
        out << cloth.get() << std::endl;
        massCount += cloth->getMassCount();
        springCount += cloth->getSpringCount();
    }
    out << "  ]," << std::endl
        << "  masses: " << massCount << "," << std::endl
        << "  ressorts: " << springCount << std::endl
        << "}" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const System& system) {
    system.display(out);
    return out;
}
