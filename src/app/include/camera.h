#pragma once

#include <cmath>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
private:
    /**
     * Camera settings
    */

    /**
     * Angle de vue par défaut
    */
    static constexpr double CAMERA_FOV = 60.0 * M_PI / 180.0;

    /**
     * Rapport largeur / hauteur par defaut
    */
    static constexpr double CAMERA_RATIO = 1.0;

    /**
     * Rapprochement maximal par defaut
    */
    static constexpr double CAMERA_NEAR = 0.1;

    /**
     * Éloignement maximal par defaut
    */
    static constexpr double CAMERA_FAR = 1000.0;

    /**
     * Angle de vue
    */
    double fov;

    /**
     * Rapport largeur / hauteur
    */
    double ratio;

    /**
     * Rapprochement maximal
    */
    double near;

    /**
     * Éloignement maximal
    */
    double far;

    /**
     * Position
    */
    glm::vec3 position;

    /**
     * Rotation selon l'axe gauche - droite
    */
    float pitch;

    /**
     * Rotation selon l'axe haut - bas
    */
    float yaw;

    /**
     * Rotation selon l'axe devant - derrière
    */
    float roll;

    /**
     * Matrice de projection
    */
    glm::mat4x4 projection;

    /**
     * Matrice de transformation translation + rotation
    */
    glm::mat4x4 view;

    /**
     * Matrice combinée projection * transformation
    */
    glm::mat4x4 world;

    /**
     * Marque s'il faut mettre à jour la matrice "world"
    */
    bool dirty;

    /**
     * Limite les angles à des valeurs cohérentes
    */
    void constrainAngles();

    /**
     * Met à jour la matrice de projection
    */
    void updateProjection();

public:
    /**
     * Crée une caméra avec les valeurs par défaut
    */
    Camera();

    /**
     * Crée une caméra avec une projection perspective définie par les paramètres donnés
    */
    Camera(double fov, double ratio, double near, double far);

    /**
     * Déplace la caméra
    */
    void translate(const glm::vec3& dt);

    /**
     * Déplace la caméra
    */
    void translate(double dx, double dy, double dz) { translate(glm::vec3(dx, dy, dz)); }
    
    /**
     * Tourne la caméra
    */
    void rotate(double dp, double dy, double dr);

    /**
     * Met la position de la caméra
    */
    void setPosition(const glm::vec3& t);

    /**
     * Met la position de la caméra
    */
    void setPosition(double x, double y, double z) { setPosition(glm::vec3(x, y, z)); }
    
    /**
     * Met la rotation de la caméra
    */
    void setRotation(double p, double y, double r);

    /**
     * Met le pitch (tangage) de la caméra
    */
    void setPitch(double p) { pitch = p; }

    /**
     * Met le yaw (lacet) de la caméra
    */
    void setYaw(double y) { yaw = y; }

    /**
     * Met le roll (roulis) de la caméra
    */
    void setRoll(double r) { roll = r; }

    /**
     * Met l'angle de vue de la caméra
    */
    void setFov(double fov);

    /**
     * Met le rapport largeur / hauteur de la caméra
    */
    void setAspect(double ratio);

    /**
     * Position de la caméra
    */
    const glm::vec3& getPosition() const { return position; }

    /**
     * Pitch (tangage) de la caméra
    */
    double getPitch() const { return pitch; }

    /**
     * Yaw (lacet) de la caméra
    */
    double getYaw() const { return yaw; }

    /**
     * Roll (roulis) de la caméra
    */
    double getRoll() const { return roll; }

    /**
     * Angle de vue de la caméra
    */
    double getFov() const { return fov; }

    /**
     * Rapport largeur / heuteur de la caméra
    */
    double getAspect() const { return ratio; }

    /**
     * Matrice projection * transformation associée à la caméra
    */
    const glm::mat4x4& getMatrix();

    // Queries
    // With help from https://stackoverflow.com/questions/1568568/how-to-convert-euler-angles-to-directional-vector
    
    /**
     * Vecteur avant de la caméra
    */
    glm::vec3 forward() const;

    /**
     * Vecteur avant sur un plan horizontal de la caméra
    */
    glm::vec3 horizontalForward() const;

    /**
     * Vecteur droite de la caméra
    */
    glm::vec3 right() const;

    /**
     * Vecteur droite sur un plan horizontal de la caméra
    */
    glm::vec3 horizontalRight() const;

    /**
     * Vecteur haut de la caméra
    */
    glm::vec3 up() const;

    /**
     * Vecteur haut sur un plan horizontal de la caméra (constant)
    */
    glm::vec3 horizontalUp() const;
};
