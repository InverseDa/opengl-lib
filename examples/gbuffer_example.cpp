#include <opengl/buffer.hpp>
#include <opengl/glfw.hpp>
#include <opengl/mesh.hpp>
#include <vector>

int main() {
    auto window = WindowWrapper::createWindow(800, 600, "Hello World");
    auto gbuffer = GBuffer::createGBuffer(800, 600);
    auto quad =
        Quad::createQuad(std::vector<glm::vec3>{glm::vec3(-1.0f, 1.0f, 0.0f),
                                                glm::vec3(-1.0f, -1.0f, 0.0f),
                                                glm::vec3(1.0f, -1.0f, 0.0f),
                                                glm::vec3(1.0f, 1.0f, 0.0f)},
                         std::vector<glm::vec2>{glm::vec2(0.0f, 1.0f),
                                                glm::vec2(0.0f, 0.0f),
                                                glm::vec2(1.0f, 0.0f),
                                                glm::vec2(1.0f, 1.0f)});

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

    auto shader_gbuffer =
        Shader::createShaderByPath("shader/model.vsh", "shader/model.fsh");
    auto shader_composite =
        Shader::createShaderByPath("shader/quad.vsh", "shader/quad.fsh");

    window->mainLoop([&]() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // PREPARE MATRIX
        glm::mat4 mat = glm::rotate(
            glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // G-BUFFER PASS
        gbuffer->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader_gbuffer->use();
        shader_gbuffer->setMatrix4("model", mat);
        triangle->draw(*shader_gbuffer);
        gbuffer->unbind();
        // COMPOSITE PASS
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gbuffer->getAlbedoSpec());
        shader_composite->setInt("finalImage", 0);
        quad->draw(*shader_composite);
    });
}
