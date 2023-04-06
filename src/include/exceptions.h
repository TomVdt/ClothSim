#pragma once
#include <stdexcept>

class BaseException : public std::runtime_error {
public:
    BaseException(char const* const message) throw() : std::runtime_error(message) {}
};

class NullVectorNormalisationException : public BaseException {
public:
    NullVectorNormalisationException(char const* const message) throw() : BaseException(message) {}
};

class NoRendererException : public BaseException {
public:
    NoRendererException(char const* const message) throw() : BaseException(message) {}
};
