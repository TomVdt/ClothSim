#include "include/buffer.h"


Buffer::Buffer(BufferType bufferType) : id(0) {
    switch (bufferType) {
    case Vertex:
        type = GL_ARRAY_BUFFER;
        break;
    case Index:
        type = GL_ELEMENT_ARRAY_BUFFER;
    }
}

Buffer::operator GLuint() const {
    return id;
}

void Buffer::create() {
    glGenBuffers(1, &id);
}

void Buffer::bind() {
    glBindBuffer(type, id);
}

void Buffer::release() {
    glBindBuffer(type, 0);
}

void Buffer::allocate(const void* data, unsigned int size) {
    glBufferData(type, size, data, GL_DYNAMIC_DRAW);
}

void Buffer::write(unsigned int offset, const void* data, unsigned int size) {
    glBufferSubData(type, offset, size, data);
}

void Buffer::destroy() {
    glDeleteBuffers(1, &id);
}
