#pragma once

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "glad/glad.h"
#include "opengl/glm.hpp"
#include "opengl/mesh.hpp"
#include "stb_image.h"

GLuint TextureFromFile(const char* path, const std::string& directory);

class Model {
  public:
    explicit Model(const std::string& path);
    static std::shared_ptr<Model> createModel(const std::string& path);

    void draw(Shader& shader);

  private:
    std::vector<Mesh> m_meshes;
    std::vector<Texture> m_textures_loaded;
    std::string m_directory;
    bool gammaCorrection{};
};
