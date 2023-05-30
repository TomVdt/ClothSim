#pragma once
#include "include/renderer.h"

#include <iostream>

class TextRenderer: public Renderer {
private:
    /**
     * Flot de sortie du support de dessin textuel
    */
    std::ostream& out;

public:
    /**
     * Constructeur prenant le flot de sortie
    */
    TextRenderer(std::ostream& out = std::cout): out(out) {}

    /**
     * Pas de copie de supports de dessin, pas vraiment de sens d'écrire 
     * sur le même fichier avec deux supports différents
    */
    TextRenderer(const TextRenderer&) = delete;

    /**
     * Pas de copie de supports de dessin, pas vraiment de sens d'écrire 
     * sur le même fichier avec deux supports différents
    */
    TextRenderer& operator=(const TextRenderer&) = delete;

    /**
     * Affiche une masse dans le flot
    */
    virtual void draw(const Mass& mass);
    
    /**
     * Affiche un ressort dans le flot
    */
    virtual void draw(const Spring& mass);
    
    /**
     * Affiche un tissu dans le flot
    */
    virtual void draw(const Cloth& cloth);
    
    /**
     * Affiche un système dans le flot
    */
    virtual void draw(const System& system);
    
    /**
     * Affiche une contrainte dans le flot
    */
    virtual void draw(const Constraint& constraint);
};