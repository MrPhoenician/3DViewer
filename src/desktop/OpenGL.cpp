#include "OpenGL.h"

using namespace s21;

OpenGL::OpenGL()
    : projectionMat(glm::mat4(1.0f)),
      gl(InitOpenGL::getInstance()),
      backColor("white"),
      pointColor(0.0f, 0.0f, 0.0f, 1.0f),
      lineColor(0.0f, 0.0f, 0.0f, 1.0f),
      matrix(glm::mat4(1.0f)),
      lineThikness(1.0f),
      verticesSize(0.0),
      cashLineColor(lineColor),
      cashStippleMode(true),
      cashMatrix(true),
      cashProjectionMat(true),
      cashVerticesSize(verticesSize),
      cashLineThikness(true) {}

void OpenGL::init() {
  currentProgram = new ShaderProgram();
  glBuffers = new OpenGLBuffers();
  getUniformsLoc();
  gl.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  gl.glClear(GL_COLOR_BUFFER_BIT);
  gl.glUniform1i(stippleLoc, 1);
}

void OpenGL::uploadDataToBuffers(ObjData data) {
  glBuffers->updateBuffers(std::move(data));
  gl.glBindVertexArray(glBuffers->getVAO());
}

void OpenGL::draw() {
  gl.glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(),
                  backColor.alphaF());
  gl.glClear(GL_COLOR_BUFFER_BIT);
  gl.glUseProgram(currentProgram->getShaderProgram());
//  if (cashLineColor != lineColor) {
    gl.glUniform4fv(colorLocation, 1, &lineColor[0]);
//    cashLineColor = lineColor;
//  }
  if (cashStippleMode != stippleMode) {
    gl.glUniform1i(stippleLoc, stippleMode);
    cashStippleMode = stippleMode;
  }
  if (cashVerticesSize != verticesSize) {
    gl.glUniform1f(pointLoc, verticesSize);
    cashVerticesSize = verticesSize;
  }
  if (cashProjectionMat) {
    gl.glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                          glm::value_ptr(projectionMat));
    cashProjectionMat = false;
  }
  if (cashMatrix) {
    gl.glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
    cashMatrix = false;
  }
  if (cashLineThikness != lineThikness) {
    gl.glLineWidth(lineThikness);
    cashLineThikness = lineThikness;
  }
  gl.glDrawElements(GL_LINES,
                    static_cast<GLsizei>(glBuffers->getIndicesCount()),
                    GL_UNSIGNED_INT, nullptr);
  if (verticesSize >= 1.0) {
    if (stippleMode) {
      gl.glUniform1i(stippleLoc, 0);
    }
    gl.glUniform4fv(colorLocation, 1, &pointColor[0]);
    gl.glUniform1i(circleLoc, isCircle ? 1 : 0);
    gl.glDrawElements(GL_POINTS,
                      static_cast<GLsizei>(glBuffers->getIndicesCount()),
                      GL_UNSIGNED_INT, nullptr);
    if (isCircle) {
      gl.glUniform1i(circleLoc, 0);
    }
    if (stippleMode) {
      gl.glUniform1i(stippleLoc, stippleMode);
    }
  }
}

void OpenGL::getUniformsLoc() {
  colorLocation =
      gl.glGetUniformLocation(currentProgram->getShaderProgram(), "ourColor");
  stippleLoc = gl.glGetUniformLocation(currentProgram->getShaderProgram(),
                                       "stippleLine");
  pointLoc =
      gl.glGetUniformLocation(currentProgram->getShaderProgram(), "pointSize");
  projectionLoc =
      gl.glGetUniformLocation(currentProgram->getShaderProgram(), "projection");
  circleLoc =
      gl.glGetUniformLocation(currentProgram->getShaderProgram(), "isCircle");
  transformLoc =
      gl.glGetUniformLocation(currentProgram->getShaderProgram(), "transform");
}

void OpenGL::setProjectionMat(glm::mat4 projectionMatrix) {
  projectionMat = projectionMatrix;
  cashProjectionMat = true;
}

void OpenGL::setMatrix(glm::mat4 matrixIn) {
  this->matrix = matrixIn;
  cashMatrix = true;
}

void OpenGL::setBackgroundColor(const QColor color) { backColor = color; }

void OpenGL::setPointColor(const QColor &color) {
  pointColor =
      glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void OpenGL::setStippleLine(int x) { stippleMode = x; }

void OpenGL::setLineColor(const QColor &color) {
  lineColor =
      glm::vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void OpenGL::changeThikness(int value) {
  lineThikness = static_cast<float>(value);
}

void OpenGL::changePointSize(int value) {
  verticesSize = static_cast<float>(value);
}

void OpenGL::setRoundVertices(int state) { isCircle = state; }

QColor OpenGL::getBackgroundColor() { return backColor; }

QColor OpenGL::getPointColor() {
  QColor color(pointColor[0] * 255, pointColor[1] * 255, pointColor[2] * 255,
               pointColor[3] * 255);
  return color;
}

QColor OpenGL::getLineColor() {
  QColor color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255,
               lineColor[3] * 255);
  return color;
}

OpenGL::~OpenGL() {
  delete currentProgram;
  delete glBuffers;
}
