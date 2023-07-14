#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "shader.hpp"
#include <memory>
#include <string>
#include <vector>

const int MAX_BONE_INFLUENCE = 4;

struct SimpleVertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

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

class SimpleMesh {
protected:
  GLuint m_VAO;
  GLuint m_VBO;
  GLuint m_EBO;
  std::vector<SimpleVertex> m_vertices;
  std::vector<GLuint> m_indices;

  void setup();

public:
  SimpleMesh(std::vector<SimpleVertex> vertices, std::vector<GLuint> indices);
  std::shared_ptr<SimpleMesh> createMesh(std::vector<Vertex> vertices,
                                         std::vector<GLuint> indices);
  ~SimpleMesh();
  inline void draw(Shader &shader);
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
  Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
       std::vector<Texture> textures);
  std::shared_ptr<Mesh> createMesh(std::vector<Vertex> vertices,
                                   std::vector<GLuint> indices,
                                   std::vector<Texture> textures);
  ~Mesh();
  inline void draw(Shader &shader);
};
