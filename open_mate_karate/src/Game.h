#ifndef GAME_H
#define GAME_H

#include "libs.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture2D.h"

class Game
{
public:
    static void setFramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void setScrollCallback(GLFWwindow* window, double deltaX, double deltaY);

    Game
    (
        const std::string& title,
        const int width,
        const int height,
        const int versionMajor,
        const int versionMinor,
        bool fullscreen,
        bool resizable
    );
    virtual ~Game();

    void run();

    void showFps();

private:
    const std::string WINDOW_TITLE;
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const int VERSION_MAJOR;
    const int VERSION_MINOR;
    const bool FULLSCREEN;
    const bool RESIZABLE;
    const double ZOOM_SENSITIVITY;
    const float CAMERA_MOVE_SPEED;
    const float MOUSE_SENSITIVITY;

    GLFWwindow* window;
    int framebufferWidth;
    int framebufferHeight;
    bool wireframe;
    bool flashlightOn;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    Camera camera;

    std::vector<glm::vec3> modelsPositions;
    std::vector<glm::vec3> modelsScales;
    std::vector<Mesh> meshes;
    std::vector<Texture2D> textures;

    ShaderProgram basicShader;

    void initGlfw();
    void initWindow();
    void initGlew();
    void initOpenGlOptions();

    void update(double deltaTime);
    void render();
};

#endif // GAME_H