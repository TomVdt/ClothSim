#include <cmath>
#include <sstream>

#include "openglwidget.h"


OpenGLTest::OpenGLTest(QWidget* parent):
    QOpenGLWidget(parent),
    ebo(QOpenGLBuffer::IndexBuffer),
    vertexBuffer(QOpenGLBuffer::VertexBuffer),
    colorBuffer(QOpenGLBuffer::VertexBuffer),
    texBuffer(QOpenGLBuffer::VertexBuffer)
{
    setWindowTitle("Cloth Sim - OpenGL testing");
}


OpenGLTest::~OpenGLTest() {
    makeCurrent();

    // pointers to delete
    delete texture;
}

void OpenGLTest::initializeGL() {
    // Set up the rendering context
    initializeOpenGLFunctions();

    // Backface culling and z buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Create shader
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vert.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/frag.glsl");
    shaderProgram.link();

    // OpenGL "accessors"
    vertexLocation = shaderProgram.attributeLocation("vertex");
    colorLocation = shaderProgram.attributeLocation("color");
    texLocation = shaderProgram.attributeLocation("tex_coord");
    pvMatrixLocation = shaderProgram.uniformLocation("pv_matrix");
    mMatrixLocation = shaderProgram.uniformLocation("m_matrix");
    timeLocation = shaderProgram.uniformLocation("time");

    // Load texture
    texture = new QOpenGLTexture(QImage(":/chappi.png").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Create geometry
    // loadObj(":/banana.obj");
    createCube();

    shaderProgram.bind();

    // Create vao & link vbos
    vao.create();
    vao.bind();

    // Verticies
    vertexBuffer.create();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vertexBuffer.bind();
    vertexBuffer.allocate(vertices.constData(), 3 * vertices.size() * sizeof(GLfloat));

    shaderProgram.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3);
    shaderProgram.enableAttributeArray(vertexLocation);

    // Indicies (allow for reusing of verticies)
    ebo.create();
    ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo.bind();
    ebo.allocate(indicies.constData(), indicies.size() * sizeof(GLuint));

    // Per vertex color
    colorBuffer.create();
    colorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    colorBuffer.bind();
    colorBuffer.allocate(colors.constData(), 3 * colors.size() * sizeof(GLfloat));

    shaderProgram.setAttributeBuffer(colorLocation, GL_FLOAT, 0, 3);
    shaderProgram.enableAttributeArray(colorLocation);

    // Per vertex texture coord
    texBuffer.create();
    texBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    texBuffer.bind();
    texBuffer.allocate(texCoords.constData(), 3 * texCoords.size() * sizeof(GLfloat));

    shaderProgram.setAttributeBuffer(texLocation, GL_FLOAT, 0, 2);
    shaderProgram.enableAttributeArray(texLocation);

    // Clean up after initializing
    vao.release();
    vertexBuffer.release();
    ebo.release();
    colorBuffer.release();
    texBuffer.release();
    shaderProgram.release();

    // Wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Normal mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGLTest::resizeGL(int width, int height) {
    // Avoid division by 0 problems
    if (height == 0) {
        height = 1;
    }

    // Update projection matrix for new size
    projection.setToIdentity();
    projection.perspective(60.0, (double)width / (double)height, 0.001, 1000);

    // Orthographic works!
    // double w(5.0);
    // double h((double) height / (double) width * w);
    // projection.ortho(-w, w, -h, h, 0.001, 1000);

    glViewport(0, 0, width, height);
    update();
}

void OpenGLTest::paintGL() {
    // Clear previous frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // R O T A T E
    // TODO: better time management
    time += 0.166666;
    QMatrix4x4 model;
    QMatrix4x4 view;
    view.setToIdentity();
    view.translate(0.0, 0.0, -7.0);
    model.setToIdentity();
    model.rotate(time * 2, 1, 0, 0);
    model.rotate(time * 3, 0, 1, 0);
    model.rotate(time * 5, 0, 0, 1);

    // Change vertex position yes!
    // vertices[0] = QVector3D(sin(time / 10), cos(time / 10), -1.0);
    // for (auto& v : vertices) {
    //     // the factory must grow
    //     v *= 1.001;
    // }
    // vertexBuffer.bind();
    // vertexBuffer.write(0, vertices.constData(), 3 * vertices.size() * sizeof(GLfloat));
    // vertexBuffer.release();
    // for (auto& c : colors) {
    //     c = QVector3D((sin(time) + 2) / 3, (sin(2 * time) + 2) / 3, 0);
    // }
    // colorBuffer.bind();
    // colorBuffer.write(0, colors.constData(), 3 * colors.size() * sizeof(GLfloat));
    // colorBuffer.release();

    // Activate shader
    shaderProgram.bind();

    // Set uniforms
    shaderProgram.setUniformValue(pvMatrixLocation, projection * view);
    shaderProgram.setUniformValue(mMatrixLocation, model);
    shaderProgram.setUniformValue(timeLocation, (GLfloat)time);

    // Activate texture
    texture->bind();

    // Draw said arrays
    vao.bind();
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_SHORT, nullptr);
    vao.release();

    // Deactivate texture
    texture->release();

    // Deactivate shader
    shaderProgram.release();

    // Schedule a new draw
    update();
}

void OpenGLTest::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    }
}

void OpenGLTest::createCube() {
    // vertices << QVector3D(-1, -1, 0) << QVector3D(-1, 1, 0) << QVector3D(1, 1, 0) << QVector3D(1, -1, 0);
    // indicies << 0 << 1 << 2 << 0 << 2 << 3;
    // colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0);
    
    int offset(vertices.size());

    vertices << QVector3D(-1, -1, -1) << QVector3D(-1, 1, -1) << QVector3D(1, 1, -1) << QVector3D(1, -1, -1)
        << QVector3D(1, -1, -1) << QVector3D(1, 1, -1) << QVector3D(1, 1, 1) << QVector3D(1, -1, 1)
        << QVector3D(1, -1, 1) << QVector3D(1, 1, 1) << QVector3D(-1, 1, 1) << QVector3D(-1, -1, 1)
        << QVector3D(-1, -1, 1) << QVector3D(-1, 1, 1) << QVector3D(-1, 1, -1) << QVector3D(-1, -1, -1)
        << QVector3D(-1, 1, -1) << QVector3D(-1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, -1)
        << QVector3D(-1, -1, -1) << QVector3D(1, -1, -1) << QVector3D(1, -1, 1) << QVector3D(-1, -1, 1);
    
    for (int i(offset); i < offset + 4 * 6; i += 4) {
        indicies << i << i + 1 << i + 2 << i << i + 2 << i + 3;
    }

    colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
        << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
        << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1)
        << QVector3D(1, 1, 0) << QVector3D(1, 1, 0) << QVector3D(1, 1, 0) << QVector3D(1, 1, 0)
        << QVector3D(1, 0, 1) << QVector3D(1, 0, 1) << QVector3D(1, 0, 1) << QVector3D(1, 0, 1)
        << QVector3D(0, 1, 1) << QVector3D(0, 1, 1) << QVector3D(0, 1, 1) << QVector3D(0, 1, 1);
    texCoords << QVector2D(0, 0) << QVector2D(0, 1) << QVector2D(1, 1) << QVector2D(1, 0)
        << QVector2D(0, 0) << QVector2D(0, 1) << QVector2D(1, 1) << QVector2D(1, 0)
        << QVector2D(0, 0) << QVector2D(0, 1) << QVector2D(1, 1) << QVector2D(1, 0)
        << QVector2D(0, 0) << QVector2D(0, 1) << QVector2D(1, 1) << QVector2D(1, 0)
        << QVector2D(0, 0) << QVector2D(0, 1) << QVector2D(1, 1) << QVector2D(1, 0)
        << QVector2D(0, 0) << QVector2D(0, 1) << QVector2D(1, 1) << QVector2D(1, 0);
}

// Stolen from OneLoneCoder
// https://www.github.com/onelonecoder
// https://www.onelonecoder.com
// https://www.youtube.com/javidx9
// https://github.com/OneLoneCoder/videos/blob/master/LICENSE
bool OpenGLTest::loadObj(QString path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        return false;

    int offset(vertices.size());

    while (!f.atEnd()) {
        char line[128];
        f.readLine(line, 128);

        std::basic_stringstream<char> s;
        s << line;

        char junk;

        if (line[0] == 'v') {
            if (line[1] != 't') {
                double x, y, z;
                s >> junk >> x >> y >> z;
                vertices << QVector3D(x, y, z);
                colors << QVector3D(0.8, 0.6, 0.3);
                texCoords << QVector2D(0, 0);
            }
        }

        if (line[0] == 'f') {
            int i, j, k;
            s >> junk >> i >> j >> k;
            indicies << (offset + i - 1) << (offset + j - 1) << (offset + k - 1);
        }
    }
    return true;
}
