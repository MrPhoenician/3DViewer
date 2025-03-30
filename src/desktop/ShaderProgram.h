#ifndef CPP4_3DVIEWER_V2_0_1_SHADERPROGRAM_H
#define CPP4_3DVIEWER_V2_0_1_SHADERPROGRAM_H

#include "InitOpenGL.h"
#include "Shader.h"

namespace s21 {
class ShaderProgram {
 private:
  InitOpenGL &gl;
  GLuint myShaderProgram;

 public:
  ShaderProgram();
  void initProgram();
  GLuint getShaderProgram();
  ~ShaderProgram();
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_1_SHADERPROGRAM_H
