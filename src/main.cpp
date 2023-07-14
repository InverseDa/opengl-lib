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
  std::vector<Vertex> vertices = {
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
  };
  std::vector<GLuint> indices = {
      0,
      1,
      2,
  };
  std::vector<Texture> textures = {};

  window->mainLoop([&]() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  });
}
