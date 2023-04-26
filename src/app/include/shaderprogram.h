#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <string>

class ShaderProgram {
private:
    // the program ID
    GLuint id;
    GLuint vertex;
    GLuint fragment;

    bool checkCompileErrors(GLuint id);

    bool checkLinkErrors(GLuint id);

    GLuint compileShader(const char* source, GLenum type);

    GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader);

    std::string readSourceCode(const char* path);

public:
    enum ShaderType {
        Vertex, Fragment
    };

    /* Create an empty program, initialize later */
    ShaderProgram();

    /* Create a complete shader program */
    ShaderProgram(const char* vertexPath, const char* fragmentPath);

    /* Implicit conversions between shader and underlying OpenGL object */
    explicit operator GLuint() const;

    GLuint getProgramId() const;

    void addShader(const char* path, ShaderType type);

    void link();

    void bind();

    void release();

    GLuint attributeLocation(const char* name);

    void setAttributeBuffer(GLuint location, GLenum type, int offset, int tupleSize);

    void enableAttributeArray(GLuint location);

    void disableAttributeArray(GLuint location);

    GLuint uniformLocation(const char* name);

    /* Set uniform value for Mat4x4 */
    void setUniformValue(GLuint location, const glm::mat4x4& mat);
    
    /* Set uniform value for vec4 */
    void setUniformValue(GLuint location, const glm::vec4& mat);
};
