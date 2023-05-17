#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <cmath>

class Camera {
private:
    /**
     * Camera settings
    */
    static constexpr double CAMERA_FOV = 60.0 * M_PI / 180.0;
    static constexpr double CAMERA_RATIO = 1.0;
    static constexpr double CAMERA_NEAR = 0.1;
    static constexpr double CAMERA_FAR = 1000.0;

    double fov;
    double ratio;
    double near;
    double far;

    glm::vec3 position;
    float pitch;
    float yaw;
    float roll;

    glm::mat4x4 projection;
    glm::mat4x4 view;
    glm::mat4x4 world;
    bool dirty;

    void constrainAngles();

    void updateProjection();

public:
    // Constructors
    Camera();
    Camera(double fov, double ratio, double near, double far);

    /**
     * Move camera
    */

    void translate(const glm::vec3& dt);
    void translate(double dx, double dy, double dz) { translate(glm::vec3(dx, dy, dz)); }
    void rotate(double dp, double dy, double dr);

    // Transform To (Setters)
    void setPosition(const glm::vec3& t);
    void setPosition(double x, double y, double z) { setPosition(glm::vec3(x, y, z)); }
    void setRotation(double p, double y, double r);
    void setPitch(double p) { pitch = p; }
    void setYaw(double y) { yaw = y; }
    void setRoll(double r) { roll = r; }
    void setFov(double fov);
    void setAspect(double ratio);

    // Accessors
    const glm::vec3& getPosition() const { return position; }
    double getPitch() const { return pitch; }
    double getYaw() const { return yaw; }
    double getRoll() const { return roll; }
    double getFov() const { return fov; }
    double getAspect() const { return ratio; }
    const glm::mat4x4& getMatrix();

    // Queries
    // With help from https://stackoverflow.com/questions/1568568/how-to-convert-euler-angles-to-directional-vector
    glm::vec3 forward() const;
    glm::vec3 horizontalForward() const;
    glm::vec3 right() const;
    glm::vec3 horizontalRight() const;
    glm::vec3 up() const;
    glm::vec3 horizontalUp() const;
};
