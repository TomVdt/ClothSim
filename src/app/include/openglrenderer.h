#include "include/renderer.h"
#include "include/camera.h"
#include "include/shaderprogram.h"
#include "include/vertexarray.h"
#include "include/buffer.h"

#include <GL/glew.h>

class Vector3D;

class OpenGLRenderer: public Renderer {
private:
    /**
     * OpenGL shader program
    */
    ShaderProgram program;
    
    /**
     * Vertex buffer
    */
    Buffer vbo;

    /**
     * Vertex index buffer
    */
    Buffer ebo;

    /**
     * Vertex array pour contenir le vbo et vao
    */
    VertexArray vao;

    /**
     * Identifiant OpenGL pour mettre la position
    */
    GLuint vertexLocation;

    /**
     * Identifiant OpenGL pour mettre la couleur
    */
    GLuint colorLocation;

    /**
     * Identifiant OpenGL pour mettre la projection
    */
    GLuint projectionViewMatrixLocation;

    /**
     * Identifiant OpenGL pour mettre la transformation
    */
    GLuint modelMatrixLocation;

    /**
     * Indice dans le vbo d'une ligne
    */
    int offsetLine;

    /**
     * Indice dans le vbo d'un cube
    */
    int offsetCube;

    /**
     * Indice dans le vbo d'une sphère
    */
    int offsetSphere;

    /**
     * Indice de départ pour le dessin d'une ligne
    */
    int indexLine;

    /**
     * Indice de départ pour le dessin d'un cube
    */
    int indexCube;

    /**
     * Indice de départ pour le dessin d'une sphère
    */
    int indexSphere;

    /**
     * Camera, controle le point de vue et la projection
    */
    Camera camera;

    /**
     * Vitesse de déplacement de la caméra
    */
    constexpr static double cameraMoveSpeed = 15.0;

    /**
     * Vitesse de rotation de la caméra
    */
    constexpr static double cameraRotateSpeed = 0.005;

    /**
     * Couleur des masses
    */
    glm::vec4 massColor;

    /**
     * Taille des masses
    */
    float massScale;

    /**
     * Activer le dessin des masses?
    */
    bool drawMasses;

    /**
     * Activer le dessin des vecteurs vitesse?
    */
    bool drawSpeedVectors;

    /**
     * Activer le dessin des ressorts?
    */
    bool drawSprings;

    /**
     * Nombre de frames depuis le début du programme
    */
    int frameCount;

public:
    /**
     * Constructeur
     * Initialise les attributs et la camera
    */
    OpenGLRenderer();

    /**
     * On ne veut pas de copie de renderer
    */
    OpenGLRenderer(const Renderer&) = delete;

    /**
     * On ne veut pas de copie de renderer
    */
    OpenGLRenderer& operator=(const Renderer&) = delete;

    /**
     * On peut déplacer un renderer
    */
    OpenGLRenderer(OpenGLRenderer&&) = default;

    /**
     * On peut déplacer un renderer
    */
    OpenGLRenderer& operator=(OpenGLRenderer&&) = default;

    /**
     * Destructeur virtuel par defaut
    */
    virtual ~OpenGLRenderer() = default;

    /**
     * Initialise OpenGL: options, shaders, géométrie
    */
    void init();

    /**
     * Met à jour le viewport et la projection
    */
    void resize(int, int);

    /**
     * Efface la frame précédente
    */
    void clear();

    /**
     * Réinitialise la position de la caméra
    */
    void reset();

    /**
     * Active le renderer pour dessiner
    */
    void beginFrame();

    /**
     * Désactive le mode dessin
    */
    void endFrame();

    /**
     * Supprime les éléments OpenGL créés
    */
    void deinit();

    /**
     * Déplace la caméra en fonction des entrées de l'utilisateur
    */
    void update(double dt);

    /**
     * Position de la camera
    */
    const glm::vec3& getPosition() const { return camera.getPosition(); }

    /**
     * Rotation (angles d'euler, pitch yaw roll) de la caméra
    */
    glm::vec3 getRotation() const { return glm::vec3(camera.getPitch(), camera.getYaw(), camera.getRoll()); }

    /**
     * Dessine une masse
    */
    virtual void draw(const Masse&) override;
    
    /**
     * Dessine un ressort
    */
    virtual void draw(const Spring&) override;
    
    /**
     * Dessine un tissu
    */
    virtual void draw(const Cloth&) override;
    
    /**
     * Dessine un système
    */
    virtual void draw(const System&) override;

    /**
     * Dessine les controles ImGui du renderer
    */
    void drawControls();

    /**
     * Dessine une ligne
    */
    void drawLine(const Vector3D& pos1, const Vector3D& pos2, const glm::vec4& color = glm::vec4(1.0));
    
    /**
     * Dessine un cube
    */
    void drawCube(const Vector3D& pos, const Vector3D& scale, const glm::vec4& color = glm::vec4(1.0));

    /**
     * Dessine une sphère
    */
    void drawSphere(const Vector3D& pos, const Vector3D& scale, const glm::vec4& color = glm::vec4(1.0));

    /**
     * Dessine le repère à (0, 0, 0)
    */
    void drawAxis();
};
