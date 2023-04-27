#include "include/window.h"
#include "include/cloth.h"
#include "include/masse.h"
#include "include/vector3d.h"
#include "include/constants.h"
#include "include/exceptions.h"

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

bool Window::needsResize(true);

Window::Window(): renderer(), system(), physicsIntegrator(std::make_unique<EulerCromerIntegrator>()), window(nullptr), paused(true) {
    std::unique_ptr<Cloth> cloth(std::make_unique<Cloth>());

    // Create particles
    constexpr int count(10);
    for (int y(0); y < count; ++y) {
        for (int x(0); x < count; ++x) {
            cloth->addMass(std::make_unique<Masse>(1.0, 0.3, Vector3D(4 * x, 0, 4 * y), Vector3D(0, 0, 0), y == 0));
        }
    }

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
}

Window::~Window() {
    // Nothing to delete, renderer has already been `deinit`-ed
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
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        
        glm::vec3 pos(renderer.getPosition());
        ImGui::Text("Pos %.1f %.1f %.1f", pos.x, pos.y, pos.z);
        glm::vec3 rot(renderer.getRotation());
        
        ImGui::Text("Rotation %.1f %.1f %.1f (rad)", rot.x, rot.y, rot.z);
        ImGui::ColorEdit3("color", renderer.shapeColor);
        ImGui::SliderFloat("Scale", &renderer.scale, 0.1, 2.0);
        ImGui::Checkbox("Pause", &paused);
        
        if (ImGui::Button("Reset Camera")) renderer.reset();
        
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
        system.step(*physicsIntegrator, CONSTANTS::PHYSICS_DT);
    }
}

void Window::render() {
    renderer.beginFrame();
    renderer.clear();
    system.draw(renderer);
    renderer.endFrame();
}
