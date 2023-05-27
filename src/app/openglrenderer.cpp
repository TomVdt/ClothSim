#include "include/cloth.h"
#include "include/constants.h"
#include "include/constraint.h"
#include "include/exceptions.h"
#include "include/geometry.h"
#include "include/masse.h"
#include "include/openglrenderer.h"
#include "include/settings.h"
#include "include/shaderprogram.h"
#include "include/spring.h"
#include "include/system.h"
#include "include/vector3d.h"

#ifdef DEBUG
#include "include/util.h"
#include <iostream>
#endif

#include <imgui/imgui.h>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

OpenGLRenderer::OpenGLRenderer():
    program(),
    vbo(Buffer::Vertex),
    ebo(Buffer::Index),
    vertexLocation(0), colorLocation(0), projectionViewMatrixLocation(0), modelMatrixLocation(0),
    offsetLine(0), offsetCube(0), offsetSphere(0),
    indexLine(0), indexCube(0), indexSphere(0),
    camera(),
    massColor(1.0), constraintColor(0.1), massScale(0.25),
    drawMasses(true), drawSpeedVectors(true), drawSprings(true), drawConstraints(true),
    frameCount(0)
{
    reset();
}

#ifdef DEBUG
// https://www.khronos.org/opengl/wiki/Example/OpenGL_Error_Testing_with_Message_Callbacks
void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    UNUSED(id); UNUSED(length); UNUSED(userParam);
    if (severity >= GL_DEBUG_SEVERITY_MEDIUM) {
        std::cerr << "GL CALLBACK: "
                  << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
                  << " type = 0x" << type
                  << ", severity = 0x" << severity
                  << ", message = " << message
                  << "\n";
    }
}
#endif

void OpenGLRenderer::init() {
    // Backface culling
    glEnable(GL_CULL_FACE);
    // Depth buffer
    glEnable(GL_DEPTH_TEST);
    // Transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    #ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    #endif

    // Background color
    // #9ddcea
    glClearColor(157.0 / 255.0, 220.0 / 255.0, 234.0 / 255.0, 1.0f);

    // Create shader
    // Macros used to avoid hardcoding the path
    // Gets set correctly by the Makefile during compilation
    #ifndef VERTEX_PATH
    #define VERTEX_PATH "src/shaders/vert.glsl"
    #endif
    program.addShader(VERTEX_PATH, ShaderProgram::Vertex);
    #ifndef FRAGMENT_PATH
    #define FRAGMENT_PATH "src/shaders/frag.glsl"
    #endif
    program.addShader(FRAGMENT_PATH, ShaderProgram::Fragment);
    program.link();
    program.bind();

    // Store attribute and uniforms location for reuse later (cleaner than strings)
    vertexLocation = program.attributeLocation("vertex");
    colorLocation = program.uniformLocation("color");
    modelMatrixLocation = program.uniformLocation("m_matrix");
    projectionViewMatrixLocation = program.uniformLocation("pv_matrix");

    // Create VAO
    vao.create();
    vao.bind();

    // VBO
    vbo.create();
    vbo.bind();

    // Load geometry
    int lineSize(Geometry::lineVertices.size() * sizeof(Geometry::lineVertices[0]));
    int cubeSize(Geometry::cubeVertices.size() * sizeof(Geometry::cubeVertices[0]));
    int sphereSize(Geometry::sphereVertices.size() * sizeof(Geometry::sphereVertices[0]));
    int total(lineSize + cubeSize + sphereSize);
    vbo.allocate(nullptr, total);

    int offset(0);
    vbo.write(offset, &Geometry::lineVertices.front(), lineSize);
    offset += lineSize;
    vbo.write(offset, &Geometry::cubeVertices.front(), cubeSize);
    offset += cubeSize;
    vbo.write(offset, &Geometry::sphereVertices.front(), sphereSize);

    program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3);
    program.enableAttributeArray(vertexLocation);

    ebo.create();
    ebo.bind();
    
    lineSize = Geometry::lineIndices.size() * sizeof(Geometry::lineIndices[0]);
    cubeSize = Geometry::cubeIndices.size() * sizeof(Geometry::cubeIndices[0]);
    sphereSize = Geometry::sphereIndices.size() * sizeof(Geometry::sphereIndices[0]);
    total = lineSize + cubeSize + sphereSize;
    ebo.allocate(nullptr, total);

    offset = 0;
    offsetLine = 0;
    indexLine = 0;
    ebo.write(offset, &Geometry::lineIndices.front(), lineSize);
    offset += lineSize;
    offsetCube = offset;
    indexCube = indexLine + Geometry::lineIndices.back() + 1;
    ebo.write(offset, &Geometry::cubeIndices.front(), cubeSize);
    offset += cubeSize;
    offsetSphere = offset;
    indexSphere = indexCube + Geometry::cubeIndices.back() + 1;
    ebo.write(offset, &Geometry::sphereIndices.front(), sphereSize);

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
    camera.setAspect(ratio);
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::clear() {
    // Clear previous frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::reset() {
    camera.setRotation(glm::radians(35.0), glm::radians(135.0), 0);
    camera.setPosition(-20, 20, -20);
}

void OpenGLRenderer::beginFrame() {
    program.bind();
    vao.bind();

    program.setUniformValue(projectionViewMatrixLocation, camera.getMatrix());
}

void OpenGLRenderer::endFrame() {
    vao.release();
    program.release();
    ++frameCount;
}

void OpenGLRenderer::deinit() {
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    program.destroy();
}

void OpenGLRenderer::update(double dt) {
    glm::vec3 move(0.0);
    // Minecraft-like movement
    glm::vec3 forward(camera.horizontalForward());
    glm::vec3 right(camera.horizontalRight());
    glm::vec3 up(camera.horizontalUp());
    if (ImGui::IsKeyDown(Settings::FRONT)) {
        move += forward;
    }
    if (ImGui::IsKeyDown(Settings::BACK)) {
        move -= forward;
    }
    if (ImGui::IsKeyDown(Settings::LEFT)) {
        move += right;
    }
    if (ImGui::IsKeyDown(Settings::RIGHT)) {
        move -= right;
    }
    if (ImGui::IsKeyDown(Settings::UP)) {
        move += up;
    }
    if (ImGui::IsKeyDown(Settings::DOWN)) {
        move -= up;
    }

    double len(glm::length(move));
    if (len > CONSTANTS::EPSILON) {
        move /= len;
        camera.translate(move * (float)cameraMoveSpeed * (float)dt);
    }

    if (not ImGui::GetIO().WantCaptureMouse && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        double dx(ImGui::GetIO().MouseDelta.x);
        double dy(ImGui::GetIO().MouseDelta.y);
        double dz(0.0);
        camera.rotate(dy * cameraRotateSpeed, dx * cameraRotateSpeed, dz * cameraRotateSpeed);
    }
}

/******************
 * Drawing stuff! *
 ******************/

#ifdef PRIDE
// https://stackoverflow.com/questions/8208905/hsv-0-255-to-rgb-0-255
glm::vec4 hsvToRgba(double h, double s, double v){
    double r, g, b;

    int i = h * 6;
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    return glm::vec4(r, g, b, 1.0);
}
#endif

void OpenGLRenderer::draw(const Masse& mass) {
    #ifdef PRIDE
    const float alpha(massColor.a);
    massColor = hsvToRgba(frameCount * 0.01 + mass.getId() * 0.1, 1.0, 1.0);
    massColor.a = alpha;
    #endif

    const Vector3D& pos(mass.getPos());

    if (drawMasses) {
        const Vector3D scaling(massScale, massScale, massScale);
        drawSphere(pos, scaling, massColor);
    }

    if (drawSpeedVectors) {
        const Vector3D& vel(mass.getVel());
        drawLine(pos, pos + vel, massColor);
    }
}

void OpenGLRenderer::draw(const Spring& spring) {
    if (not drawSprings) {
        return;
    }

    glm::vec4 squishColor(1.0, 0.0, 0.0, 1.0);
    glm::vec4 neutralColor(1.0);
    glm::vec4 stretchColor(0.0, 0.0, 1.0, 1.0);
    const double springDelta(spring.length() - spring.getL0());
    double factor(1 / (1 + std::exp(-springDelta)));

    glm::vec4 color(1.0);
    if (factor < 0.5) {
        // Squished
        color = glm::mix(squishColor, neutralColor, factor * 2);
    } else {
        // Stretched
        color = glm::mix(neutralColor, stretchColor, (factor - 0.5) * 2);
    }

    const Vector3D start(spring.getStartPos());
    const Vector3D end(spring.getEndPos());
    drawLine(start, end, color);
}

void OpenGLRenderer::draw(const Cloth& cloth) {
    cloth.drawParticles(*this);
}

void OpenGLRenderer::draw(const System& system) {
    system.drawContents(*this);
}

void OpenGLRenderer::draw(const Constraint& constraint) {
    if (not drawConstraints) {
        return;
    }

    double scale(constraint.getRadius());
    drawSphere(constraint.getPos(), Vector3D(scale, scale, scale), constraintColor);
}

void OpenGLRenderer::drawControls() {
    ImGui::ColorEdit4("Mass color", &massColor[0]);
    ImGui::ColorEdit4("Constraint color", &constraintColor[0]);
    ImGui::SliderFloat("Scale", &massScale, 0.1, 0.5);
    ImGui::Checkbox("Draw Masses?", &drawMasses);
    ImGui::Checkbox("Draw Speed Vectors?", &drawSpeedVectors);
    ImGui::Checkbox("Draw Springs?", &drawSprings);
    ImGui::Checkbox("Draw Constraints?", &drawConstraints);
    
    if (ImGui::Button("Reset Camera")) reset();
}

/*******************
 * Drawing shapes! *
 *******************/

void OpenGLRenderer::drawLine(const Vector3D& pos1, const Vector3D& pos2, const glm::vec4& color) {
    // Let's call this "extremely hacky but it works" *dabs*
    // Who needs optimised rendering code anyways right?
    GLfloat line[] = {
        (float)pos1.getX(), (float)pos1.getY(), (float)pos1.getZ(),
        (float)pos2.getX(), (float)pos2.getY(), (float)pos2.getZ()
    };

    glm::mat4x4 model(1.0);
    program.setUniformValue(modelMatrixLocation, model);
    program.setUniformValue(colorLocation, color);
    vbo.bind();
    vbo.write(indexLine, line, sizeof(line));
    glDrawElementsBaseVertex(GL_LINES, Geometry::lineIndices.size(), GL_UNSIGNED_INT, reinterpret_cast<void*>(offsetLine), indexLine);
}

void OpenGLRenderer::drawCube(const Vector3D& pos, const Vector3D& scale, const glm::vec4& color) {
    glm::mat4x4 model(1.0);
    model = glm::translate(model, pos.toGlmVec3());
    model = glm::scale(model, scale.toGlmVec3());
    program.setUniformValue(modelMatrixLocation, model);
    program.setUniformValue(colorLocation, color);
    glDrawElementsBaseVertex(GL_TRIANGLES, Geometry::cubeIndices.size(), GL_UNSIGNED_INT, reinterpret_cast<void*>(offsetCube), indexCube);
}

void OpenGLRenderer::drawSphere(const Vector3D& pos, const Vector3D& scale, const glm::vec4& color) {
    glm::mat4x4 model(1.0);
    model = glm::translate(model, pos.toGlmVec3());
    model = glm::scale(model, scale.toGlmVec3());
    program.setUniformValue(modelMatrixLocation, model);
    program.setUniformValue(colorLocation, color);
    glDrawElementsBaseVertex(GL_TRIANGLES, Geometry::sphereIndices.size(), GL_UNSIGNED_INT, reinterpret_cast<void*>(offsetSphere), indexSphere);
}

void OpenGLRenderer::drawAxis() {
    drawCube(Vector3D(1.1, 0.0, 0.0), Vector3D(1.0, 0.1, 0.1), glm::vec4(1.0, 0.0, 0.0, 1.0));
    drawCube(Vector3D(0.0, 1.1, 0.0), Vector3D(0.1, 1.0, 0.1), glm::vec4(0.0, 1.0, 0.0, 1.0));
    drawCube(Vector3D(0.0, 0.0, 1.1), Vector3D(0.1, 0.1, 1.0), glm::vec4(0.0, 0.0, 1.0, 1.0));
    drawCube(Vector3D(0.0, 0.0, 0.0), Vector3D(0.1, 0.1, 0.1), glm::vec4(1.0, 1.0, 1.0, 1.0));
}
