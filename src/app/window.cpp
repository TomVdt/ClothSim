#include "include/window.h"
#include "include/cloth.h"
#include "include/masse.h"
#include "include/vector3d.h"
#include "include/constants.h"


Window::Window(): QOpenGLWindow(), renderer(), system(), physicsIntegrator(std::make_unique<EulerCromerIntegrator>()) {
    setTitle("Cloth Simulation");
    // TODO: init system
    std::vector<Masse> masses;
    
    // Create particles
    constexpr int count(10);
    for (int y(0); y < count; ++y) {
        for (int x(0); x < count; ++x) {
            masses.push_back(Masse(1.0, 0.3, Vector3D(4 * x, -4 * y, 0), Vector3D(0, 0, 0), y == 0));
        }
    }
    
    std::unique_ptr<Cloth> cloth = std::make_unique<Cloth>(masses);

    // Connect particles
    for (int y(0); y < count; ++y) {
        for (int x(0); x < count; ++x) {
            const int i(y * count + x);
            // Up
            if (i - count >= 0) {
                cloth->connect(i, i - count, 100.0, 4.0);
            }
            // Left
            if (x > 0) {
                cloth->connect(i, i - 1, 100.0, 4.0);
            }
        }
    }

    system.addCloth(std::move(cloth));

    timer.start();
}

Window::~Window() {
    makeCurrent();
    renderer.deinit();
}

void Window::initializeGL() {
    // Auto-redraw at correct rate
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    renderer.init();
}

void Window::resizeGL(int width, int height) {
    renderer.resize(width, height);
}

void Window::paintGL() {
    renderer.beginFrame();
    renderer.clear();
    system.draw(renderer);
    renderer.endFrame();
}

void Window::keyPressEvent(QKeyEvent* event) {
    inputs.handleKeyPress(event);
}

void Window::keyReleaseEvent(QKeyEvent* event) {
    inputs.handleKeyRelease(event);
}

void Window::update() {

    // Milliseconds since last update
    const double dt((double)timer.restart() / 1000.0);

    // Check inputs
    renderer.update(inputs, dt);

    // Step physics with constant time (deterministic)
    system.step(*physicsIntegrator, CONSTANTS::PHYSICS_DT);

    // Schedule a redraw
    QOpenGLWindow::update();
}
