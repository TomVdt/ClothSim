#include "include/tissu.h"
#include <iostream>



Tissu::Tissu(const ManyMass& init_mass)
: massList(init_mass),
  springList() 
{}


Tissu::~Tissu() {
    for(auto spring:springList) {
        delete spring;
    }
}


void Tissu::connect(size_t m1, size_t m2, double k, double l0) {
    const size_t taille(massList.size());
    if (m1 < taille and m2 < taille) {
        Spring* s(new Spring(k, l0, massList[m1], massList[m2]));
        springList.push_back(s);
    } else {
        std::cerr << "y a pas autant de masses dans le tissu je tiens à mon cpu" << std::endl;
    }
}



bool Tissu::check() const {
    for(auto spring:springList) {
        if (not spring->valid()) return false;
        for(auto mass:massList) {
            if( mass->springConnected(spring) != spring->massConnected(mass) ) {
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
    for(auto mass:massList) {
        mass->updateForce();
    }
}


void Tissu::evolve(Integrator* integratator, double dt) {
    for(auto mass:massList) {
        integratator->integrate(mass, dt);
    }
}
