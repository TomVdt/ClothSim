#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <string>

class ShaderProgram {
private:
    /**
     * Identifiant OpenGL du programme
    */
    GLuint id;

    /**
     * Identifiant OpenGL du vertex shader
    */
    GLuint vertex;

    /**
     * Identifiant OpenGL du fragment shader
    */
    GLuint fragment;

    /**
     * Vérifie les erreurs potentielles de compilation
    */
    bool checkCompileErrors(GLuint id);

    /**
     * Vérifie les erreurs potentielles de linking
    */
    bool checkLinkErrors(GLuint id);

    /**
     * Compile un shader
    */
    GLuint compileShader(const char* source, GLenum type);

    /**
     * Finalise les programme
    */
    GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader);

    /**
     * Lire le code source d'un shader depuis un fichier
    */
    std::string readSourceCode(const char* path);

public:
    /**
     * Types de shader supportés par ce programme
    */
    enum ShaderType {
        Vertex, Fragment
    };

    /**
     * Crée un shader vide, à initialiser plus tard
    */
    ShaderProgram();

    /**
     * Créer un shader complet
    */
    ShaderProgram(const char* vertexPath, const char* fragmentPath);

    /**
     * Permet la conversion implicite entre le program et son identifiant OpenGL
    */
    explicit operator GLuint() const;

    /**
     * Identifiant OpenGL
    */
    GLuint getProgramId() const;

    /**
     * Rajoute un shader au programme
    */
    void addShader(const char* path, ShaderType type);

    /**
     * Finalise le programme
    */
    void link();

    /**
     * Activer le shader
    */
    void bind();

    /**
     * Desactiver le shader
    */
    void release();

    /**
     * Détruit l'objet OpenGL associé au shader
    */
    void destroy();

    /**
     * Identifiant OpenGL d'un attribut
    */
    GLuint attributeLocation(const char* name);

    /**
     * Définit l'utilisation d'un attribut
    */
    void setAttributeBuffer(GLuint location, GLenum type, int offset, int tupleSize);

    /**
     * Active un attribut
    */
    void enableAttributeArray(GLuint location);

    /**
     * Désactive un attribut
    */
    void disableAttributeArray(GLuint location);

    /**
     * Identifiant OpenGL d'un uniform
    */
    GLuint uniformLocation(const char* name);

    /**
     * Écrit une `mat4x4` dans un uniform donné
    */
    void setUniformValue(GLuint location, const glm::mat4x4& mat);

    /**
     * Écrit un `vec4` dans un uniform donné
    */
    void setUniformValue(GLuint location, const glm::vec4& vec);
};
