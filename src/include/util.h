#pragma once

#include <iostream>
#include <iomanip>

class indent {
private:
    size_t level;

public:
    indent(size_t level) : level(level) {}

    size_t getLevel() const { return level; }
};

std::ostream& operator<<(std::ostream& out, const indent& ind);
