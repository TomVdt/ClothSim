#include "include/renderer.h"
#include "include/camera.h"
#include "include/shaderprogram.h"
#include "include/vertexarray.h"
#include "include/buffer.h"

#include <GL/glew.h>

class Vector3D;

class OpenGLRenderer: public Renderer {
private:
    /* OpenGL */
    ShaderProgram program;
    
    /* Buffers */
    Buffer vbo;
    Buffer ebo;
    VertexArray vao;

    /* Accessors for shader */
    GLuint vertexLocation;
    GLuint colorLocation;
    GLuint projectionViewMatrixLocation;
    GLuint modelMatrixLocation;

    int offsetLine;
    int offsetCube;
    int offsetSphere;

    int indexLine;
    int indexCube;
    int indexSphere;

    Camera camera;

    constexpr static double cameraMoveSpeed = 15.0;
    constexpr static double cameraRotateSpeed = 0.005;

    glm::vec4 massColor;
    float massScale;
    bool drawMasses;
    bool drawSprings;
    int frameCount;

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

    void update(double dt);

    const glm::vec3& getPosition() const { return camera.getPosition(); }

    glm::vec3 getRotation() const { return glm::vec3(camera.getPitch(), camera.getYaw(), camera.getRoll()); }

    virtual void draw(const Masse&) override;
    
    virtual void draw(const Spring&) override;
    
    virtual void draw(const Cloth&) override;
    
    virtual void draw(const System&) override;

    void drawControls();

    void drawLine(const Vector3D& pos1, const Vector3D& pos2, const glm::vec4& color = glm::vec4(1.0));
    
    void drawCube(const Vector3D& pos, const Vector3D& scale, const glm::vec4& color = glm::vec4(1.0));

    void drawSphere(const Vector3D& pos, const Vector3D& scale, const glm::vec4& color = glm::vec4(1.0));

    void drawAxis();
};
