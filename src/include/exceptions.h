#pragma once
#include <stdexcept>

class BaseException: public std::runtime_error {
public:
    BaseException(char const* const message) throw(): std::runtime_error(message) {}
};

class NullVectorNormalisationException: public BaseException {
public:
    NullVectorNormalisationException(char const* const message) throw(): BaseException(message) {}
};

class OutOfBoundsException: public BaseException {
public:
    OutOfBoundsException(char const* const message) throw(): BaseException(message) {}
};

class InvalidValueException: public BaseException {
public:
    InvalidValueException(char const* const message) throw(): BaseException(message) {}
};

class PerpetualMotionException: public InvalidValueException {
public:
    PerpetualMotionException(char const* const message) throw(): InvalidValueException(message) {}
};
