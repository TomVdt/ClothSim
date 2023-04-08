#pragma once

class Renderer;

class Drawable {
public:
    Drawable() {}

    virtual void draw(Renderer& dest) = 0;
};