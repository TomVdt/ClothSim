#pragma once

class Renderer;

class Drawable {
public:
    virtual ~Drawable() = default;

    /**
     * Fonction à surcharger pour afficher les objets concernés
    */
    virtual void draw(Renderer& dest) = 0;
};