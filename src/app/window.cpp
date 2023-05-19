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
#include "include/settings.h"

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

bool Window::needsResize(true);

Window::Window(System&& system_):
    renderer(),
    system(std::move(system_)),
    physicsIntegrator(std::make_unique<EulerCromerIntegrator>()),
    window(nullptr),
    paused(true),
    drawAxis(false),
    deltaTime(CONSTANTS::PHYSICS_DT),
    iterationsPerFrame(1) {}

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

void Window::setSystem(System&& sys) {
    system = std::move(sys);
}

#ifdef DEBUG
void glfwErrorCallback(int err, const char* description) {
    printf("GLFW Error %d: %s\n", err, description);
}
#endif

void Window::initGLFW() {
    #ifdef DEBUG
    glfwSetErrorCallback(glfwErrorCallback);
    #endif
    if (!glfwInit()) {
        ERROR(GLFWError, "Failed to initialise GLFW");
    }

    // Set GLSL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Window::createWindow() {
    // Create window with graphics context
    window = glfwCreateWindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, Settings::WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        ERROR(GLFWError, "Failed to create window");
    }
}

void Window::initOpenGL() {
    if (GLEW_OK != glewInit()) {
        ERROR(GLFWError, "Failed to initialise OpenGL context");
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
    // Do not put in destructor because window creation might have failed
    // and then there would be nothing to destroy when `Window` gets deleted
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
    bool showClothMenu(false);
    bool showConstraintMenu(false);

    constexpr int energyCount(512);
    int energyOffset(0);
    float energyMin(0.0);
    float energyMax(0.0);
    float energy[energyCount] = { 0.0 };

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
        renderer.drawControls();
        ImGui::Checkbox("Draw Axis?", &drawAxis);

        ImGui::SeparatorText("Simulation");
        ImGui::Text("Elapsed time: %.3fs", system.getTime());

        // nrj12
        if (not paused) {
            energy[energyOffset] = system.energy();
            energyMin = std::min(energyMin, energy[energyOffset]);
            energyMax = std::max(energyMax, energy[energyOffset]);
            energyOffset = (energyOffset + 1) % energyCount;
        }
        ImGui::PlotLines("##Energie", energy, energyCount, energyOffset, "Energie", energyMin, energyMax, ImVec2(280, 100));

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
        //if (ImGui::RadioButton("RK4", &integratorSelection, 1))
        //    physicsIntegrator = std::make_unique<RK4Integrator>();
        //if (ImGui::IsItemHovered()) ImGui::SetTooltip("RK4 wouhouhouhouhou");
        //ImGui::SameLine();
        if (ImGui::RadioButton("Non-existant", &integratorSelection, 2))
            physicsIntegrator = std::unique_ptr<Integrator>(nullptr);
        if (ImGui::IsItemHovered()) ImGui::SetTooltip("Crap nullptr integrator that segfault this lol");

        ImGui::SliderFloat("Delta time", &deltaTime, 0.001, 0.1, "%.3f sec");
        ImGui::SliderInt("Speed", &iterationsPerFrame, 1, 100, "%dx speed", ImGuiSliderFlags_Logarithmic);

        if (ImGui::Button("Add Cloth")) showClothMenu = true;
        ImGui::SameLine();
        if (ImGui::Button("Add Constraint")) showConstraintMenu = true;
        ImGui::SameLine();
        if (ImGui::Button("Clear System")) {
            system.clear();
            paused = true;
            shouldPause = true;
            energyOffset = 0;
            energyMin = 0.0;
            energyMax = 0.0;
        }

        if (showClothMenu) {
            ImGui::Begin("Add new cloth", &showClothMenu);
            const char* options[] = { "Chain Cloth", "Rectangle Cloth", "Disk Cloth" };
            static int selected(0);
            ImGui::Combo("Cloth type", &selected, options, 3);

            ImGui::PushItemWidth(100);
            static float mass(1.0);
            ImGui::InputFloat("Mass", &mass, 0.01, 0.05, "%.2f kg");
            if (mass < 0.01) mass = 0.01;
            static float lambda(0.3);
            ImGui::InputFloat("Friction", &lambda, 0.01, 0.05, "%.2f");
            if (lambda < 0.0) lambda = 0.0;
            static float k(1.0);
            ImGui::InputFloat("Spring hardness", &k, 0.01, 0.05, "%.2f");
            if (k < 0.0) k = 0.0;
            static float l0(1.0);
            ImGui::InputFloat("Spring rest length", &l0, 0.01, 0.05, "%.2f");
            if (l0 < 0.01) l0 = 0.01;
            ImGui::PopItemWidth();

            switch (selected) {
            case 0:
                {
                    static int count(2);
                    static float positions[100][3] = { {0.0} };
                    for (int i(0); i < count; ++i) {
                        ImGui::SetNextItemWidth(200);
                        char id[16];
                        snprintf(id, 16, "Position##%i", i);
                        ImGui::InputFloat3(id, positions[i]);
                    }
                    if (ImGui::Button("+") and count < 100) ++count;
                    ImGui::SameLine();
                    if (ImGui::Button("-") and count > 1) --count;
                    if (ImGui::Button("Add")) {
                        std::vector<Vector3D> realPositions;
                        for (int i(0); i < count; ++i) realPositions.emplace_back(positions[i][0], positions[i][1], positions[i][2]);
                        system.addCloth(std::make_unique<ChainCloth>(
                            mass, lambda, k, l0,
                            realPositions
                        ));
                    }
                }
                break;
            case 1:
                {
                    static float origin[3] = { 0.0, 0.0, 0.0 };
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat3("Origin", origin);
                    static float vec1[3] = { 1.0, 0.0, 0.0 };
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat3("Vector 1", vec1);
                    static float vec2[3] = { 0.0, 0.0, 1.0 };
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat3("Vector 2", vec2);
                    static float step(1.0);
                    ImGui::InputFloat("Step between masses", &step, 0.01, 0.05, "%.2f units");
                    if (step < 0.01) step = 0.01;
                    if (ImGui::Button("Add")) {
                        system.addCloth(std::make_unique<RectCloth>(
                            mass,
                            Vector3D(vec1[0], vec1[1], vec1[2]), Vector3D(vec2[0], vec2[1], vec2[2]),
                            Vector3D(origin[0], origin[1], origin[2]),
                            lambda, step, k, l0
                        ));
                    }
                }
                break;
            case 2: 
                {
                    static float origin[3] = { 0.0, 0.0, 0.0 };
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat3("Origin", origin);
                    static float radius[3] = { 0.0, 5.0, 0.0 };
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat3("Radius vector", radius);
                    static float radStep(1.0);
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputFloat("Radial step", &radStep, 0.1, 0.5, "%.1f units");
                    if (radStep < 0.1) radStep = 0.1;
                    static float angStep(20.0);
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputFloat("Angular step", &angStep, 1.0, 5.0, "%.0f deg");
                    if (angStep < 0.0) angStep = 0.0;
                    if (angStep > 180.0) angStep = 180.0;
                    if (ImGui::Button("Add")) {
                        system.addCloth(std::make_unique<DiskCloth>(
                            mass,
                            Vector3D(origin[0], origin[1], origin[2]),
                            Vector3D(radius[0], radius[1], radius[2]),
                            radStep,
                            lambda, k,
                            angStep * M_PI / 180.0
                        ));
                    }
                }
                break;
            default:
                break;
            }

            ImGui::End();
        }

        if (showConstraintMenu) {
            ImGui::Begin("Add new constraint", &showConstraintMenu);
            const char* options[] = { "Hook Constraint", "Impulsion Constraint", "Sine Impulsion Constraint" };
            static int selected(0);
            ImGui::Combo("Cloth type", &selected, options, 3);

            static float pos[3] = { 0.0, 0.0, 0.0 };
            ImGui::SetNextItemWidth(200);
            ImGui::InputFloat3("Position", pos);
            static float radius(0.1);
            ImGui::SetNextItemWidth(100);
            ImGui::InputFloat("Radius", &radius, 0.01, 0.05, "%.2f");
            if (radius < 0.0) radius = 0.0;

            switch (selected) {
            case 0:
                if (ImGui::Button("Add")) {
                    system.addConstraint(std::make_unique<HookConstraint>(
                        Vector3D(pos[0], pos[1], pos[2]),
                        radius
                    ));
                }
                break;
            case 1:
                ImGui::Text("TODO");
                break;
            case 2:
                ImGui::Text("TODO");
                break;
            default:
                break;
            }

            ImGui::End();
        }

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
    if (drawAxis) {
        renderer.drawAxis();
    }
    renderer.endFrame();
}
