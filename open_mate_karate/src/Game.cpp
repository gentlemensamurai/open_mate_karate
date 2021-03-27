#include "Game.h"

void Game::setFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    //windowWidth = width;
    //windowHeight = height;

    glViewport(0, 0, width, height);
}

Game::Game
(
    const std::string& title,
    const int width,
    const int height,
    const int versionMajor,
    const int versionMinor,
    bool fullscreen,
    bool resizable
)
    : WINDOW_TITLE(title),
      WINDOW_WIDTH(width),
      WINDOW_HEIGHT(height),
      VERSION_MAJOR(versionMajor),
      VERSION_MINOR(versionMinor),
      FULLSCREEN(fullscreen),
      RESIZABLE(resizable),
      window(nullptr),
      framebufferWidth(WINDOW_WIDTH),
      framebufferHeight(WINDOW_HEIGHT)
{
    initGlfw();
    initWindow();
    initGlew();
    initOpenGlOptions();
}

Game::~Game()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::update()
{

}

void Game::render()
{

}

void Game::initGlfw()
{
    if (!glfwInit())
    {
        std::cerr << "Error! Failed to GLFW initialization!" << std::endl;
        glfwTerminate();
    }
}

void Game::initWindow()
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, RESIZABLE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE); CHECK IT

    if (!FULLSCREEN)
    {
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), nullptr, nullptr);
    }
    else
    {
        GLFWmonitor* monitor { glfwGetPrimaryMonitor() };
        const GLFWvidmode* vidmode { glfwGetVideoMode(monitor) };

        if (vidmode != nullptr)
        {
            framebufferWidth = vidmode->width;
            framebufferHeight = vidmode->height;
            window = glfwCreateWindow(framebufferWidth, framebufferHeight, WINDOW_TITLE.c_str(), monitor, nullptr);
        }
    }

    if (window == nullptr)
    {
        std::cerr << "Error! Failed to create window!" << std::endl;
        glfwTerminate();
    }

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glfwSetFramebufferSizeCallback(window, setFramebufferSizeCallback);

    glfwMakeContextCurrent(window);
}

void Game::initGlew()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error! Failed to GLEW initialization!" << std::endl;
        glfwTerminate();
    }
}

void Game::initOpenGlOptions()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
    //glViewport(0, 0, windowWidth, windowHeight);
    
}