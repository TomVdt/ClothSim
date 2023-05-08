#include "include/window.h"
#include "include/cloth.h"
#include "include/masse.h"
#include "include/vector3d.h"
#include "include/constants.h"
#include "include/exceptions.h"
#include "include/chaincloth.h"
#include "include/rectcloth.h"
#include "include/diskcloth.h"
#include "include/compositecloth.h"
#include "include/constraint.h"

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

bool Window::needsResize(true);

Window::Window():
    renderer(),
    system(),
    physicsIntegrator(std::make_unique<EulerCromerIntegrator>()),
    window(nullptr),
    paused(true),
    deltaTime(CONSTANTS::PHYSICS_DT),
    iterationsPerFrame(1)
{
    Cloth* cloth1(new DiskCloth(
        1.0,
        Vector3D(),
        Vector3D(0.0, 100.0, 0.0),
        2.0,
        0.3,
        100.0
    ));

    Constraint* constraint1(new HookConstraint(
        Vector3D(),
        0.1
    ));
    /*
    Constraint* constraint2(new SineImpulsionConstraint(
        Vector3D(),
        0.1,
        0.0, 10.0,
        Vector3D(0, 0, 30),
        1.0,
        {
            cloth1
        }
    ));
    */
    system.addCloth(std::unique_ptr<Cloth>(cloth1));
    system.addConstraint(std::unique_ptr<Constraint>(constraint1));
    // system.addConstraint(std::unique_ptr<Constraint>(constraint2));

    /*
    Cloth* cloth2(new RectCloth(
        0.3125,
        Vector3D(3, 0, 0), Vector3D(0, 0, 3),
        Vector3D(),
        0.3,
        1.0,
        1.0,
        1.0
    ));

    Constraint* constraint3(new HookConstraint(
        Vector3D(),
        0.1
    ));

    Constraint* constraint4(new HookConstraint(
        Vector3D(0, 0, 3),
        0.1
    ));

    Constraint* constraint5(new SineImpulsionConstraint(
        Vector3D(3, 0, 0),
        0.5,
        0.0, 2.0,
        Vector3D(0, 30, 0),
        1.5,
        {
            cloth2
        }
    ));

    Constraint* constraint6(new SineImpulsionConstraint(
        Vector3D(3, 0, 3),
        0.5,
        0.0, 2.0,
        Vector3D(0, 30, 0),
        1.5,
        {
            cloth2
        }
    ));

    system.addCloth(std::unique_ptr<Cloth>(cloth2));
    system.addConstraint(std::unique_ptr<Constraint>(constraint3));
    system.addConstraint(std::unique_ptr<Constraint>(constraint4));
    system.addConstraint(std::unique_ptr<Constraint>(constraint5));
    system.addConstraint(std::unique_ptr<Constraint>(constraint6));
    */

    // Cloth* cloth3(new ChainCloth(
    //     1.0,
    //     0.3,
    //     1.0,
    //     1.0,
    //     {
    //         Vector3D(),
    //         Vector3D(1, 4, 1),
    //         Vector3D(2, 8, 2)
    //     }
    // ));

    // Constraint* constraint7(new HookConstraint(
    //     Vector3D(),
    //     0.1
    // ));

    // system.addCloth(std::unique_ptr<Cloth>(cloth3));
    // system.addConstraint(std::unique_ptr<Constraint>(constraint7));
}

// static void glfw_error_callback(int err, const char* description) {
//     std::cout << description << std::endl;
// }

void Window::init() {
    // Create window
    initGLFW();
    createWindow();

    // Set OpenGL context
    glfwMakeContextCurrent(window);

    // Enable vsync
    glfwSwapInterval(1);
    
    // Set resize callback
    glfwSetFramebufferSizeCallback(window, fbResizeCallback);

    // Actually start OpenGL
    initOpenGL();

    // Start ImGui
    initImGui();
}

void Window::initGLFW() {
    // glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        throw WindowException("Failed to initialise GLFW");
    }

    // Set GLSL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Window::createWindow() {
    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, "Cloth Simulation", nullptr, nullptr);
    if (window == nullptr) {
        throw WindowException("Failed to create window!");
    }
}

void Window::initOpenGL() {
    if (GLEW_OK != glewInit()) {
        throw WindowException("Failed to initialise OpenGL context");
    }
    // OpenGL calls can now be made, init renderer
    renderer.init();
}

void Window::initImGui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::deinit() {
    // Do not put in destructor because window creationg might have failed
    // and then there would be nothing to destroy when Window gets deleted
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    renderer.deinit();

    glfwDestroyWindow(window);
    glfwTerminate();
}

// For window resizing, glfw isn't very OOP friendly
void Window::fbResizeCallback(GLFWwindow* window, int width, int height) {
    Window::needsResize = true;
}

void Window::run() {
    init();

    int integratorSelection(0);
    bool shouldStep(false);
    bool shouldPause(paused);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Update system and handle inputs
        update();
        
        // Resize window before rendering
        if (needsResize) {
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            renderer.resize(display_w, display_h);
        }
        // Render system
        render();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Cloth Simulation!");
        
        ImGui::SeparatorText("General information");
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        glm::vec3 pos(renderer.getPosition());
        ImGui::Text("Pos %.1f %.1f %.1f", pos.x, pos.y, pos.z);
        glm::vec3 rot(renderer.getRotation());
        ImGui::Text("Pitch %.0f°, Yaw %.0f°, Roll %.0f°", rot.x * 180 / M_PI, rot.y * 180 / M_PI, rot.z * 180 / M_PI);

        ImGui::SeparatorText("Appearance");
        ImGui::ColorEdit3("color", renderer.shapeColor);
        ImGui::SliderFloat("Scale", &renderer.scale, 0.1, 2.0);
        ImGui::Checkbox("Draw Masses?", &renderer.drawMass);
        ImGui::Checkbox("Draw Springs?", &renderer.drawSpring);
        
        if (ImGui::Button("Reset Camera")) renderer.reset();

        ImGui::SeparatorText("Simulation");
        ImGui::Text("Elapsed time: %.3fs", system.getTime());
        ImGui::Checkbox("Pause", &shouldPause);
        if (shouldPause) {
            ImGui::SameLine();
            if (ImGui::Button("Step")) shouldStep = true;
        }
        paused = shouldPause and not shouldStep;
        shouldStep = false;

        ImGui::Text("Integrator selection");
        if (ImGui::RadioButton("Euler-Cromer", &integratorSelection, 0))
            physicsIntegrator = std::make_unique<EulerCromerIntegrator>();
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Classic Euler-Cromer method, not very precise");
        ImGui::SameLine();
        if (ImGui::RadioButton("RK4", &integratorSelection, 1))
            physicsIntegrator = std::make_unique<RK4Integrator>();
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("RK4 wouhouhouhouhou");
        ImGui::SameLine();
        if (ImGui::RadioButton("Non-existant", &integratorSelection, 2))
            physicsIntegrator = std::unique_ptr<Integrator>(nullptr);
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Crap nullptr integrator that segfault this lol");

        ImGui::SliderFloat("Delta time", &deltaTime, 0.001, 0.1, "%.3f sec");
        ImGui::SliderInt("Speed", &iterationsPerFrame, 1, 100, "%dx speed", ImGuiSliderFlags_Logarithmic);

        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    deinit();
}

void Window::update() {
    // Get elapsed time between frames (for framerate independent movement)
    const double dt(ImGui::GetIO().DeltaTime);

    // Handle camera movement
    renderer.update(dt);

    // Step physics with constant time (deterministic)
    if (not paused) {
        for (int i(0); i < iterationsPerFrame; ++i) {
            system.step(*physicsIntegrator, deltaTime);
        }
    }
}

void Window::render() {
    renderer.beginFrame();
    renderer.clear();
    system.draw(renderer);
    // renderer.drawAxis();
    renderer.endFrame();
}
