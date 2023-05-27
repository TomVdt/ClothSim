#pragma once
#include "include/renderer.h"

#include <iostream>


class TextRenderer: public Renderer {
private:
    std::ostream& out;

public:
    TextRenderer(std::ostream& out = std::cout): out(out) {}

    TextRenderer(const TextRenderer&) = delete;

    virtual void draw(const Masse& mass);
    virtual void draw(const Spring& mass);
    virtual void draw(const Cloth& cloth);
    virtual void draw(const System& system);
    virtual void draw(const Constraint& constraint);
};