#include <opengl/glfw.hpp>
#include <opengl/mesh.hpp>
#include <opengl/shader.hpp>
#include <vector>

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
    window->mainLoop([&]() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        triangle->draw(*shader);
    });
}
