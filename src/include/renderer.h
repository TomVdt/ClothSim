#pragma once

class Masse;
class Cloth;
class System;

class Renderer {
public:
    Renderer() = default;
    virtual ~Renderer() {}
    Renderer(const Renderer&) = delete;

    virtual void draw(Masse&) = 0;      //TODO : mettre Masse comme une sous classe de drawable?
    virtual void draw(Cloth&) = 0;
    virtual void draw(System&) = 0;
};
