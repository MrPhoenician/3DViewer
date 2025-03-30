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
      verticesSize(0.0) {}

void OpenGL::init() {
  currentProgram = new ShaderProgram();
  glBuffers = new OpenGLBuffers();
  getUniformsLoc();
  gl.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  gl.glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::uploadDataToBuffers(ObjData data) {
  glBuffers->updateBuffers(data);
}

void OpenGL::draw() {
  gl.glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(),
                  backColor.alphaF());  // Устанавливаем цвет очистки
  gl.glClear(GL_COLOR_BUFFER_BIT);
  gl.glUseProgram(currentProgram->getShaderProgram());
  gl.glUniform4fv(colorLocation, 1, &lineColor[0]);
  gl.glUniform1i(stippleLoc, stippleMode ? 1 : 0);
  gl.glUniform1f(pointLoc, verticesSize);
  gl.glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                        glm::value_ptr(projectionMat));
  gl.glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
  gl.glLineWidth(lineThikness);
  gl.glBindVertexArray(glBuffers->getVAO());
  gl.glDrawElements(GL_LINES,
                    static_cast<GLsizei>(glBuffers->getIndicesCount()),
                    GL_UNSIGNED_INT, 0);
  if (verticesSize >= 1.0) {
    gl.glUniform1i(stippleLoc, 0);
    gl.glUniform4fv(colorLocation, 1, &pointColor[0]);
    gl.glUniform1i(circleLoc, isCircle ? 1 : 0);
    gl.glDrawElements(GL_POINTS,
                      static_cast<GLsizei>(glBuffers->getIndicesCount()),
                      GL_UNSIGNED_INT, 0);
    gl.glUniform1i(circleLoc, 0);
  }
  gl.glBindVertexArray(0);
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
}

void OpenGL::setMatrix(glm::mat4 matrix) { this->matrix = matrix; }

void OpenGL::setBackgroundColor(const QColor &color) { backColor = color; }

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

void OpenGL::disable() {}
