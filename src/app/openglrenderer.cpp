#include "include/openglrenderer.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/system.h"
#include "include/vector3d.h"


OpenGLRenderer::OpenGLRenderer():
    camera(),
    active(false),
    vbo(QOpenGLBuffer::VertexBuffer),
    ebo(QOpenGLBuffer::IndexBuffer),
    vao()
{
    reset();
}

void OpenGLRenderer::init() {
    // Set up the rendering context
    initializeOpenGLFunctions();

    // Backface culling and z buffer
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Create shader
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vert.glsl");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/frag.glsl");
    program.link();
    program.bind();

    // Store attribute and uniforms location for reuse later (cleaner than strings)
    vertexLocation = program.attributeLocation("vertex");
    colorLocation = program.uniformLocation("color");
    projectionViewMatrixLocation = program.uniformLocation("pv_matrix");
    modelMatrixLocation = program.uniformLocation("m_matrix");

    // Create geometry for testing
    createCube();

    // Create VAO
    vao.create();
    vao.bind();

    // VBO
    vbo.create();
    vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo.bind();
    vbo.allocate(vertices.constData(), 3 * vertices.size() * sizeof(GLfloat));

    program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3);
    program.enableAttributeArray(vertexLocation);

    ebo.create();
    ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo.bind();
    ebo.allocate(indicies.constData(), indicies.size() * sizeof(GLushort));

    // Clean up after initializing
    // RELEASE THE VAO FIRST!!!
    vao.release();
    vbo.release();
    ebo.release();
    program.release();

    // Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Normal mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGLRenderer::resize(int width, int height) {
    // Avoid division by 0 problems
    if (height == 0) {
        height = 1;
    }

    // Update projection matrix for new size
    const double ratio((double)width / (double)height);
    camera.setProjection(60.0, ratio, 0.001, 1000);

    glViewport(0, 0, width, height);
}

void OpenGLRenderer::clear() {
    // Clear previous frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::reset() {
    camera.setRotation(0, 0, 1, 0);
    camera.setPosition(0, 0, -5);
    camera.setMode(Camera::Gimbal);
}

void OpenGLRenderer::beginFrame() {
    if (active) {
        return;
    }
    program.bind();
    vao.bind();
    program.setUniformValue(projectionViewMatrixLocation, camera.getMatrix());
    active = true;
}

void OpenGLRenderer::endFrame() {
    vao.release();
    program.release();
    active = false;
    ++frameCount;
}

void OpenGLRenderer::deinit() {
    vao.destroy();
    vbo.destroy();
}

void OpenGLRenderer::update(const InputManager& inputs, double dt) {
    QVector3D move;
    // Minecraft-like movement
    QVector3D flatForward(QVector3D::crossProduct(camera.right(), Camera::LocalUp));
    if (inputs.isKeyPressed(Qt::Key_W)) {
        move += flatForward;
    }
    if (inputs.isKeyPressed(Qt::Key_S)) {
        move -= flatForward;
    }
    if (inputs.isKeyPressed(Qt::Key_A)) {
        move += camera.right();
    }
    if (inputs.isKeyPressed(Qt::Key_D)) {
        move -= camera.right();
    }
    if (inputs.isKeyPressed(Qt::Key_Shift)) {
        move += camera.up();
    }
    if (inputs.isKeyPressed(Qt::Key_Space)) {
        move -= camera.up();
    }

    // TODO: double comparaison
    // TODO: constants
    if (move.length() != 0.0) {
        move.normalize();
        camera.translate(move * 5.0 * dt);
    }

    // TODO: mouse movement
    double dpitch(0.0);
    double dyaw(0.0);
    if (inputs.isKeyPressed(Qt::Key_Up)) {
        dpitch += 1.0;
    }
    if (inputs.isKeyPressed(Qt::Key_Down)) {
        dpitch -= 1.0;
    }
    if (inputs.isKeyPressed(Qt::Key_Left)) {
        dyaw += 1.0;
    }
    if (inputs.isKeyPressed(Qt::Key_Right)) {
        dyaw -= 1.0;
    }

    // TODO: constants
    camera.rotate(dyaw * 50.0 * dt, Camera::LocalUp);
    camera.rotate(dpitch * 50.0 * dt, camera.right());
}

/* Drawing stuff! */

void OpenGLRenderer::draw(const Masse& masse) {
    // Set to correct position
    const Vector3D& pos(masse.getPos());
    QMatrix4x4 model;
    model.translate(pos.getX(), pos.getY(), pos.getZ());
    program.setUniformValue(modelMatrixLocation, model);

    // Set color
    program.setUniformValue(colorLocation, QVector4D(1.0, 0.0, 0.0, 1.0));

    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_SHORT, nullptr);
}

void OpenGLRenderer::draw(const Cloth& cloth) {
    cloth.drawParticles(*this);
}

void OpenGLRenderer::draw(const System& system) {
    system.drawContents(*this);

    // QMatrix4x4 model;
    // program.setUniformValue(modelMatrixLocation, model);
    // program.setUniformValue(colorLocation, QVector4D(1.0, 1.0, 1.0, 1.0));

    // glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_SHORT, nullptr);
}

void OpenGLRenderer::createCube() {
    int offset(vertices.size());

    vertices << QVector3D(-0.1, -0.1, -0.1) << QVector3D(-0.1, 0.1, -0.1) << QVector3D(0.1, 0.1, -0.1) << QVector3D(0.1, -0.1, -0.1)
        << QVector3D(0.1, -0.1, -0.1) << QVector3D(0.1, 0.1, -0.1) << QVector3D(0.1, 0.1, 0.1) << QVector3D(0.1, -0.1, 0.1)
        << QVector3D(0.1, -0.1, 0.1) << QVector3D(0.1, 0.1, 0.1) << QVector3D(-0.1, 0.1, 0.1) << QVector3D(-0.1, -0.1, 0.1)
        << QVector3D(-0.1, -0.1, 0.1) << QVector3D(-0.1, 0.1, 0.1) << QVector3D(-0.1, 0.1, -0.1) << QVector3D(-0.1, -0.1, -0.1)
        << QVector3D(-0.1, 0.1, -0.1) << QVector3D(-0.1, 0.1, 0.1) << QVector3D(0.1, 0.1, 0.1) << QVector3D(0.1, 0.1, -0.1)
        << QVector3D(-0.1, -0.1, -0.1) << QVector3D(0.1, -0.1, -0.1) << QVector3D(0.1, -0.1, 0.1) << QVector3D(-0.1, -0.1, 0.1);

    for (int i(offset); i < offset + 4 * 6; i += 4) {
        indicies << i << i + 1 << i + 2 << i << i + 2 << i + 3;
    }
}
