#include <opengl/glfw.hpp>

int main() {
    auto window = WindowWrapper::createWindow(800, 600, "Hello World");
    window->mainLoop([&]() {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
}