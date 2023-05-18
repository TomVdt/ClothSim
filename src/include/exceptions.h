#pragma once
#include <stdexcept>
#include <string>

class Exception: public std::runtime_error {
public:
    Exception(const std::string& message, const std::string& file, int line) noexcept:
        std::runtime_error("Error occured in file " + file + ", line " + std::to_string(line) + ": " + message) {}
};

class ZeroDivisionError: public Exception {
public:
    using Exception::Exception;
};

class IndexError: public Exception {
public:
    using Exception::Exception;
};

class ValueError: public Exception {
public:
    using Exception::Exception;
};

class GLFWError: public Exception {
public:
    using Exception::Exception;
};

class ConnectionError: public Exception {
public:
    using Exception::Exception;
};

class UnreachableError: public Exception {
public:
    using Exception::Exception;
};

#define ERROR(type, msg) throw type(msg, __FILE__, __LINE__)

