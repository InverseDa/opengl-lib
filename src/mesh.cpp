#include "opengl/mesh.hpp"

// ========================== Mesh ==========================

std::shared_ptr<Mesh> Mesh::createMesh(std::vector<Vertex> vertices,
                                       std::vector<GLuint> indices,
                                       std::vector<Texture> textures) {
    return std::make_shared<Mesh>(vertices, indices, textures);
}

Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<GLuint> indices,
           std::vector<Texture> textures)
    : m_vertices(vertices),
      m_indices(indices),
      m_textures(textures) {
    setup();
}

Mesh::~Mesh() {}

void Mesh::setup() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(Vertex),
                 &m_vertices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(GLuint),
                 &m_indices[0],
                 GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, normal));

    // texCoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, texCoords));

    // tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, tangent));

    // bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, bitangent));
}

inline void Mesh::draw(Shader& shader) {
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

Triangle::Triangle(std::vector<glm::vec3> position,
                   std::vector<glm::vec3> colors) {
    m_vertices = std::vector<__vertex>{{position[0], colors[0]},
                                       {position[1], colors[1]},
                                       {position[2], colors[2]}};
    m_indices = std::vector<GLuint>{0, 1, 2};
    setup();
}

Triangle::Triangle(std::vector<glm::vec3> position,
                   std::vector<glm::vec2> texCoords,
                   std::vector<Texture> textures) {
    m_vertices =
        std::vector<__vertex>{{position[0], glm::vec3(0.0f), texCoords[0]},
                              {position[1], glm::vec3(0.0f), texCoords[1]},
                              {position[2], glm::vec3(0.0f), texCoords[2]}};
    m_indices = std::vector<GLuint>{0, 1, 2};
    m_textures = textures;
    setup();
}

void Triangle::setup() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(__vertex),
                 &m_vertices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(GLuint),
                 &m_indices[0],
                 GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(__vertex), (GLvoid*)0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(__vertex),
                          (GLvoid*)offsetof(__vertex, color));

    // texCoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(__vertex),
                          (GLvoid*)offsetof(__vertex, texCoords));
}

std::shared_ptr<Triangle>
Triangle::createTriangle(std::vector<glm::vec3> position,
                         std::vector<glm::vec3> colors) {
    return std::make_shared<Triangle>(position, colors);
}

std::shared_ptr<Triangle>
Triangle::createTriangle(std::vector<glm::vec3> position,
                         std::vector<glm::vec2> texCoords,
                         std::vector<Texture> textures) {
    return std::make_shared<Triangle>(position, texCoords, textures);
}

Triangle::~Triangle() {}

void Triangle::draw(Shader& shader) {
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
Quad::Quad(std::vector<glm::vec3> position, std::vector<glm::vec3> colors)
    : Triangle(position, colors) {
    m_vertices = std::vector<__vertex>{{position[0], colors[0]},
                                       {position[1], colors[1]},
                                       {position[2], colors[2]},
                                       {position[3], colors[3]}};
    m_indices = std::vector<GLuint>{0, 1, 2, 0, 2, 3};
    setup();
}

Quad::Quad(std::vector<glm::vec3> position,
           std::vector<glm::vec2> texCoords,
           std::vector<Texture> textures)
    : Triangle(position, texCoords, textures) {
    m_vertices =
        std::vector<__vertex>{{position[0], glm::vec3(0.0f), texCoords[0]},
                              {position[1], glm::vec3(0.0f), texCoords[1]},
                              {position[2], glm::vec3(0.0f), texCoords[2]},
                              {position[3], glm::vec3(0.0f), texCoords[3]}};
    m_indices = std::vector<GLuint>{0, 1, 2, 0, 2, 3};
    m_textures = textures;
    setup();
}

std::shared_ptr<Quad> Quad::createQuad(std::vector<glm::vec3> position,
                                       std::vector<glm::vec3> colors) {
    return std::make_shared<Quad>(position, colors);
}

std::shared_ptr<Quad> Quad::createQuad(std::vector<glm::vec3> position,
                                       std::vector<glm::vec2> texCoords,
                                       std::vector<Texture> textures) {
    return std::make_shared<Quad>(position, texCoords, textures);
}

Quad::~Quad() {}

// ========================== Cube ==========================
Cube::Cube(std::vector<glm::vec3> position, std::vector<glm::vec3> colors)
    : Quad(position, colors) {
    m_vertices = std::vector<__vertex>{{position[0], colors[0]},
                                       {position[1], colors[1]},
                                       {position[2], colors[2]},
                                       {position[3], colors[3]},
                                       {position[4], colors[4]},
                                       {position[5], colors[5]},
                                       {position[6], colors[6]},
                                       {position[7], colors[7]}};
    m_indices = std::vector<GLuint>{
        0, 1, 2, 0, 2, 3, // front
        4, 5, 6, 4, 6, 7, // back
        0, 1, 5, 0, 5, 4, // left
        2, 3, 7, 2, 7, 6, // right
        1, 2, 6, 1, 6, 5, // top
        0, 3, 7, 0, 7, 4  // bottom
    };
    setup();
}

Cube::Cube(std::vector<glm::vec3> position,
           std::vector<glm::vec2> texCoords,
           std::vector<Texture> textures)
    : Quad(position, texCoords, textures) {
    m_vertices =
        std::vector<__vertex>{{position[0], glm::vec3(0.0f), texCoords[0]},
                              {position[1], glm::vec3(0.0f), texCoords[1]},
                              {position[2], glm::vec3(0.0f), texCoords[2]},
                              {position[3], glm::vec3(0.0f), texCoords[3]},
                              {position[4], glm::vec3(0.0f), texCoords[4]},
                              {position[5], glm::vec3(0.0f), texCoords[5]},
                              {position[6], glm::vec3(0.0f), texCoords[6]},
                              {position[7], glm::vec3(0.0f), texCoords[7]}};
    m_indices = std::vector<GLuint>{
        0, 1, 2, 0, 2, 3, // front
        4, 5, 6, 4, 6, 7, // back
        0, 1, 5, 0, 5, 4, // left
        2, 3, 7, 2, 7, 6, // right
        1, 2, 6, 1, 6, 5, // top
        0, 3, 7, 0, 7, 4  // bottom
    };
    m_textures = textures;
    setup();
}

std::shared_ptr<Cube> Cube::createCube(std::vector<glm::vec3> position,
                                       std::vector<glm::vec3> colors) {
    return std::make_shared<Cube>(position, colors);
}

std::shared_ptr<Cube> Cube::createCube(std::vector<glm::vec3> position,
                                       std::vector<glm::vec2> texCoords,
                                       std::vector<Texture> textures) {
    return std::make_shared<Cube>(position, texCoords, textures);
}

Cube::~Cube() {}