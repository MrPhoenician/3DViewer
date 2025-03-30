#ifndef CPP4_3DVIEWER_V2_0_1_OPENGLBUFFERS_H
#define CPP4_3DVIEWER_V2_0_1_OPENGLBUFFERS_H

#include <QOpenGLExtraFunctions>
#include <iostream>

#include "../api/ControllerApi.h"
#include "InitOpenGL.h"

namespace s21 {

class OpenGLBuffers {
 private:
  GLuint VBO, VAO, EBO;
  unsigned int indicesCount;
  InitOpenGL &gl;

 public:
  OpenGLBuffers();
  GLuint getVAO();
  void updateBuffers(ObjData data);
  unsigned int getIndicesCount();
  ~OpenGLBuffers();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OPENGLBUFFERS_H
