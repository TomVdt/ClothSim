#include "include/openglrenderer.h"
#include "include/masse.h"
#include "include/cloth.h"
#include "include/system.h"
#include "include/vector3d.h"
#include "include/exceptions.h"

#include "GLFW/glfw3.h"
#include <imgui/imgui.h>
#include <iostream>
#include <stdio.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

float OpenGLRenderer::shapeColor[3] = { 0.2, 0.3, 0.6 };
float OpenGLRenderer::scale = 0.5;
bool OpenGLRenderer::drawMass = true;
bool OpenGLRenderer::drawSpring = true;

OpenGLRenderer::OpenGLRenderer():
    camera(),
    program(),
    vbo(Buffer::Vertex),
    ebo(Buffer::Index)
{
    reset();
}

// TODO: clean up
// void GLAPIENTRY MessageCallback(GLenum source,
//     GLenum type,
//     GLuint id,
//     GLenum severity,
//     GLsizei length,
//     const GLchar* message,
//     const void* userParam)
// {
//     fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
//         (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
//         type, severity, message);
// }


void OpenGLRenderer::init() {
    // Backface culling and z buffer
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    // During init, enable debug output
    // TODO: clean up
    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(MessageCallback, 0);

    // Background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Create shader
    // TODO: unhardcode path?
    program.addShader("src/shaders/vert.glsl", ShaderProgram::Vertex);
    program.addShader("src/shaders/frag.glsl", ShaderProgram::Fragment);
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
    // TODO: actual geometry handling
    GLfloat verts[] = {
		-1.0, -1.0, -1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,  1.0,  1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,  1.0, -1.0, -1.0,  1.0,
		-1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0, -1.0, -1.0,
		-1.0, -1.0, -1.0,  1.0, -1.0, -1.0,  1.0, -1.0,  1.0, -1.0, -1.0,  1.0,
		-1.0,  1.0, -1.0, -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
        // Free space to write to...
		69, 69, 69, 69, 69, 69
	};
    vbo.allocate(verts, sizeof(verts) + 4 * 6);

    program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3);
    program.enableAttributeArray(vertexLocation);

    ebo.create();
    ebo.bind();
    GLushort ind[] = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 3, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };
    ebo.allocate(ind, sizeof(ind));

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
    // TODO: camera constants, not this
    camera.setProjection(glm::perspective(CONSTANTS::CAMERA_FOV, ratio, CONSTANTS::CAMERA_NEAR, CONSTANTS::CAMERA_FAR));
    // camera.setProjection(glm::ortho(-width / 100.0, width / 100.0, -height / 100.0, height / 100.0, CONSTANTS::CAMERA_NEAR, CONSTANTS::CAMERA_FAR));

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
}

void OpenGLRenderer::deinit() {
    vao.destroy();
    vbo.destroy();
}

void OpenGLRenderer::update(double dt) {
    glm::vec3 move(0.0);
    // Minecraft-like movement
    glm::vec3 forward(camera.forward());
    glm::vec3 right(camera.right());
    glm::vec3 up(camera.up());
    if (ImGui::IsKeyDown(ImGuiKey_W)) {
        move -= forward;
    }
    if (ImGui::IsKeyDown(ImGuiKey_S)) {
        move += forward;
    }
    if (ImGui::IsKeyDown(ImGuiKey_A)) {
        move -= right;
    }
    if (ImGui::IsKeyDown(ImGuiKey_D)) {
        move += right;
    }
    if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
        move -= up;
    }
    if (ImGui::IsKeyDown(ImGuiKey_Space)) {
        move += up;
    }

    double len(glm::length(move));
    if (len > CONSTANTS::EPSILON) {
        move /= len;
        camera.translate(move * (float)cameraMoveSpeed * (float)dt);
    }

    if (not ImGui::GetIO().WantCaptureMouse && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        double dx(ImGui::GetIO().MouseDelta.x);
        double dy(ImGui::GetIO().MouseDelta.y);
        camera.rotate(dy * cameraRotateSpeed, dx * cameraRotateSpeed, 0);
    }
}

/******************
 * Drawing stuff! *
 ******************/

void OpenGLRenderer::draw(const Masse& masse) {
    if (not drawMass) {
        return;
    }

    // Set to correct position
    const Vector3D& pos(masse.getPos());
    glm::mat4x4 model(1.0);
    model = glm::translate(model, pos.toGlmVec3());
    model = glm::scale(model, glm::vec3(scale));
    program.setUniformValue(modelMatrixLocation, model);

    // Set color
    glm::vec4 color(shapeColor[0], shapeColor[1], shapeColor[2], 1.0);
    program.setUniformValue(colorLocation, color);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, 0);
}

void OpenGLRenderer::draw(const Spring& spring) {
    if (not drawSpring) {
        return;
    }

    glm::mat4x4 model(1.0);
    program.setUniformValue(modelMatrixLocation, model);

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
    program.setUniformValue(colorLocation, color);

    const Vector3D start(spring.getStartMass().getPos());
    const Vector3D end(spring.getEndMass().getPos());
    drawLine(start, end);
}

void OpenGLRenderer::draw(const Cloth& cloth) {
    cloth.drawParticles(*this);
}

void OpenGLRenderer::draw(const System& system) {
    system.drawContents(*this);
}

/*******************
 * Drawing shapes! *
 *******************/

// TODO: clean up comment
// If ever needed: https://github.com/qt/qtbase/blob/9d2cc4dd766ca6538e17040b6ac845ed880ab0fe/src/gui/math3d/qquaternion.cpp#L714

void OpenGLRenderer::drawLine(const Vector3D& pos1, const Vector3D& pos2) {
    // Let's call this "extremely hacky but it works" *dabs*
    // Who needs optimised rendering code anyways right?
    GLfloat line[] = {
        (float)pos1.getX(), (float)pos1.getY(), (float)pos1.getZ(),
        (float)pos2.getX(), (float)pos2.getY(), (float)pos2.getZ()
    };
    vbo.bind();
    // TODO: hardcoding go brrrrrr
    vbo.write(4 * 12 * 6, line, sizeof(line));
    glDrawArrays(GL_LINES, 4 * 6, 2);
}

void OpenGLRenderer::drawRect(const Vector3D& pos, const Vector3D& scale, const Vector3D& color) {
    glm::mat4x4 model(1.0);
    model = glm::translate(model, pos.toGlmVec3());
    model = glm::scale(model, scale.toGlmVec3());
    program.setUniformValue(modelMatrixLocation, model);
    program.setUniformValue(colorLocation, glm::vec4(color.toGlmVec3(), 1.0));
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, 0);
}

void OpenGLRenderer::drawAxis() {
    drawRect(Vector3D(1.1, 0.0, 0.0), Vector3D(1.0, 0.1, 0.1), Vector3D(1, 0, 0));
    drawRect(Vector3D(0.0, 1.1, 0.0), Vector3D(0.1, 1.0, 0.1), Vector3D(0, 1, 0));
    drawRect(Vector3D(0.0, 0.0, 1.1), Vector3D(0.1, 0.1, 1.0), Vector3D(0, 0, 1));
}
