#pragma once

#include <GL/glew.h>


class Buffer {
private:
    GLuint id;
    GLenum type;

public:
    enum BufferType {
        Vertex,
        Index
    };

    Buffer(BufferType bufferType);

    explicit operator GLuint() const;

    void create();

    void bind();

    void release();

    void allocate(const void* data, unsigned int size);

    void write(unsigned int offset, const void* data, unsigned int size);

    void destroy();
};
