#pragma once
#include "include/openglrenderer.h"
#include "include/system.h"
#include "include/integrator.h"

#include "GLFW/glfw3.h"
#include <memory>

class Window {
private:
    /**
     * Renderer
    */
    OpenGLRenderer renderer;
    
    /**
     * Système à dessiner et simuler
    */
    System system;

    /**
     * Intégrateur utilisé pour faire avancer le système
    */
    std::unique_ptr<Integrator> physicsIntegrator;

    /**
     * Fenetre GLFW
    */
    GLFWwindow* window;

    /**
     * Controle le mode pause
    */
    bool paused;

    /**
     * Controle le dessinage du rèpere
    */
    bool drawAxis;

    /**
     * Temps d'intégration
    */
    float deltaTime;

    /**
     * Nombre d'intégrations du système par frame
    */
    int iterationsPerFrame;

    /**
     * Pour GLFW: indique s'il faut changer la taille de la fenetre
    */
    static bool needsResize;

    /**
     * Initialise entièrement la fenetre
    */
    void init();

    /**
     * Initialise GLFW
    */
    void initGLFW();

    /**
     * Crée la fenetre GLFW
    */
    void createWindow();

    /**
     * Initialise les commandes OpenGL
    */
    void initOpenGL();

    /**
     * Initialise ImGui
    */
    void initImGui();

    /**
     * Supprime la fenetre et désactive le renderer
     * Ne peut pas être mis dans le destructeur car on n'est pas garanti
     * que la fenetre a été créée
    */
    void deinit();

    /**
     * Met à jour le point de vue du renderer et avance le système
    */
    void update();

    /**
     * Dessine le système
    */
    void render();

public:
    /**
     * Crée une fenetre avec optionnellement un système à dessiner et simuler
    */
    Window(System&& system = System());
    
    /**
     * Destructeur virtual, par défaut (en cas d'héritage)
    */
    virtual ~Window() = default;

    /**
     * Nécessaire pour GLFW, qui n'est pas une librairie orientée objet
    */
    static void fbResizeCallback(GLFWwindow* window, int width, int height);

    /**
     * Donne un système à dessiner et simuler à la fenetre
    */
    void setSystem(System&& sys);

    /**
     * Boucle principale: active la fenetre et lance la boucle de simulation et dessin
    */
    void run();
};
