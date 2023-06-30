#include "opengl/shader.hpp"

std::shared_ptr<Shader>
Shader::createShader(const std::string &vertexShaderPath,
                     const std::string &fragmentShaderPath) {
  return std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
}

Shader::Shader(const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath) {
  // 转成绝对路径
  std::string vshAbsoulutePath = std::filesystem::absolute(vertexShaderPath);
  std::string fshAbsoulutePath = std::filesystem::absolute(fragmentShaderPath);

  // 读取文件
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // 打开文件
    vShaderFile.open(vertexShaderPath);
    fShaderFile.open(fragmentShaderPath);
    std::stringstream vShaderStream, fShaderStream;
    // 读取文件的缓冲内容到数据流中
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // 关闭文件处理器
    vShaderFile.close();
    fShaderFile.close();
    // 转换数据流到string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure e) {
    throw std::runtime_error("Failed to read shader file.");
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  // 编译着色器
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];
  // 顶点着色器
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);
  // 打印错误信息
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    throw std::runtime_error("Failed to compile vertex shader.");
  }
  // 片段着色器
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);
  // 打印错误信息
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
    throw std::runtime_error("Failed to compile fragment shader.");
  }

  // 链接着色器程序
  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);
  // 打印连接错误（如果有的话）
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, nullptr, infoLog);
    throw std::runtime_error("Failed to link shader.");
  }

  // 删除着色器，因为已经链接到程序了
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() const { glUseProgram(id); }

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVector2(const std::string &name, float x, float y) const {
  glUniform2fv(glGetUniformLocation(id, name.c_str()), 1,
               glm::value_ptr(glm::vec2(x, y)));
}

void Shader::setVector2(const std::string &name, glm::vec2 vec) const {
  glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVector3(const std::string &name, float x, float y,
                        float z) const {
  glUniform3fv(glGetUniformLocation(id, name.c_str()), 1,
               glm::value_ptr(glm::vec3(x, y, z)));
}

void Shader::setVector3(const std::string &name, glm::vec3 vec) const {
  glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVector4(const std::string &name, float x, float y, float z,
                        float w) const {
  glUniform4fv(glGetUniformLocation(id, name.c_str()), 1,
               glm::value_ptr(glm::vec4(x, y, z, w)));
}

void Shader::setVector4(const std::string &name, glm::vec4 vec) const {
  glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setMatrix3(const std::string &name, glm::mat3 mat3) const {
  glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(mat3));
}

void Shader::setMatrix4(const std::string &name, glm::mat4 mat4) const {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(mat4));
}