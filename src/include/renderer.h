#pragma once

class Masse;
class Spring;
class Cloth;
class System;

class Renderer {
public:
    Renderer() = default;
    virtual ~Renderer() {}

    /* Pas de copie */
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    /* Déplacable */
    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    virtual void draw(const Masse&) = 0;
    virtual void draw(const Spring&) = 0;
    virtual void draw(const Cloth&) = 0;
    virtual void draw(const System&) = 0;
};
