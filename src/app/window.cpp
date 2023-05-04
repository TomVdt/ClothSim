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
    // std::unique_ptr<RectCloth> cloth1(std::make_unique<RectCloth>(
    //     1.0,
    //     Vector3D(40.0, 0.0, 0.0), Vector3D(0.0, 0.0, 40.0),
    //     Vector3D(0.0, 10.0, 0.0),
    //     0.3,
    //     20.0,
    //     50.0, 2.0
    // ));

    std::unique_ptr<DiskCloth> cloth2(std::make_unique<DiskCloth>(
        1.0,
        Vector3D(),
        Vector3D(0.0, 100.0, 0.0),
        2.0,
        0.3,
        100.0
    ));

    // std::unique_ptr<DiskCloth> cloth3(std::make_unique<DiskCloth>(
    //     1.0,
    //     Vector3D(0.0, 0.0, 16.5),
    //     Vector3D(0.0, 10.0, 0.0),
    //     2.0,
    //     0.3,
    //     100.0
    // ));

    // std::unique_ptr<CompositeCloth> cloth4(std::make_unique<CompositeCloth>());
    // cloth4->linkCloth(std::move(cloth2));
    // cloth4->linkCloth(std::move(cloth3));

    // system.addCloth(std::move(cloth1));
    system.addCloth(std::move(cloth2));
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

        ImGui::Begin("Hallo wereld!");
        
        ImGui::SeparatorText("General information");
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        glm::vec3 pos(renderer.getPosition());
        ImGui::Text("Pos %.1f %.1f %.1f", pos.x, pos.y, pos.z);
        glm::vec3 rot(renderer.getRotation());
        ImGui::Text("Pitch %.0f°, Yaw %.0f°, Roll %.0f°", rot.x * 180 / M_PI, rot.y * 180 / M_PI, rot.z * 180 / M_PI);

        ImGui::SeparatorText("Appearance");
        ImGui::ColorEdit3("color", renderer.shapeColor);
        ImGui::SliderFloat("Scale", &renderer.scale, 0.1, 2.0);
        ImGui::SliderInt("Test", &renderer.test, 0, 24);
        
        if (ImGui::Button("Reset Camera")) renderer.reset();

        ImGui::SeparatorText("Simulation");
        ImGui::Checkbox("Pause", &paused);

        ImGui::Text("Integrator selection");
        if (ImGui::RadioButton("Euler-Cromer", &integratorSelection, 0))
            physicsIntegrator = std::make_unique<EulerCromerIntegrator>();
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Classic Euler-Cromer method, not very precise");
        ImGui::SameLine();
        if (ImGui::RadioButton("Non-existant", &integratorSelection, 1))
            physicsIntegrator = std::unique_ptr<Integrator>(nullptr);
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Crap nullptr integrator that segfault this lol");

        ImGui::SliderFloat("Delta time", &deltaTime, 0.001, 0.5, "%.3f sec");
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
    renderer.endFrame();
}
