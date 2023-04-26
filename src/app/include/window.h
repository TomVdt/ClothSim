#pragma once
#include "include/openglrenderer.h"
#include "include/system.h"
#include "include/integrator.h"

#include <memory>


class Window {
private:
    OpenGLRenderer renderer;
    System system;
    std::unique_ptr<Integrator> physicsIntegrator;

    GLFWwindow* window;

    bool paused;

    // Resizing window bookkeping
    static bool needsResize;

    void init();

    void initGLFW();

    void createWindow();

    void initOpenGL();

    void initImGui();

    void deinit();

    void update();

    void render();

public:
    Window();
    virtual ~Window();

    static void fbResizeCallback(GLFWwindow* window, int width, int height);

    void run();
};
