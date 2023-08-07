# opengl-lib
OpenGL-lib is a C++ library designed to streamline the development of OpenGL applications. It provides a wrapper around GLFW and GLAD, offering a set of user-friendly interfaces and functionalities that make graphics rendering with OpenGL easier and more efficient.

Here are the key features and capabilities of OpenGL-lib:

1. GLFW encapsulation: OpenGL-lib encapsulates the GLFW library to handle window management, user input, and event handling. By abstracting GLFW, it provides a simple yet powerful window management interface that makes creating and managing OpenGL windows more convenient.

2. GLAD encapsulation: OpenGL-lib utilizes GLAD (OpenGL Loader) to load and manage OpenGL function pointers. This simplifies the initialization and management of OpenGL functions across different platforms and environments, making it easier to leverage the various capabilities of OpenGL.

3. Simplified rendering pipeline: OpenGL-lib offers a set of high-level graphics rendering features that allow easy configuration of vertex data, textures, shaders, and rendering states. This enables developers to focus on implementing graphics effects without getting bogged down in low-level OpenGL details.

4. Built-in math library: OpenGL-lib includes a simple yet powerful math library for handling vectors, matrices, and common mathematical operations. This math library provides convenient functions and tools for geometric transformations, coordinate conversions, and mathematical computations.

5. Cross-platform support: With cross-platform support in mind, OpenGL-lib can be used on multiple operating systems, including Windows, Linux, and macOS. This allows developers to conveniently develop and deploy OpenGL applications across different platforms.

## Usage
### Linux
Unfortunately, we don't provide a pre-build library for Linux caused Linux has two display systems, 
X11 and Wayland. We can't provide a library that can be used in both systems. 
So you need to build it by yourself or use package manager(`apt`, `dnf`, `pacman`, etc). 

Prepare the environment:
`CMake`, `GCC`, `GLFW`, `GLAD`, `GLM`
#### Arch Linux
For X11 User:
```bash
sudo pacman -S glfw-x11 glad glm
```
For Wayland User:
```bash
sudo pacman -S glfw-wayland glad glm
```
Then in `CMakeLists.txt`, add the following lines between `if(LINUX) ... end(LINUX)`:
```cmake
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(glad REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw glm glad)
```
### Darwin
Prepare the environment:
`XCode Toolchain`

For MacOS User, we provide GLFW, GLAD and GLM, you can use it directly.
```bash
git clone https://github.com/InverseDa/opengl-lib.git
cd opengl-lib
cmake -S . -B build
cd build
make
```
### Windows
Prepare the environment:
`Visual Studio ToolChain`

For Windows User, we provide GLFW, GLAD and GLM, you can use it directly.
```bash
git clone https://github.com/InverseDa/opengl-lib.git
cd opengl-lib
cmake -S . -B build -G "Visual Studio 16 2019" -A x64
```
Then open `opengl-lib.sln` and build it.

## Examples

### Init GLFW window

```cpp
#include <opengl/glfw.hpp>

int main() {
    auto window = GLFW::WindowWrapper::createWindow(800, 600, "Hello World");
    window->mainLoop([&]() {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });
}
```
This will show a window with red color.
![window.png](img%2Fwindow.png)

### Draw a triangle

```cpp
#include <opengl/glfw.hpp>
#include <opengl/mesh.hpp>
#include <opengl/shader.hpp>
#include <vector>

const char* vsh = "#version 330 core\n"
                  "layout (location = 0) in vec3 aPos;\n"
                  "layout (location = 1) in vec3 aColor;\n"
                  "out vec3 ourColor;\n"
                  "void main()\n"
                  "{\n"
                  "   gl_Position = vec4(aPos, 1.0);\n"
                  "   ourColor = aColor;\n"
                  "}\0";

const char* fsh = "#version 330 core\n"
                  "out vec4 FragColor;\n"
                  "in vec3 ourColor;\n"
                  "void main()\n"
                  "{\n"
                  "   FragColor = vec4(ourColor, 1.0f);\n"
                  "}\0";

int main() {
    auto window = GLFW::WindowWrapper::createWindow(800, 600, "Triangle");
    auto shader = Shader::createShader(vsh, fsh);
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
```
![triangle.png](img%2Ftriangle.png)

### Draw a rectangle

```cpp
#include <opengl/glfw.hpp>
#include <opengl/mesh.hpp>
#include <opengl/shader.hpp>
#include <vector>

const char* vsh = "#version 330 core\n"
                  "layout (location = 0) in vec3 aPos;\n"
                  "layout (location = 1) in vec3 aColor;\n"
                  "out vec3 ourColor;\n"
                  "void main()\n"
                  "{\n"
                  "   gl_Position = vec4(aPos, 1.0);\n"
                  "   ourColor = aColor;\n"
                  "}\0";

const char* fsh = "#version 330 core\n"
                  "out vec4 FragColor;\n"
                  "in vec3 ourColor;\n"
                  "void main()\n"
                  "{\n"
                  "   FragColor = vec4(ourColor, 1.0f);\n"
                  "}\0";

int main() {
    auto window = GLFW::WindowWrapper::createWindow(800, 600, "Rectangle");
    auto shader = Shader::createShader(vsh, fsh);
    auto rectangle = Quad::createQuad(
        std::vector<glm::vec3>{
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(0.5f, 0.5f, 0.0f),
            glm::vec3(-0.5f, 0.5f, 0.0f),
        },
        std::vector<glm::vec3>{
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
        }
    );
    window->mainLoop([&]() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        rectangle->draw(*shader);
    });
}
```
![quad.png](img%2Fquad.png)
