#pragma once

#include <GL/glew.h>


class VertexArray {
private:
    GLuint id;

public:
    VertexArray();

    explicit operator GLuint() const;

    void create();

    void bind();

    void release();

    void destroy();
};
