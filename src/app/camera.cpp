#include "include/camera.h"
#include "include/constants.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/trigonometric.hpp>
#include <algorithm>

Camera::Camera(): Camera(CAMERA_FOV, CAMERA_RATIO, CAMERA_NEAR, CAMERA_FAR) {}

Camera::Camera(double fov, double ratio, double near, double far):
    fov(fov), ratio(ratio), near(near), far(far),
    position(0.0), pitch(0.0), yaw(0.0), roll(0.0), dirty(true)
{
    updateProjection();
}

void Camera::constrainAngles() {
    // yaw (left / right): free
    // pitch (up / down): -90 deg to 90 deg
    // roll (barrel roll): free
    pitch = std::clamp((double)pitch, -M_PI_2, M_PI_2);
}

void Camera::updateProjection() {
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
    constrainAngles();
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
    constrainAngles();
}

void Camera::setFov(double newFov) {
    dirty = true;
    fov = newFov;
    updateProjection();
}

void Camera::setAspect(double newRatio) {
    dirty = true;
    ratio = newRatio;
    updateProjection();
}

// Accessors
const glm::mat4x4& Camera::getMatrix() {
    if (dirty) {
        view = glm::mat4x4(1.0);
        view = glm::rotate(view, roll, glm::vec3(0, 0, 1));
        view = glm::rotate(view, pitch, glm::vec3(1, 0, 0));
        view = glm::rotate(view, yaw, glm::vec3(0, 1, 0));
        view = glm::translate(view, -position);

        world = projection * view;
        dirty = false;
    }
    return world;
}

// Queries
glm::vec3 Camera::forward() const {
    return glm::vec3(
        sin(yaw) * cos(pitch),
        -sin(pitch),
        -cos(yaw) * cos(pitch)
    );
}

glm::vec3 Camera::horizontalForward() const {
    return glm::vec3(sin(yaw), 0, -cos(yaw));
}

glm::vec3 Camera::right() const {
    return glm::vec3(
        sin(yaw) * sin(pitch) * sin(roll) - cos(yaw) * cos(roll),
        cos(pitch) * sin(roll),
        -cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll)
    );
}

glm::vec3 Camera::horizontalRight() const {
    return glm::vec3(-cos(yaw), 0, -sin(yaw));
}

glm::vec3 Camera::up() const {
    return glm::cross(forward(), right());
}

glm::vec3 Camera::horizontalUp() const {
    return glm::vec3(0.0, 1.0, 0.0);
}
