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
float OpenGLRenderer::scale = 1.0;
int OpenGLRenderer::test = 0;

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
    program.addShader("src/shaders/vert.glsl", ShaderProgram::Vertex);
    program.addShader("src/shaders/frag.glsl", ShaderProgram::Fragment);
    program.link();
    program.bind();

    // Add an fbo to enable rendering to texture
    // fbo.create(1, 1);

    // Store attribute and uniforms location for reuse later (cleaner than strings)
    vertexLocation = program.attributeLocation("vertex");
    colorLocation = program.uniformLocation("color");
    modelMatrixLocation = program.uniformLocation("m_matrix");
    projectionViewMatrixLocation = program.uniformLocation("pv_matrix");

    // Create geometry for testing
    // createCube();

    // Create VAO
    vao.create();
    vao.bind();

    // VBO
    vbo.create();
    vbo.bind();
    GLfloat verts[] = {
		-1.0, -1.0, -1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0,
		 1.0, -1.0, -1.0,  1.0,  1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,
		 1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,  1.0, -1.0, -1.0,  1.0,
		-1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0, -1.0, -1.0,
		-1.0, -1.0, -1.0,  1.0, -1.0, -1.0,  1.0, -1.0,  1.0, -1.0, -1.0,  1.0,
		-1.0,  1.0, -1.0, -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0
	};
    vbo.allocate(verts, sizeof(verts));

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
    camera.setProjection(glm::perspective(CONSTANTS::CAMERA_FOV, ratio, CONSTANTS::CAMERA_NEAR, CONSTANTS::CAMERA_FAR));

    glViewport(0, 0, width, height);
    // fbo.rescaleFrameBuffer(width, height);
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
    // Possibly render to a texture
    // fbo.bind();

    program.setUniformValue(projectionViewMatrixLocation, camera.getMatrix());
}

void OpenGLRenderer::endFrame() {
    // fbo.release();
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

    // TODO: double comparaison
    // TODO: constants
    constexpr float moveSpeed(25.0);
    double len(glm::length(move));
    if (len != 0.0) {
        move /= len;
        camera.translate(move * moveSpeed * (float)dt);
    }

    if (not ImGui::GetIO().WantCaptureMouse && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        double dx(ImGui::GetIO().MouseDelta.x);
        double dy(ImGui::GetIO().MouseDelta.y);
        // TODO: constants
        constexpr double rotateSpeed(0.005);
        camera.rotate(dy * rotateSpeed, dx * rotateSpeed, 0);
    }
}

GLuint OpenGLRenderer::getFrameTexture() {
    // return fbo.getFrameTexture();
    return 0;
}

/******************
 * Drawing stuff! *
 ******************/

void OpenGLRenderer::draw(const Masse& masse) {
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
    // TODO: draw springs
    Vector3D smol((spring.getStartMass().getPos() + spring.getEndMass().getPos()) / 2.0);

    glm::mat4x4 model(1.0);
    model = glm::translate(model, smol.toGlmVec3());
    model = glm::scale(model, glm::vec3(0.1));
    program.setUniformValue(modelMatrixLocation, model);

    // Set color
    glm::vec4 color(1.0);
    program.setUniformValue(colorLocation, color);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, 0);
}

void OpenGLRenderer::draw(const Cloth& cloth) {
    cloth.drawParticles(*this);
}

void OpenGLRenderer::draw(const System& system) {
    system.drawContents(*this);
    drawAxis();
}

void OpenGLRenderer::drawAxis() {
    glm::mat4x4 model(1.0);
    model = glm::translate(model, glm::vec3(2, 0, 0));
    model = glm::scale(model, glm::vec3(2, 0.5, 0.5));
    program.setUniformValue(modelMatrixLocation, model);
    glm::vec4 red(1.0, 0.0, 0.0, 1.0);
    program.setUniformValue(colorLocation, red);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, 0);

    model = glm::mat4x4(1.0);
    model = glm::translate(model, glm::vec3(0, 2, 0));
    model = glm::scale(model, glm::vec3(0.5, 2.0, 0.5));
    program.setUniformValue(modelMatrixLocation, model);
    glm::vec4 green(0.0, 1.0, 0.0, 1.0);
    program.setUniformValue(colorLocation, green);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, 0);

    model = glm::mat4x4(1.0);
    model = glm::translate(model, glm::vec3(0, 0, 2));
    model = glm::scale(model, glm::vec3(0.5, 0.5, 2));
    program.setUniformValue(modelMatrixLocation, model);
    glm::vec4 blue(0.0, 0.0, 1.0, 1.0);
    program.setUniformValue(colorLocation, blue);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, 0);
}
