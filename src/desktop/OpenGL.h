#ifndef CPP4_3DVIEWER_V2_0_1_OPENGL_H
#define CPP4_3DVIEWER_V2_0_1_OPENGL_H

#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>

#include "OpenGLBuffers.h"
#include "ShaderProgram.h"
#include "Singleton.h"

namespace s21 {

class OpenGL : public Singleton<OpenGL> {
  friend class Singleton<OpenGL>;

 public:
  void init();
  void disable();
  void setMatrix(glm::mat4 matrix);
  void uploadDataToBuffers(ObjData data);
  void draw();
  void setBackgroundColor(const QColor &color);
  void setStippleLine(int x);
  void setLineColor(const QColor &color);
  void changeThikness(int value);
  void changePointSize(int value);
  void setPointColor(const QColor &color);
  void setRoundVertices(int state);
  void setProjectionMat(glm::mat4 matrix);
  QColor getBackgroundColor();
  QColor getPointColor();
  QColor getLineColor();

 private:
  OpenGL();
  glm::mat4 projectionMat;
  InitOpenGL &gl;
  QColor backColor;
  glm::vec4 pointColor;
  glm::vec4 lineColor;
  glm::mat4 matrix;
  bool stippleMode;
  float lineThikness;
  float verticesSize;
  bool bufferStatus;
  bool isCircle;
  ShaderProgram *currentProgram;
  OpenGLBuffers *glBuffers;
  GLint colorLocation;
  GLint stippleLoc;
  GLint pointLoc;
  GLint projectionLoc;
  GLint transformLoc;
  GLint circleLoc;
  void getUniformsLoc();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OPENGL_H
