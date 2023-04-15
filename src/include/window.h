#pragma once
#include "include/openglrenderer.h"
#include "include/system.h"
#include "include/integrator.h"
#include "include/input.h"

#include <memory>
#include <QOpenGLWindow>
#include <QElapsedTimer>
#include <QKeyEvent>


class Window : public QOpenGLWindow {
    // Allow the use of signals
    // in our case, automatically refresh on vsync
    Q_OBJECT

private:
    OpenGLRenderer renderer;
    System system;
    std::unique_ptr<Integrator> physicsIntegrator;
    QElapsedTimer timer;
    InputManager inputs;

public:
    Window();
    virtual ~Window();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

protected slots:
    void update();
};
