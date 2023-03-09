#pragma once
#include <iostream>
#include <iomanip>


// TODO: trouver une meilleure manière de faire les tests
// TODO: ne pas supposer que == fonctionne?
// TODO: une seule evalutation de l'expression à tester (effets de bord)
#define SHOW_TEST(n, c, v) (\
    std::cout << std::setw(26) << std::left << n << ": "\
              << ((c) == (v) ? "\x1B[32mPASS\033[0m" : "\x1B[31mFAIL\033[0m") << " "\
              << #c << " => " << (c) << ", expected " << v << "\n"\
)
