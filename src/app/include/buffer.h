#pragma once

#include <GL/glew.h>

class Buffer {
private:
    /**
     * Identifiant OpenGL du buffer
    */
    GLuint id;

    /**
     * Type OpenGL du buffer
    */
    GLenum type;

public:
    /**
     * Types de buffer supportés par cet objet
    */
    enum BufferType {
        Vertex,
        Index
    };

    /**
     * Initialise le type de buffer
    */
    Buffer(BufferType bufferType);

    /**
     * Permet la conversion implicite entre le program et son identifiant OpenGL
    */
    explicit operator GLuint() const;

    /**
     * Crée l'objet OpenGL associé au buffer
    */
    void create();

    /**
     * Active le buffer
    */
    void bind();

    /**
     * Desactive le buffer
    */
    void release();

    /**
     * Alloue de la mémoire pour le buffer
    */
    void allocate(const void* data, unsigned int size);

    /**
     * Écrit dans le buffer
    */
    void write(unsigned int offset, const void* data, unsigned int size);

    /**
     * Détruit l'objet OpenGL associé au buffer
    */
    void destroy();
};
