#include "include/util.h"

std::ostream& operator<<(std::ostream& out, const indent& ind) {
    out << std::setw(ind.getLevel() * 2) << "";
    return out;
}
