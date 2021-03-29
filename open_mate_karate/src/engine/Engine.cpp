#include "Engine.h"

void Engine::setFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    //windowWidth = width;
    //windowHeight = height;

    glViewport(0, 0, width, height);
}

void Engine::setScrollCallback(GLFWwindow* window, double deltaX, double deltaY)
{
    //double fieldOfView { camera.getFieldOfView() + deltaY * ZOOM_SENSITIVITY };
    //fieldOfView = glm::clamp(fieldOfView, 1.0, 120.0);

    //camera.setFieldOfView((float)fieldOfView);
}

Engine::Engine
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
      ZOOM_SENSITIVITY(-3.0),
      CAMERA_MOVE_SPEED(5.0f),
      MOUSE_SENSITIVITY(0.1f),
      window(nullptr),
      framebufferWidth(WINDOW_WIDTH),
      framebufferHeight(WINDOW_HEIGHT),
      wireframe(false),
      flashlightOn(true),
      model(1.0f),
      view(1.0f),
      projection(1.0f),
      camera(glm::vec3(0.0f, 3.0f, 10.0f)),
      meshes(),
      textures(),
      materials(),
      models(),
      basicShader()
{
    initGlfw();
    initWindow();
    initGlew();
    initOpenGlOptions();
}

Engine::~Engine()
{
    for (size_t i { 0 }; i < models.size(); i++)
    {
        delete models[i];
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::run()
{
    // SHADER PROGRAM
    basicShader.loadShaders("shaders/basic_dir.vert", "shaders/basic_dir.frag");

    // MATERIALS
    Material material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.5f), 0, 0, 150.0f);
    materials.push_back(material);
    materials.push_back(material);
    materials.push_back(material);
    materials.push_back(material);
    materials.push_back(material);
    materials.push_back(material);
    materials.push_back(material);

    // LOAD MESHES AND TEXTURES
    meshes.resize(7);
    textures.resize(7);

    meshes[0].loadObj("models/crate.obj");
    meshes[1].loadObj("models/woodcrate.obj");
    meshes[2].loadObj("models/robot.obj");
    meshes[3].loadObj("models/floor.obj");
    meshes[4].loadObj("models/bowling_pin.obj");
    meshes[5].loadObj("models/bunny.obj");
    meshes[6].loadObj("models/lampPost.obj");

    textures[0].loadTexture("textures/crate_diffuse.jpg", true);
    textures[1].loadTexture("textures/woodcrate_diffuse.jpg", true);
    textures[2].loadTexture("textures/robot_diffuse.jpg", true);
    textures[3].loadTexture("textures/tile_floor.jpg", true);
    textures[4].loadTexture("textures/AMF.jpg", true);
    textures[5].loadTexture("textures/bunny_diffuse.jpg", true);
    textures[6].loadTexture("textures/lamp_post_diffuse.png", true);

    models.push_back(new Model(&materials[0], &textures[0], &textures[0], &meshes[0], glm::vec3(-3.5f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))); // CRATE 1
    models.push_back(new Model(&materials[1], &textures[1], &textures[1], &meshes[1], glm::vec3(3.5f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))); // CRATE 2
    models.push_back(new Model(&materials[2], &textures[2], &textures[2], &meshes[2], glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))); // ROBOT
    models.push_back(new Model(&materials[3], &textures[3], &textures[3], &meshes[3], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(10.0f, 1.0f, 10.0f))); // FLOOR
    models.push_back(new Model(&materials[4], &textures[4], &textures[4], &meshes[4], glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(1.0f), glm::vec3(0.1f, 0.1f, 0.1f))); // PIN
    models.push_back(new Model(&materials[5], &textures[5], &textures[5], &meshes[5], glm::vec3(-2.0f, 0.0f, 2.0f), glm::vec3(1.0f), glm::vec3(0.7f, 0.7f, 0.7f))); // BUNNY
    models.push_back(new Model(&materials[6], &textures[6], &textures[6], &meshes[6], glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))); // LAMP POST

    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    double lastTime { glfwGetTime() };

    while (!glfwWindowShouldClose(window))
    {
        showFps();

        double currentTime { glfwGetTime() };
        double deltaTime { currentTime - lastTime };

        glfwPollEvents();

        update(deltaTime);
        render();

        lastTime = currentTime;
    }
}

void Engine::showFps()
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
        outs << std::fixed << WINDOW_TITLE << " (FPS: " << fps << ", frame time: " << msPerFrame << " ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;
    }

    frameCount++;
}

void Engine::initGlfw()
{
    if (!glfwInit())
    {
        std::cerr << "Error! Failed to GLFW initialization!" << std::endl;
        glfwTerminate();
    }
}

void Engine::initWindow()
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, RESIZABLE);

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

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, setFramebufferSizeCallback);
    glfwSetScrollCallback(window, setScrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, framebufferWidth / 2.0f, framebufferHeight / 2.0);
}

void Engine::initGlew()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error! Failed to GLEW initialization!" << std::endl;
        glfwTerminate();
    }
}

void Engine::initOpenGlOptions()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Engine::update(double deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
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

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        flashlightOn = !flashlightOn;
    }

    double mouseX { 0.0 };
    double mouseY { 0.0 };

    glfwGetCursorPos(window, &mouseX, &mouseY);

    float yaw { static_cast<float>(framebufferWidth / 2 - mouseX) * MOUSE_SENSITIVITY };
    float pitch { static_cast<float>(framebufferHeight / 2 - mouseY) * MOUSE_SENSITIVITY };

    camera.rotate(yaw, pitch);

    glfwSetCursorPos(window, framebufferWidth / 2.0, framebufferHeight / 2.0);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.move(CAMERA_MOVE_SPEED * (float)deltaTime * camera.getLook());
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.move(CAMERA_MOVE_SPEED * (float)deltaTime * -camera.getLook());
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.move(CAMERA_MOVE_SPEED * (float)deltaTime * -camera.getRight());
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.move(CAMERA_MOVE_SPEED * (float)deltaTime * camera.getRight());
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.move(CAMERA_MOVE_SPEED * (float)deltaTime * -camera.getUp());
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.move(CAMERA_MOVE_SPEED * (float)deltaTime * camera.getUp());
    }
}

void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = camera.getViewMatrix();
    projection = glm::perspective(glm::radians(camera.getFieldOfView()), static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight), 0.1f, 100.0f);

    glm::vec3 viewPos {camera.getPos() };

    glm::vec3 lightPos = camera.getPos();
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    lightPos.y -= 0.5f;

    basicShader.use();

    basicShader.setUniform("view", view);
    basicShader.setUniform("projection", projection);
    basicShader.setUniform("viewPos", viewPos);

    basicShader.setUniform("light.dir", glm::vec3(-0.5f, -1.0f, -0.5f));
    basicShader.setUniform("light.ambient", glm::vec3(1.0f));
    basicShader.setUniform("light.diffuse", lightColor);
    basicShader.setUniform("light.specular", glm::vec3(1.0f));

    for (size_t i { 0 }; i < models.size(); i++)
    {
        models[i]->update();
        models[i]->render(basicShader);
    }

    glfwSwapBuffers(window);
    glFlush();
}