#include "libs.h"
#include "ShaderProgram.h"

const char* TITLE { "Open Mate Karate" };
const int WINDOW_WIDTH { 800 };
const int WINDOW_HIGHT { 600 };
const bool fullscreen { false };

GLFWwindow* window { nullptr };
bool wireframe { false };

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
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
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLuint indices[]
    {
        0, 1, 2,
        0, 2, 3
    };

    GLuint vbo;
    GLuint ibo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // POSITION

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // SHADER PROGRAM

    ShaderProgram shaderProgram;
    shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

    // MAIN LOOP

    while (!glfwWindowShouldClose(window))
    {
        showFPS(window);

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();

        GLfloat time = glfwGetTime();
        GLfloat blueColor { (sin(time) / 2) + 0.5f };

        glm::vec2 posOffset;
        posOffset.x = sin(time) / 2;
        posOffset.y = cos(time) / 2;

        shaderProgram.setUniform("vertColor", glm::vec4(0.0f, 0.0f, blueColor, 1.0f));
        shaderProgram.setUniform("posOffset", posOffset);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if (!fullscreen)
    {
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HIGHT, TITLE, nullptr, nullptr);
    }
    else
    {
        GLFWmonitor* monitor { glfwGetPrimaryMonitor() };
        const GLFWvidmode* vidmode { glfwGetVideoMode(monitor) };

        if (vidmode != nullptr)
        {
            window = glfwCreateWindow(vidmode->width, vidmode->height, TITLE, monitor, nullptr);
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

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return false;
    }

    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

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
        outs << std::fixed << TITLE << " (FPS: " << fps << ", frame time: " << msPerFrame << " ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;
    }

    frameCount++;
}