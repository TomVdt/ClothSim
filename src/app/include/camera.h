#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 position;
    float pitch;
    float yaw;
    float roll;

    glm::mat4x4 projection;
    glm::mat4x4 view;
    glm::mat4x4 world;
    bool dirty;

public:
    // Constructors
    Camera();
    Camera(double fov, double ratio, double near, double far);

    // Transform By (Add/Scale)

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
    void setProjection(const glm::mat4x4& proj);

    // Accessors
    const glm::vec3& getPosition() const { return position; }
    double getPitch() const { return pitch; }
    double getYaw() const { return yaw; }
    double getRoll() const { return roll; }
    const glm::mat4x4& getMatrix();

    // Queries
    glm::vec3 forward() const;
    glm::vec3 right() const;
    glm::vec3 up() const;
};
