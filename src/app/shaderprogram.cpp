#include "include/shaderprogram.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

// Based on
// https://learnopengl.com/Getting-started/Shaders

ShaderProgram::ShaderProgram() : id(0), vertex(0), fragment(0) {}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) : ShaderProgram() {
    // Create & compile shaders
    addShader(vertexPath, Vertex);
    addShader(fragmentPath, Fragment);

    link();
}

bool ShaderProgram::checkCompileErrors(GLuint id) {
    int code;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &code);
    if (not code) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "Failed to compile shader!\n" << infoLog << std::endl;
        return true;
    };
    return false;
}

bool ShaderProgram::checkLinkErrors(GLuint id) {
    int code;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &code);
    if (not code) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "Failed to link shader program!\n" << infoLog << std::endl;
        return true;
    }
    return false;
}

std::string ShaderProgram::readSourceCode(const char* path) {
    std::string code;
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        file.open(path);
        std::stringstream stream;
        // read file's buffer contents into streams
        stream << file.rdbuf();
        // close file handlers
        file.close();
        // convert stream into string
        code = stream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "Couldn't open source file " << path << std::endl;
    }
    return code;
}

GLuint ShaderProgram::compileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // print compile errors if any
    checkCompileErrors(shader);
    return shader;
}

GLuint ShaderProgram::linkShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // print linking errors if any
    checkLinkErrors(program);

    return program;
}

ShaderProgram::operator GLuint() const {
    return id;
}

GLuint ShaderProgram::getProgramId() const {
    return id;
}

void ShaderProgram::addShader(const char* path, ShaderType type) {
    std::string code = readSourceCode(path);
    switch (type) {
    case Vertex:
        vertex = compileShader(code.c_str(), GL_VERTEX_SHADER);
        break;
    case Fragment:
        fragment = compileShader(code.c_str(), GL_FRAGMENT_SHADER);
        break;
    }
}

void ShaderProgram::link() {
    // If shaders are invalid or uninitialised, should throw an error
    id = linkShaderProgram(vertex, fragment);

    // Clean up
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void ShaderProgram::bind() {
    glUseProgram(id);
}

void ShaderProgram::release() {
    glUseProgram(0);
}

GLuint ShaderProgram::attributeLocation(const char* name) {
    return glGetAttribLocation(id, name);
}

void ShaderProgram::setAttributeBuffer(GLuint location, GLenum type, int offset, int tupleSize) {
    glVertexAttribPointer(location, tupleSize, type, GL_FALSE, 0, reinterpret_cast<const void*>(offset));
}

void ShaderProgram::enableAttributeArray(GLuint location) {
    glEnableVertexAttribArray(location);
}

void ShaderProgram::disableAttributeArray(GLuint location) {
    glDisableVertexAttribArray(location);
}

GLuint ShaderProgram::uniformLocation(const char* name) {
    return glGetUniformLocation(id, name);
}

void ShaderProgram::setUniformValue(GLuint location, const glm::mat4x4& mat) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniformValue(GLuint location, const glm::vec4& vec) {
    glUniform4fv(location, 1, glm::value_ptr(vec));
}
