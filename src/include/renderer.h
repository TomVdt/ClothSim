#pragma once

class Masse;
class Tissu;
class System;

class Renderer {
public:
    virtual ~Renderer() {}
    Renderer(const Renderer&) = delete;

    virtual void draw(Masse&) = 0;
    virtual void draw(Tissu&) = 0;
    virtual void draw(System&) = 0;
};
