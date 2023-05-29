#pragma once
#include <stdexcept>
#include <string>

/**
 * Exception standard comme super-classe
*/
class Exception: public std::runtime_error {
public:
    /**
     * Constructeur d'exceptions prenant un message, le nom du fichier où l'erreur s'est produite et la ligne correspondante
    */
    Exception(const std::string& message, const std::string& file, int line) noexcept:
        std::runtime_error("Error occured in file " + file + ", line " + std::to_string(line) + ": " + message) {}
};

/**
 * Erreur de division par zéro
*/
class ZeroDivisionError: public Exception {
public:
    using Exception::Exception;
};

/**
 * Erreur d'index erroné pour accéder à un élément d'une liste
*/
class IndexError: public Exception {
public:
    using Exception::Exception;
};

/**
 * Erreur sur la valeur fournie non-valide
*/
class ValueError: public Exception {
public:
    using Exception::Exception;
};

/**
 * Erreur dans une méthode de la bibliothèque GLFW pour OpenGL
*/
class GLFWError: public Exception {
public:
    using Exception::Exception;
};

/**
 * Erreur dans la connexion entre deux éléments
*/
class ConnectionError: public Exception {
public:
    using Exception::Exception;
};

/**
 * Erreur d'élément non-accessible
*/
class UnreachableError: public Exception {
public:
    using Exception::Exception;
};

/**
 * Définit la structure de base pour l'appel à des exceptions: ERROR(type d'erreur, message fourni)
 * Récupère automatiquement le nom du fichier et la ligne de l'erreur
*/
#define ERROR(type, msg) throw type(msg, __FILE__, __LINE__)

