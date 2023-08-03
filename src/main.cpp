#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

#include <iostream>
#include <opengl/glfw.hpp>
#include <opengl/mesh.hpp>
#include <opengl/shader.hpp>
#include <thread>
#include <vector>

int main() {
    auto window = GLFW::WindowWrapper::createWindow(800, 600, "Hello World");
    auto shader =
        Shader::createShader("shader/vertex.glsl", "shader/fragment.glsl");
    window->mainLoop([&]() {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
}
