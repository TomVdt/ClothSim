#include "include/vertexarray.h"


VertexArray::VertexArray() : id(0) {}

VertexArray::operator GLuint() const {
    return id;
}

void VertexArray::create() {
    glGenVertexArrays(1, &id);
}

void VertexArray::bind() {
    glBindVertexArray(id);
}

void VertexArray::release() {
    glBindVertexArray(0);
}

void VertexArray::destroy() {
    glDeleteVertexArrays(1, &id);
}
