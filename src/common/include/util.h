#pragma once

#include <iostream>
#include <iomanip>

/**
 * Classe simple pour indenter une sortie dans cout
 * Plus élégant que de faire `std::cout << "  " << std::setw(...) << ...;`
 * Avec: `std::cout << indent(...) << ...;` 
*/
class indent {
private:
    size_t level;

public:
    indent(size_t level) : level(level) {}

    size_t getLevel() const { return level; }
};

std::ostream& operator<<(std::ostream& out, const indent& ind);

// Pour enlever les warnings "unused parameter"
#define UNUSED(x) (void)(x)

