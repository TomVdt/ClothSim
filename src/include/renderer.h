#pragma once

class Masse;
class Cloth;
class System;

class Renderer {
public:
    virtual ~Renderer() {}
    Renderer(const Renderer&) = delete;

    virtual void draw(Masse&) = 0;
    virtual void draw(Cloth&) = 0;
    virtual void draw(System&) = 0;
};
