#include <opengl/model.hpp>

GLuint TextureFromFile(const char* path, const std::string& directory) {
    std::string filename = directory + '/' + std::string(path);
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data =
        stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format{};
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     format,
                     width,
                     height,
                     0,
                     format,
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "ERROR";
        stbi_image_free(data);
    }

    return textureID;
}

Model::Model(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene =
        importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
        return;
    }

    m_directory = path.substr(0, path.find_last_of('/'));

    //    processNode(scene->mRootNode, scene);
}

std::shared_ptr<Model> Model::createModel(const std::string& path) {
    return std::make_shared<Model>(path);
}

void Model::draw(Shader& shader) {
    for (auto& mesh : m_meshes) {
        mesh.draw(shader);
    }
}
