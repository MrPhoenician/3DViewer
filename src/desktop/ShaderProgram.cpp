#include "ShaderProgram.h"

using namespace s21;

ShaderProgram::ShaderProgram() : gl(InitOpenGL::getInstance()) {
  initProgram();
}
void ShaderProgram::initProgram() {
  int success;
  char infoLog[512];
  Shader vertexShader("shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
  Shader fragmentShader("shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);

  this->myShaderProgram = gl.glCreateProgram();
  gl.glAttachShader(this->myShaderProgram, vertexShader.getShader());
  gl.glAttachShader(this->myShaderProgram, fragmentShader.getShader());
  gl.glLinkProgram(this->myShaderProgram);
  gl.glGetProgramiv(this->myShaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    gl.glGetProgramInfoLog(this->myShaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}

GLuint ShaderProgram::getShaderProgram() { return this->myShaderProgram; }

ShaderProgram::~ShaderProgram() { gl.glDeleteProgram(this->myShaderProgram); }
