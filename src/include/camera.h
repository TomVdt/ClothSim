#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>


class Camera {
public:
    enum Mode {
        FPS,
        Gimbal
    };

private:
    QVector3D position;
    QQuaternion rotation;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 world;
    bool dirty;
    Mode mode;

public:

    // Constants
    static const QVector3D LocalForward;
    static const QVector3D LocalUp;
    static const QVector3D LocalRight;

    // Constructors
    Camera();
    Camera(double fov, double ratio, double near, double far);

    // Transform By (Add/Scale)
    void translate(const QVector3D& dt);
    void translate(double dx, double dy, double dz) { translate(QVector3D(dx, dy, dz)); }
    void rotate(const QQuaternion& dr);
    void rotate(double angle, const QVector3D& axis) { rotate(QQuaternion::fromAxisAndAngle(axis, angle)); }
    void rotate(double angle, double ax, double ay, double az) { rotate(angle, QVector3D(ax, ay, az)); }

    // Transform To (Setters)
    void setPosition(const QVector3D& t);
    void setPosition(double x, double y, double z) { setPosition(QVector3D(x, y, z)); }
    void setRotation(const QQuaternion& r);
    void setRotation(double angle, const QVector3D& axis) { setRotation(QQuaternion::fromAxisAndAngle(axis, angle)); }
    void setRotation(double angle, double ax, double ay, double az) { setRotation(angle, QVector3D(ax, ay, az)); }
    void setProjection(double fov, double ratio, double near, double far);

    void setMode(Mode newMode);

    // Accessors
    const QVector3D& getTranslation() const { return position; }
    const QQuaternion& getRotation() const { return rotation; }
    const QMatrix4x4& getMatrix();

    // Queries
    QVector3D forward() const;
    QVector3D right() const;
    QVector3D up() const;
};
