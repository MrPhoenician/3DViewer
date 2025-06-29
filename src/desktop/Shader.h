#ifndef CPP4_3DVIEWER_V2_0_1_SHADER_H
#define CPP4_3DVIEWER_V2_0_1_SHADER_H

#include <fstream>
#include <iostream>
#include <string>

#include "InitOpenGL.h"

namespace s21 {

class Shader {
 private:
  GLuint myShader;
  static std::string loadShaderFromFile(const char *filepath);
  InitOpenGL &gl;

 public:
  Shader(const char *filepath, GLenum shaderType);
  GLuint getShader() const;
  ~Shader();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_SHADER_H
