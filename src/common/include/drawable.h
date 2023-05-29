#pragma once

class Renderer;

class Drawable {
public:
    /**
     * Destructeur par défaut virtuel pour l'héritage
    */
    virtual ~Drawable() = default;

    /**
     * Fonction à surcharger pour afficher les objets concernés
    */
    virtual void draw(Renderer& dest) = 0;
};