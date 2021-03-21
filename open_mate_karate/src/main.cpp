#include "libs.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"

constexpr bool fullscreen { false };
constexpr double zoomSensitivity { -3.0 };
constexpr float moveSpeed { 5.0f };
constexpr float mouseSensitivity { 0.1f };
const std::string windowTitle { "Open Mate Karate" };

int windowWidth { 1920 };
int windowHeight { 1080 };
GLFWwindow* window { nullptr };
bool wireframe { false };

Camera camera(glm::vec3(0.0f, 3.0f, 10.0f));
float yaw { 0.0f };
float pitch { 0.0f };
float radius { 10.0f };

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void update(double deltaTime);
void showFPS(GLFWwindow* window);
bool init();

int main()
{
    if (!init())
    {
        std::cerr << "Initialization failed!" << std::endl;
        return -1;
    }

    // MODEL POSITION
    std::vector<glm::vec3> modelPos;
    modelPos.push_back(glm::vec3(-3.5f, 0.0f, 0.0f)); // CRATE 1
    modelPos.push_back(glm::vec3(3.5f, 0.0f, 0.0f)); // CRATE 2
    modelPos.push_back(glm::vec3(0.0f, 0.0f, -2.0f)); // ROBOT
    modelPos.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // FLOOR
    modelPos.push_back(glm::vec3(0.0f, 0.0f, 2.0f)); // PIN
    modelPos.push_back(glm::vec3(-2.0f, 0.0f, 2.0f)); // BUNNY

    // MODEL SCALE
    std::vector<glm::vec3> modelScale;
    modelScale.push_back(glm::vec3(1.0f, 1.0f, 1.0f)); // CRATE 1
    modelScale.push_back(glm::vec3(1.0f, 1.0f, 1.0f)); // CRATE 2
    modelScale.push_back(glm::vec3(1.0f, 1.0f, 1.0f)); // ROBOT
    modelScale.push_back(glm::vec3(10.0f, 1.0f, 10.0f)); // FLOOR
    modelScale.push_back(glm::vec3(0.1f, 0.1f, 0.1f)); // PIN
    modelScale.push_back(glm::vec3(0.7f, 0.7f, 0.7f)); // BUNNY

    // SHADER PROGRAM
    ShaderProgram basicShader;
    basicShader.loadShaders("shaders/basic.vert", "shaders/basic.frag");

    ShaderProgram lightShader;
    lightShader.loadShaders("shaders/light.vert", "shaders/light.frag");

    // LOAD MESHES AND TEXTURES
    const size_t modelsCount { 6 };
    std::vector<Mesh> meshes(modelsCount);
    std::vector<Texture2D> textures(modelsCount);

    meshes[0].loadObj("models/crate.obj");
    meshes[1].loadObj("models/woodcrate.obj");
    meshes[2].loadObj("models/robot.obj");
    meshes[3].loadObj("models/floor.obj");
    meshes[4].loadObj("models/bowling_pin.obj");
    meshes[5].loadObj("models/bunny.obj");

    textures[0].loadTexture("textures/crate_diffuse.jpg", true);
    textures[1].loadTexture("textures/woodcrate_diffuse.jpg", true);
    textures[2].loadTexture("textures/robot_diffuse.jpg", true);
    textures[3].loadTexture("textures/tile_floor.jpg", true);
    textures[4].loadTexture("textures/AMF.jpg", true);
    textures[5].loadTexture("textures/bunny_diffuse.jpg", true);

    Mesh lightMesh;
    lightMesh.loadObj("models/light.obj");

    double lastTime { glfwGetTime() };
    float lightAngle { 0.0f };

    // MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {
        showFPS(window);

        double currentTime { glfwGetTime() };
        double deltaTime { currentTime - lastTime };

        glfwPollEvents();
        update(deltaTime);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);

        view = camera.getViewMatrix();
        projection = glm::perspective(glm::radians(camera.getFieldOfView()), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);

        glm::vec3 lightPos(0.0f, 1.0f, 10.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        lightAngle += (float)deltaTime * 50.0f;
        lightPos.x = 8.0 * sinf(glm::radians(lightAngle));

        basicShader.use();

        basicShader.setUniform("view", view);
        basicShader.setUniform("projection", projection);
        basicShader.setUniform("lightColor", lightColor);
        basicShader.setUniform("lightPos", lightPos);

        for (size_t i { 0 }; i < modelsCount; i++)
        {
            model = glm::translate(glm::mat4(1.0f), modelPos[i]) * glm::scale(glm::mat4(1.0f), modelScale[i]);
            basicShader.setUniform("model", model);
            textures[i].bind(0);
            meshes[i].draw();
            textures[i].unbind(0);
        }

        model = glm::translate(glm::mat4(1.0f), lightPos);
        lightShader.use();
        lightShader.setUniform("lightColor", lightColor);
        lightShader.setUniform("model", model);
        lightShader.setUniform("view", view);
        lightShader.setUniform("projection", projection);
        lightMesh.draw();

        glfwSwapBuffers(window);
        lastTime = currentTime;
    }

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
            windowWidth = vidmode->width;
            windowHeight = vidmode->height;
            window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), monitor, nullptr);
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
    glfwSetScrollCallback(window, glfw_onMouseScroll);
    glfwSetFramebufferSizeCallback(window, glfw_onFramebufferSize);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, windowWidth / 2.0f, windowHeight / 2.0);

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

    if (key == GLFW_KEY_O && action == GLFW_PRESS)
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

void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
{
    double fieldOfView { camera.getFieldOfView() + deltaY * zoomSensitivity };
    fieldOfView = glm::clamp(fieldOfView, 1.0, 120.0);

    camera.setFieldOfView((float)fieldOfView);
}

void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, windowWidth, windowHeight);
}

void update(double deltaTime)
{
    double mouseX { 0.0 };
    double mouseY { 0.0 };

    glfwGetCursorPos(window, &mouseX, &mouseY);

    float yaw { static_cast<float>(windowWidth / 2 - mouseX) * mouseSensitivity };
    float pitch { static_cast<float>(windowHeight / 2 - mouseY) * mouseSensitivity };

    camera.rotate(yaw, pitch);

    glfwSetCursorPos(window, windowWidth / 2.0, windowHeight / 2.0);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.move(moveSpeed * (float)deltaTime * camera.getLook());
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.move(moveSpeed * (float)deltaTime * -camera.getLook());
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.move(moveSpeed * (float)deltaTime * -camera.getRight());
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.move(moveSpeed * (float)deltaTime * camera.getRight());
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.move(moveSpeed * (float)deltaTime * -camera.getUp());
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.move(moveSpeed * (float)deltaTime * camera.getUp());
    }
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