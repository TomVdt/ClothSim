#include "include/camera.h"
#include "include/constants.h"

const QVector3D Camera::LocalForward(0.0, 0.0, 1.0);
const QVector3D Camera::LocalUp(0.0, 1.0, 0.0);
const QVector3D Camera::LocalRight(1.0, 0.0, 0.0);

Camera::Camera():
    Camera(CONSTANTS::CAMERA_FOV, CONSTANTS::CAMERA_RATIO, CONSTANTS::CAMERA_NEAR, CONSTANTS::CAMERA_FAR) {}


Camera::Camera(double fov, double ratio, double near, double far):
    dirty(true),
    mode(FPS)
{
    setProjection(fov, ratio, near, far);
}

// Transform By (Add/Scale)
void Camera::translate(const QVector3D& dt) {
    dirty = true;
    position += dt;
}

void Camera::rotate(const QQuaternion& dr) {
    dirty = true;
    rotation = dr * rotation;
}

// Transform To (Setters)
void Camera::setPosition(const QVector3D& t) {
    dirty = true;
    position = t;
}

void Camera::setRotation(const QQuaternion& r) {
    dirty = true;
    rotation = r;
}

void Camera::setProjection(double fov, double ratio, double near, double far) {
    projection.setToIdentity();
    projection.perspective(fov, ratio, near, far);
}

void Camera::setMode(Mode newMode) {
    mode = newMode;
}

// Accessors
const QMatrix4x4& Camera::getMatrix() {
    if (dirty) {
        view.setToIdentity();

        // Switching modes is simply order of operations
        // TODO: switch mode
        view.rotate(rotation.conjugated());
        view.translate(position);

        world = projection * view;
        dirty = false;
    }
    return world;
}

// Queries
QVector3D Camera::forward() const {
    return rotation.rotatedVector(LocalForward);
}

QVector3D Camera::right() const {
    return rotation.rotatedVector(LocalRight);
}

QVector3D Camera::up() const {
    return rotation.rotatedVector(LocalUp);
}