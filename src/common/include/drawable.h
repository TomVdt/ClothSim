#pragma once

class Renderer;

class Drawable {
public:
    /**
     * fonction à surcharger pour afficher les objets concernés
    */
    virtual void draw(Renderer& dest) = 0;
};