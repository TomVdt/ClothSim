#pragma once

#include <GL/glew.h>

class VertexArray {
private:
    /**
     * Identifiant OpenGL de l'array
    */
    GLuint id;

public:
    /**
     * Constructeur
     * Le vertex array doit être créé plus tard
    */
    VertexArray();

    /**
     * Permet la conversion implicite entre le program et son identifiant OpenGL
    */
    explicit operator GLuint() const;

    /**
     * Crée l'objet OpenGL associé
    */
    void create();

    /**
     * Activer le vertex array
    */
    void bind();

    /**
     * Desactiver le vertex array
    */
    void release();

    /**
     * Détruit l'objet OpenGL associé au vertex array
    */
    void destroy();
};
