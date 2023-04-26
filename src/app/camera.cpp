#include "include/camera.h"
#include "include/constants.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera():
    Camera(CONSTANTS::CAMERA_FOV, CONSTANTS::CAMERA_RATIO, CONSTANTS::CAMERA_NEAR, CONSTANTS::CAMERA_FAR) {}


Camera::Camera(double fov, double ratio, double near, double far): position(0.0), pitch(0.0), yaw(0.0), roll(0.0), dirty(true) {
    projection = glm::perspective(fov, ratio, near, far);
}

// Transform By (Add/Scale)
void Camera::translate(const glm::vec3& dt) {
    dirty = true;
    position += dt;
}

void Camera::rotate(double dp, double dy, double dr) {
    dirty = true;
    pitch += dp;
    yaw += dy;
    roll += dr;
}

// Transform To (Setters)
void Camera::setPosition(const glm::vec3& t) {
    dirty = true;
    position = t;
}

void Camera::setRotation(double p, double y, double r) {
    dirty = true;
    pitch = p;
    yaw = y;
    roll = r;
}

void Camera::setProjection(const glm::mat4x4& proj) {
    dirty = true;
    projection = proj;
}

// Accessors
const glm::mat4x4& Camera::getMatrix() {
    if (dirty) {
        view = glm::mat4x4(1.0);
        view = glm::rotate(view, pitch, glm::vec3(1, 0, 0));
        view = glm::rotate(view, yaw, glm::vec3(0, 1, 0));
        view = glm::rotate(view, roll, glm::vec3(0, 0, 1));
        view = glm::translate(view, -position);

        world = projection * view;
        dirty = false;
    }
    return world;
}

// Queries
glm::vec3 Camera::forward() const {
    return glm::vec3(-sin(yaw), 0, cos(yaw));
}

glm::vec3 Camera::right() const {
    return glm::vec3(cos(yaw), 0, sin(yaw));
}

glm::vec3 Camera::up() const {
    return glm::vec3(0, 1, 0);
}