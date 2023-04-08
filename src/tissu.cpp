#include "include/tissu.h"
#include "include/spring.h"
#include "include/masse.h"
#include "include/exceptions.h"
#include "include/integrator.h"

#include <iostream>


Tissu::Tissu(const ManyMass& init_mass)
: massList(init_mass),
  springList() 
{}

Tissu::~Tissu () {}

unsigned int Tissu::getMassCount() const {
    return massList.size();
}

unsigned int Tissu::getSpringCount() const {
    return springList.size();
}

void Tissu::connect(size_t m1, size_t m2, double k, double l0) {
    const size_t taille(massList.size());
    if (m1 < taille and m2 < taille) {
        Spring* s(new Spring(k, l0, *massList[m1], *massList[m2]));
        massList[m1]->connectSpring(*s);
        massList[m2]->connectSpring(*s);
        springList.push_back(s);
    } else {
        throw OutOfBoundsException("y a pas autant de masses dans le tissu je tiens à mon cpu");
    }class Tissu;

}

bool Tissu::check() const {
    for(auto& spring:springList) {
        if (not spring->valid()) return false;
        for(auto mass : massList) {
            if( mass->springConnected(*spring) != spring->massConnected(*mass) ) {
                return false;
            }
            /* le test d'égalité sur des booléens sert de xor afin de vérifier que 
            soit il ne sont pas connectés ni l'un ni l'autre 
            soit ils sont tous les deux connectés entre eux */
        }
    }

    return true;
}


void Tissu::updateForce() {
    for(auto& mass : massList) {
        mass->updateForce();
    }
}


void Tissu::evolve(const Integrator& integratator, double dt = CONSTANTS::PHYSICS_DT) {
    for(auto& mass : massList) {
        integratator.integrate(*mass, dt);
    }
}

void Tissu::display(std::ostream& out) const {
    out << "Cloth " << this << " {" << std::endl
        << "  masses (" << massList.size() << "): [" << std::endl;
    
    // Aucune masse ne peut etre un nullptr
    for (const auto& mass : massList) {
        out << "    " << *mass << std::endl;
    }
    out << "  ]," << std::endl
        << "  ressorts (" << springList.size() << "): [" << std::endl;
    
    // Aucun spring ne peut etre un nullptr
    for (const auto& spring : springList) {
        out << "    " << *spring << std::endl;
    }
    out << "  ]" << std::endl << "}" << std::endl;
}

std::ostream& operator<<(std::ostream out, const Tissu& tissu) {
    tissu.display(out);
    return out;
}
