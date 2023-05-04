#include "include/renderer.h"
#include "include/camera.h"
#include "include/shaderprogram.h"
#include "include/vertexarray.h"
#include "include/buffer.h"
#include "include/framebuffer.h"

#include <GL/glew.h>


class OpenGLRenderer: public Renderer {
private:
    Camera camera;

    /* OpenGL */
    ShaderProgram program;
    
    /* Buffers */
    Buffer vbo;
    Buffer ebo;
    VertexArray vao;
    // FrameBuffer fbo;

    /* Accessors for shader */
    GLint vertexLocation;
    GLuint colorLocation;
    GLuint projectionViewMatrixLocation;
    GLuint modelMatrixLocation;

    void drawAxis();

public:
    // TODO: not this lmao
    static float shapeColor[3];
    static float scale;
    static int test;
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

    void update(double dt);

    GLuint getFrameTexture();

    const glm::vec3& getPosition() const { return camera.getPosition(); }

    glm::vec3 getRotation() const { return glm::vec3(camera.getPitch(), camera.getYaw(), camera.getRoll()); }

    virtual void draw(const Masse&) override;
    virtual void draw(const Spring&) override;
    virtual void draw(const Cloth&) override;
    virtual void draw(const System&) override;
};
