#pragma once

class Mass;
class Spring;
class Cloth;
class System;
class Constraint;

class Renderer {
public:
    /**
     * Constructeur par défaut par défaut suffisant
    */
    Renderer() = default;

    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Renderer() {}

    /**
     * Pas de copie de `Renderer`, tous les supports de dessin sont spécifiques et nécessitent beaucoup de mémoire
    */
    Renderer(const Renderer&) = delete;

    /**
     * Pas de copie de `Renderer`, tous les supports de dessin sont spécifiques et nécessitent beaucoup de mémoire
    */
    Renderer& operator=(const Renderer&) = delete;

    /**
     * Possible de déplacer des supports de dessin
    */
    Renderer(Renderer&&) = default;

    /**
     * Possible de déplacer des supports de dessin
    */
    Renderer& operator=(Renderer&&) = default;

    /**
     * Dessine une masse
    */
    virtual void draw(const Mass&) = 0;

    /**
     * Dessine un ressort
    */
    virtual void draw(const Spring&) = 0;

    /**
     * Dessine un tissu
    */
    virtual void draw(const Cloth&) = 0;

    /**
     * Dessine un système
    */
    virtual void draw(const System&) = 0;

    /**
     * Dessine une contrainte
    */
    virtual void draw(const Constraint&) = 0;
};
