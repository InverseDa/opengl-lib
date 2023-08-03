#include <opengl/camera.hpp>
#include <opengl/glfw.hpp>
#include <opengl/mesh.hpp>
#include <opengl/shader.hpp>
#include <vector>
auto camera = Camera::createCamera();

bool firstMouse = true;
double lastX = 400, lastY = 300;

void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(FORWARD, 0.015f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(BACKWARD, 0.015f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(LEFT, 0.015f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(RIGHT, 0.015f);
}

void mouse(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    //  注意方向问题
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xOffset, yOffset);
}

int main() {
    auto window = GLFW::WindowWrapper::createWindow(800, 600, "Hello World");
    auto shader =
        Shader::createShader("shader/vertex.glsl", "shader/fragment.glsl");
    auto triangle = Triangle::createTriangle(
        std::vector<glm::vec3>{
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(0.0f, 0.5f, 0.0f),
        },
        std::vector<glm::vec3>{
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
        });

    window->setKeyCallback(key);

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

    window->setCursorPosCallback(mouse);

    auto projection = glm::perspective(glm::radians(camera->getFov()),
                                       static_cast<float>(window->getWidth()) /
                                           window->getHeight(),
                                       0.1f,
                                       100.0f);
    auto model = glm::scale(glm::mat4(1.f), glm::vec3(3.f));

    glfwSetInputMode(window->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    window->mainLoop([&]() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader->setMatrix4("model", model);
        shader->setMatrix4("projection", projection);
        shader->setMatrix4("view", camera->getViewMatrix());
        triangle->draw(*shader);
    });
}
