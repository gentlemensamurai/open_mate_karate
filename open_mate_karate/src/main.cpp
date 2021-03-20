#include "libs.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "OrbitCamera.h"

constexpr bool fullscreen { false };
constexpr float mouseSensitivity { 0.25f };
const std::string windowTitle { "Open Mate Karate" };
const std::string texPathCrate { "textures/crate.jpg" };
const std::string texPathGrid { "textures/grid.jpg" };

int windowWidth { 1920 };
int windowHeight { 1080 };
GLFWwindow* window { nullptr };
bool wireframe { false };

OrbitCamera orbitCamera;
float yaw { 0.0f };
float pitch { 0.0f };
float radius { 10.0f };

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onMouseMove(GLFWwindow* window, double posX, double posY);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void showFPS(GLFWwindow* window);
bool init();

int main()
{
    if (!init())
    {
        std::cerr << "Initialization failed!" << std::endl;
        return -1;
    }

    GLfloat vertices[]
    {
         // POSITION         // TEXTURE COORDINATES

         // FRONT FACE
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

         // BACK FACE
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

         // LEFT FACE
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

         // RIGHT FACE
         1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

         // TOP FACE
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

         // BOTTOM FACE
        -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f
    };

    glm::vec3 cubePos { glm::vec3(0.0f, 0.0f, -5.0f) };

    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    // TEXTURE COORDINATES
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // SHADER PROGRAM
    ShaderProgram shaderProgram;
    shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

    Texture2D texCrate;
    texCrate.loadTexture(texPathCrate, true);

    //Texture2D texGrid;
    //texGrid.loadTexture(texPathGrid, true);

    float cubeAngle { 0.0f };
    double lastTime { glfwGetTime() };

    // MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {
        showFPS(window);

        double currentTime { glfwGetTime() };
        double deltaTime { currentTime - lastTime };

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texCrate.bind(0);
        //texLeaves.bind(1);

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);

        orbitCamera.setLookAt(cubePos);
        orbitCamera.rotate(yaw, pitch);
        orbitCamera.setRadius(radius);

        model = glm::translate(model, cubePos);
        view = orbitCamera.getViewMatrix();
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.f);

        shaderProgram.use();

        shaderProgram.setUniform("model", model);
        shaderProgram.setUniform("view", view);
        shaderProgram.setUniform("projection", projection);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);

        lastTime = currentTime;
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}

bool init()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

    if (!fullscreen)
    {
        window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
    }
    else
    {
        GLFWmonitor* monitor { glfwGetPrimaryMonitor() };
        const GLFWvidmode* vidmode { glfwGetVideoMode(monitor) };

        if (vidmode != nullptr)
        {
            window = glfwCreateWindow(vidmode->width, vidmode->height, windowTitle.c_str(), monitor, nullptr);
        }
    }

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, glfw_onKey);
    glfwSetCursorPosCallback(window, glfw_onMouseMove);
    glfwSetFramebufferSizeCallback(window, glfw_onFramebufferSize);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return false;
    }

    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        wireframe = !wireframe;

        if (wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

void glfw_onMouseMove(GLFWwindow* window, double posX, double posY)
{
    static glm::vec2 lastMousePos { glm::vec2(0.0f, 0.0f) };

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        yaw -= (static_cast<float>(posX) - lastMousePos.x) * mouseSensitivity;
        pitch += (static_cast<float>(posY) - lastMousePos.y) * mouseSensitivity;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        float dX { 0.01f * (static_cast<float>(posX) - lastMousePos.x) };
        float dY { 0.01f * (static_cast<float>(posY) - lastMousePos.y) };
        radius += dX - dY;
    }

    lastMousePos.x = static_cast<float>(posX);
    lastMousePos.y = static_cast<float>(posY);
}

void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, windowWidth, windowHeight);
}

void showFPS(GLFWwindow* window)
{
    static double previousSeconds { 0.0 };
    static int frameCount { 0 };

    double currentSeconds { glfwGetTime() };
    double elapsedSeconds { currentSeconds - previousSeconds };

    if (elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        double fps { static_cast<double>(frameCount) / elapsedSeconds };
        double msPerFrame { 1000.0 / fps };

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed << windowTitle << " (FPS: " << fps << ", frame time: " << msPerFrame << " ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;
    }

    frameCount++;
}