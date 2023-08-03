#pragma once
#include "glad/glad.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "shader.hpp"

#include <memory>
#include <string>
#include <vector>


const int MAX_BONE_INFLUENCE = 4;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Texture {
    GLuint id;
    std::string type;
    std::string path;
};

class Mesh {
  protected:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::vector<Texture> m_textures;

    void setup();

  public:
    Mesh(std::vector<Vertex> vertices,
         std::vector<GLuint> indices,
         std::vector<Texture> textures);
    ~Mesh();
    std::shared_ptr<Mesh> createMesh(std::vector<Vertex> vertices,
                                     std::vector<GLuint> indices,
                                     std::vector<Texture> textures);
    inline void draw(Shader& shader);
};

class Triangle {
  protected:
    struct __vertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoords;
    };
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    std::vector<__vertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::vector<Texture> m_textures;

    void setup();

  public:
    Triangle(std::vector<glm::vec3> position,
             std::vector<glm::vec3> colors = {});
    Triangle(std::vector<glm::vec3> position,
             std::vector<glm::vec2> texCoords = {},
             std::vector<Texture> textures = {});
    ~Triangle();

    static std::shared_ptr<Triangle>
    createTriangle(std::vector<glm::vec3> position,
                   std::vector<glm::vec3> colors = {});

    static std::shared_ptr<Triangle>
    createTriangle(std::vector<glm::vec3> position,
                   std::vector<glm::vec2> texCoords = {},
                   std::vector<Texture> textures = {});
    void draw(Shader& shader);
};

class Quad : public Triangle {
  public:
    Quad(std::vector<glm::vec3> position, std::vector<glm::vec3> colors = {});
    Quad(std::vector<glm::vec3> position,
         std::vector<glm::vec2> texCoords = {},
         std::vector<Texture> textures = {});
    ~Quad();

    static std::shared_ptr<Quad> createQuad(std::vector<glm::vec3> position,
                                            std::vector<glm::vec3> colors = {});

    static std::shared_ptr<Quad>
    createQuad(std::vector<glm::vec3> position,
               std::vector<glm::vec2> texCoords = {},
               std::vector<Texture> textures = {});
};

class Cube : public Quad {
  public:
    Cube(std::vector<glm::vec3> position, std::vector<glm::vec3> colors = {});
    Cube(std::vector<glm::vec3> position,
         std::vector<glm::vec2> texCoords = {},
         std::vector<Texture> textures = {});
    ~Cube();

    static std::shared_ptr<Cube> createCube(std::vector<glm::vec3> position,
                                            std::vector<glm::vec3> colors = {});

    static std::shared_ptr<Cube>
    createCube(std::vector<glm::vec3> position,
               std::vector<glm::vec2> texCoords = {},
               std::vector<Texture> textures = {});
};