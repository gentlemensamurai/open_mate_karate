#ifndef GAME_H
#define GAME_H

#include "libs.h"

class Game
{
public:
    static void setFramebufferSizeCallback(GLFWwindow* window, int width, int height);

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

    void update();
    void render();
    int getWindowShouldClose();
    void setWindowShouldClose();

private:
    const std::string WINDOW_TITLE;
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const int VERSION_MAJOR;
    const int VERSION_MINOR;
    const bool FULLSCREEN;
    const bool RESIZABLE;

    GLFWwindow* window;
    int framebufferWidth;
    int framebufferHeight;

    void initGlfw();
    void initWindow();
    void initGlew();
    void initOpenGlOptions();
};

#endif // GAME_H