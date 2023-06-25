#include <iostream>
#include <opengl/glfw.hpp>
#include <opengl/input.hpp>
#include <thread>

int main() {
  auto window =
      GLFW::WindowWrapper::createWindow(800, 600, "window 1", 4, 3, Type::CORE);
  window->makeContextCurrent();
  auto window2 = GLFW::WindowWrapper::createWindow(1980, 1080, "window 2", 3, 3,
                                                   Type::CORE);
  window2->makeContextCurrent();

  std::thread thread([&]() {
    window->setKeyCallback(
        [](GLFWwindow *window, int key, int scancode, int action, int mods) {
          if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
          }
        });
    window->mainLoop([]() {
      glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
    });
  });

  std::thread thread2([&]() {
    window2->mainLoop([]() {
      glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
    });
  });

  thread.join();
  thread2.join();
}
