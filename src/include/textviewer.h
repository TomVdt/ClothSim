#pragma once

#include "include/renderer.h"

#include <iostream>


class TextViewer: public Renderer {
private:
    std::ostream& out;

public:
    TextViewer(std::ostream& out = std::cout): out(out) {}

    TextViewer(const TextViewer&) = delete;

    virtual void draw(Masse& mass);
    virtual void draw(Cloth& cloth);
    virtual void draw(System& system);


};