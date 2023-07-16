#pragma once
#include "glad/glad.h"
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

struct SimpleVertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec3 normal;
  glm::vec2 texCoords;
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
  Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
       std::vector<Texture> textures);
  ~Mesh();
  std::shared_ptr<Mesh> createMesh(std::vector<Vertex> vertices,
                                   std::vector<GLuint> indices,
                                   std::vector<Texture> textures);
  inline void draw(Shader &shader);
};

class Triangle {
protected:
  GLuint m_VAO;
  GLuint m_VBO;
  GLuint m_EBO;
  std::vector<SimpleVertex> m_vertices;
  std::vector<GLuint> m_indices;
  std::vector<glm::vec3> m_colors;
  std::vector<Texture> m_textures;

  void setup();

public:
  Triangle(std::vector<SimpleVertex> vertices);
  Triangle(std::vector<SimpleVertex> vertices, std::vector<Texture> textures);
  ~Triangle();

  std::shared_ptr<Triangle> createTriangle(std::vector<SimpleVertex> vertices);
  std::shared_ptr<Triangle> createTriangle(std::vector<SimpleVertex> vertices,
                                           std::vector<Texture> textures);
  inline void draw(Shader &shader);
};

// class Quad : public Triangle {
// protected:
//   void setup();

// public:
//   Quad(std::vector<SimpleVertex> vertices);
//   Quad(std::vector<SimpleVertex> vertices, std::vector<Texture> textures);
//   ~Quad();
//   std::shared_ptr<Quad> createQuad(std::vector<SimpleVertex> vertices);
//   std::shared_ptr<Quad> createQuad(std::vector<SimpleVertex> vertices,
//                                    std::vector<Texture> textures);
//   inline void draw(Shader &shader);
// };