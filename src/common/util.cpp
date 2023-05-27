#include "include/util.h"

#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const indent& ind) {
    out << std::setw(ind.getLevel() * 2) << "";
    return out;
}
