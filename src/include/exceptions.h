#pragma once
#include <stdexcept>

class BaseException: public std::runtime_error {
public:
    BaseException(char const* const message) throw(): std::runtime_error(message) {}
};

class DivZeroException: public BaseException {
public:
    DivZeroException(char const* const message) throw(): BaseException(message) {}
};

class OutOfBoundsException: public BaseException {
public:
    OutOfBoundsException(char const* const message) throw(): BaseException(message) {}
};

class InvalidValueException: public BaseException {
public:
    InvalidValueException(char const* const message) throw(): BaseException(message) {}
};

class WindowException: public BaseException {
public:
    WindowException(char const* const message) throw(): BaseException(message) {}
};

