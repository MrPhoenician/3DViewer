#include "Shader.h"

using namespace s21;

Shader::Shader(const char* filepath, GLenum shaderType)
    : gl(InitOpenGL::getInstance()) {
  this->myShader = gl.glCreateShader(shaderType);
  std::string shaderCode = loadShaderFromFile(filepath);
  const char* shaderSource = shaderCode.c_str();
  gl.glShaderSource(this->myShader, 1, &shaderSource, nullptr);
  gl.glCompileShader(this->myShader);
  int success;
  char infoLog[512];
  gl.glGetShaderiv(this->myShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    gl.glGetShaderInfoLog(this->myShader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

std::string Shader::loadShaderFromFile(const char* filepath) {
  std::string shaderSource;
  std::ifstream file(filepath, std::ios::in);
  if (file.is_open()) {
    std::stringstream sstr;  // Буфер для чтения
    sstr << file.rdbuf();    // Считываем файл
    shaderSource = sstr.str();  // Преобразуем буфер к строке
    file.close();               // Закрываем файл
  }

  return shaderSource;
}

GLuint Shader::getShader() const { return this->myShader; }

Shader::~Shader() { gl.glDeleteShader(this->myShader); }
