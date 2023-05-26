#pragma once
#include "include/constants.h"

#include <iostream>
#include <cassert>
#include <cmath>

// Egalites génériques
template<typename T1, typename T2>
bool EQ(T1 a, T2 b) {
    return a == b;
}

// Spécialisation pour les doubles
template<>
bool EQ<double, double>(double a, double b) {
    return std::abs(a - b) < CONSTANTS::EPSILON;
}

#define assertmsg(msg, val, expected) \
    do {\
        assert(((void)msg, (EQ(val, expected))));\
        std::cout << msg << ": " << "\x1B[32mPASS\033[0m\n";\
    } while (0)

#define assertexception(msg, expr, exception) \
    try {\
        expr;\
        assert(((void)msg, (void)"expected "#exception, false));\
    } catch (exception& e) {\
        std::cout << msg << ": " << "\x1B[32mPASS\033[0m\n";\
    }\
