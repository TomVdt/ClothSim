#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>
#include <QKeyEvent>


class OpenGLTest : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    OpenGLTest(QWidget *parent);
    virtual ~OpenGLTest();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent* event) override;

    void createCube();

    bool loadObj(QString path);

private:
    QOpenGLShaderProgram shaderProgram;
    QMatrix4x4 projection;

    // Temporary testing data
    double time;

    GLuint vertexLocation;
    GLuint colorLocation;
    GLuint texLocation;
    GLuint pvMatrixLocation;
    GLuint mMatrixLocation;
    GLuint timeLocation;

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer ebo;
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer colorBuffer;
    QOpenGLBuffer texBuffer;
    QOpenGLTexture* texture;

    QVector<QVector3D> vertices;
    QVector<GLushort> indicies;
    QVector<QVector3D> colors;
    QVector<QVector2D> texCoords;
};