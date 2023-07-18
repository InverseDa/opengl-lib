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
  auto triangle = Triangle::createTriangle(
      std::vector<glm::vec3>{glm::vec3(-0.5f, -0.5f, 0.0f),
                             glm::vec3(0.5f, -0.5f, 0.0f),
                             glm::vec3(0.0f, 0.5f, 0.0f)},
      std::vector<glm::vec3>{
          glm::vec3(1.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 1.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f),
      });

  auto quad =
      Quad::createQuad(std::vector<glm::vec3>{glm::vec3(-0.5f, -0.5f, 0.0f),
                                              glm::vec3(0.5f, -0.5f, 0.0f),
                                              glm::vec3(0.5f, 0.5f, 0.0f),
                                              glm::vec3(-0.5f, 0.5f, 0.0f)},
                       std::vector<glm::vec3>{
                           glm::vec3(1.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f),
                           glm::vec3(0.0f, 0.0f, 1.0f),
                           glm::vec3(1.0f, 1.0f, 1.0f),
                       });

  auto cube = Cube::createCube(
      std::vector<glm::vec3>{
          glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f),
          glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
          glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f),
          glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f)},
      std::vector<glm::vec3>{
          glm::vec3(1.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 1.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3(1.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 1.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
      });
  window->mainLoop([&]() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    quad->draw(*shader);
  });
}
