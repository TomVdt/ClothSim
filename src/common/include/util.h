#pragma once

#include <iostream>

/**
 * Classe simple pour indenter une sortie dans cout
 * Avec: `std::cout << indent(...) << ...;` 
 * Plus élégant que de faire `std::cout << "  " << std::setw(...) << ...;`
*/
class indent {
private:
    /**
     * Niveau d'indentation correspondant
    */
    size_t level;

public:
    /**
     * Constructeur prenant le niveau d'indentation
    */
    indent(size_t level) : level(level) {}

    /**
     * Retourne le niveau d'indentation de cette instance
    */
    size_t getLevel() const { return level; }
};

/**
 * Surcharge de l'opérateur << pour régler une indentation dans un flot
*/
std::ostream& operator<<(std::ostream& out, const indent& ind);

/**
 * Pour enlever les warnings "unused parameter"
*/
#define UNUSED(x) (void)(x)