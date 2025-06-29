#ifndef CPP4_3DVIEWER_V2_0_1_OPENGL_H
#define CPP4_3DVIEWER_V2_0_1_OPENGL_H

#include <QOpenGLWidget>

#include "OpenGLBuffers.h"
#include "ShaderProgram.h"
#include "Singleton.h"

namespace s21 {

class OpenGL : public Singleton<OpenGL> {
  friend class Singleton<OpenGL>;

 public:
  void init();
  void setMatrix(const glm::mat4 &matrixIn);
  void uploadDataToBuffers(ObjData data) const;
  void draw();
  void setBackgroundColor(const QColor &color);
  void setStippleLine(int value);
  void setLineColor(const QColor &color);
  void changeThikness(int value);
  void changePointSize(int value);
  void setPointColor(const QColor &color);
  void setRoundVertices(int state);
  void setProjectionMat(const glm::mat4 &projectionMatrix);
  QColor getBackgroundColor();
  QColor getPointColor();
  QColor getLineColor();
  ~OpenGL() override;

 private:
  OpenGL();
  void getUniformsLoc();
  glm::mat4 projectionMat;
  InitOpenGL &gl;
  QColor backColor;
  glm::vec4 pointColor;
  glm::vec4 lineColor;
  glm::mat4 matrix;
  bool stippleMode;
  float lineThikness;
  float verticesSize;
  bool isCircle;
  ShaderProgram *currentProgram;
  OpenGLBuffers *glBuffers;
  GLint colorLocation;
  GLint stippleLoc;
  GLint pointLoc;
  GLint projectionLoc;
  GLint transformLoc;
  GLint circleLoc;
  glm::vec4 cashLineColor;
  bool cashStippleMode;
  bool cashMatrix;
  bool cashProjectionMat;
  float cashVerticesSize;
  float cashLineThikness;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OPENGL_H
