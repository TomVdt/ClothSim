#pragma once
#include "include/constants.h"

#include <iostream>
#include <cassert>
#include <cmath>

/**
 * Gestion des égalités génériques
*/
template<typename T1, typename T2>
bool EQ(T1 a, T2 b) {
    return a == b;
}

/**
 * Gestion des égalités entre double
*/
template<>
bool EQ<double, double>(double a, double b) {
    return std::abs(a - b) < CONSTANTS::EPSILON;
}

/**
 * Test générique comparant le résultat et la valeur attendue
 * Affiche un message et indique si le test est réussi
*/
#define assertmsg(msg, val, expected) \
    do {\
        assert(((void)msg, (EQ(val, expected))));\
        std::cout << msg << ": " << "\x1B[32mPASS\033[0m\n";\
    } while (0)

/**
 * Test pour les exceptions vérifie que la bonne exception est renvoyée
*/
#define assertexception(msg, expr, exception) \
    try {\
        expr;\
        assert(((void)msg, (void)"expected", (void)#exception, false));\
    } catch (exception& e) {\
        std::cout << msg << ": " << "\x1B[32mPASS\033[0m\n";\
    }\
