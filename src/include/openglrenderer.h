#include "include/renderer.h"
#include "include/camera.h"
#include "include/input.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>


class OpenGLRenderer: public Renderer, protected QOpenGLFunctions {
private:
    Camera camera;
    bool active;

    /* OpenGL */
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;
    QOpenGLVertexArrayObject vao;

    /* Accessors for shader */
    GLuint vertexLocation;
    GLuint colorLocation;
    GLuint projectionViewMatrixLocation;
    GLuint modelMatrixLocation;

    /* Geometry */
    QVector<QVector3D> vertices;
    QVector<GLushort> indicies;

    size_t frameCount;

    void createCube();

public:
    OpenGLRenderer();

    /* Pas de copie de Renderer */

    OpenGLRenderer(const Renderer&) = delete;
    OpenGLRenderer& operator=(const Renderer&) = delete;

    /* Renderer déplacable */

    OpenGLRenderer(OpenGLRenderer&&) = default;
    OpenGLRenderer& operator=(OpenGLRenderer&&) = default;

    virtual ~OpenGLRenderer() = default;

    void init();

    void resize(int, int);

    void clear();

    void reset();

    void beginFrame();

    void endFrame();

    void deinit();

    void update(const InputManager& inputs, double dt);

    virtual void draw(const Masse&);
    virtual void draw(const Cloth&);
    virtual void draw(const System&);
};