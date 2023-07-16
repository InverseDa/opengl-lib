#include "opengl/mesh.hpp"

// ========================== Mesh ==========================

std::shared_ptr<Mesh> Mesh::createMesh(std::vector<Vertex> vertices,
                                       std::vector<GLuint> indices,
                                       std::vector<Texture> textures) {
  return std::make_shared<Mesh>(vertices, indices, textures);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
           std::vector<Texture> textures)
    : m_vertices(vertices), m_indices(indices), m_textures(textures) {
  setup();
}

Mesh::~Mesh() {}

void Mesh::setup() {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
               &m_vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint),
               &m_indices[0], GL_STATIC_DRAW);

  // position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);

  // normal
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (GLvoid *)offsetof(Vertex, normal));

  // texCoords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (GLvoid *)offsetof(Vertex, texCoords));

  // tangent
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (GLvoid *)offsetof(Vertex, tangent));

  // bitangent
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (GLvoid *)offsetof(Vertex, bitangent));
}

inline void Mesh::draw(Shader &shader) {
  GLuint diffuseNr = 1;
  GLuint specularNr = 1;
  GLuint normalNr = 1;
  GLuint heightNr = 1;
  shader.use();
  for (GLuint i = 0; i < m_textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string name = m_textures[i].type;
    std::string number;
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_specular")
      number = std::to_string(specularNr++);
    else if (name == "texture_normal")
      number = std::to_string(normalNr++);
    else if (name == "texture_height")
      number = std::to_string(heightNr++);
    shader.setInt((name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// ========================== Triangle ==========================

Triangle::Triangle(std::vector<SimpleVertex> vertices) : m_vertices(vertices) {
  m_indices = std::vector<GLuint>{0, 1, 2};
  setup();
}

void Triangle::setup() {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
               &m_vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint),
               &m_indices[0], GL_STATIC_DRAW);

  // position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex),
                        (GLvoid *)0);

  // color
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (GLvoid *)offsetof(SimpleVertex, color));

  // normal
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (GLvoid *)offsetof(SimpleVertex, normal));

  // texCoords
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (GLvoid *)offsetof(SimpleVertex, texCoords));
}

Triangle::~Triangle() {}

std::shared_ptr<Triangle>
Triangle::createTriangle(std::vector<SimpleVertex> vertices) {
  return std::make_shared<Triangle>(vertices);
}

inline void Triangle::draw(Shader &shader) {
  GLuint diffuseNr = 1;
  GLuint specularNr = 1;
  GLuint normalNr = 1;
  GLuint heightNr = 1;
  shader.use();
  for (GLuint i = 0; i < m_textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string name = m_textures[i].type;
    std::string number;
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_specular")
      number = std::to_string(specularNr++);
    else if (name == "texture_normal")
      number = std::to_string(normalNr++);
    else if (name == "texture_height")
      number = std::to_string(heightNr++);
    shader.setInt((name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// ========================== Quad ==========================
// Quad::Quad(std::vector<SimpleVertex> vertices) : m_vertices(vertices) {
//   m_indices = std::vector<GLuint>{0, 1, 2, 0, 2, 3};
//   setup();
// }
