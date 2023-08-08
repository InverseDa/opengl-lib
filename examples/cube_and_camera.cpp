#include "opengl/camera.hpp"
#include "opengl/glfw.hpp"
#include "opengl/mesh.hpp"
#include "opengl/shader.hpp"
#include <vector>

auto camera = Camera::createCamera();
bool firstMouse = true;
double lastX = 400, lastY = 300;
double deltaTime = 0, lastFrame = 0;

void keyProcess(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(RIGHT, deltaTime);
}

void mouseMovementProcess(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera->processMouseMovement(xOffset, yOffset);
}

void mouseScrollProcess(GLFWwindow* window, double xoffset, double yoffset) {
    camera->processMouseScroll(yoffset);
}

int main() {
    auto window = WindowWrapper::createWindow(800, 600, "Hello World");
    auto shader = Shader::createShader("shader/vertex.glsl", "shader/fragment.glsl");

    auto cube = Cube::createCube(
        std::vector<glm::vec3>{
            glm::vec3(-0.5f, -0.5f, -0.5f), // 0
            glm::vec3(0.5f, -0.5f, -0.5f),  // 1
            glm::vec3(0.5f, 0.5f, -0.5f),   // 2
            glm::vec3(-0.5f, 0.5f, -0.5f),  // 3
            glm::vec3(-0.5f, -0.5f, 0.5f),  // 4
            glm::vec3(0.5f, -0.5f, 0.5f),   // 5
            glm::vec3(0.5f, 0.5f, 0.5f),    // 6
            glm::vec3(-0.5f, 0.5f, 0.5f),   // 7
        },
        std::vector<glm::vec3>{
            glm::vec3(1.0f, 0.0f, 0.0f), // 0
            glm::vec3(0.0f, 1.0f, 0.0f), // 1
            glm::vec3(0.0f, 0.0f, 1.0f), // 2
            glm::vec3(1.0f, 1.0f, 0.0f), // 3
            glm::vec3(1.0f, 0.0f, 1.0f), // 4
            glm::vec3(0.0f, 1.0f, 1.0f), // 5
            glm::vec3(1.0f, 1.0f, 1.0f), // 6
            glm::vec3(0.0f, 0.0f, 0.0f), // 7
        });

    window->setMouseButtonCallback(
        [](GLFWwindow* window, int button, int action, int mods) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                std::cout << "Mouse position: " << xpos << ", " << ypos
                          << std::endl;
            }
        });
    window->setScrollCallback(
        [](GLFWwindow* window, double xoffset, double yoffset) {
            std::cout << "Scroll offset: " << xoffset << ", " << yoffset
                      << std::endl;
        });
    window->setCursorPosCallback(mouseMovementProcess);
    window->setScrollCallback(mouseScrollProcess);
    window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    auto model = glm::scale(glm::mat4(1.f), glm::vec3(3.f));
    glEnable(GL_DEPTH_TEST);

    window->mainLoop([&]() {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        auto projection = glm::perspective(
            glm::radians(camera->getFov()),
            static_cast<float>(window->getWidth()) / window->getHeight(),
            0.1f,
            100.0f);
        keyProcess(window->get());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->setMatrix4("model", model);
        shader->setMatrix4("projection", projection);
        shader->setMatrix4("view", camera->getViewMatrix());
        cube->draw(*shader);
    });
}
