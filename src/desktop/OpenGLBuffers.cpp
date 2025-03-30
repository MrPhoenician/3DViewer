#include "OpenGLBuffers.h"

using namespace s21;

OpenGLBuffers::OpenGLBuffers() : gl(InitOpenGL::getInstance()){};

void OpenGLBuffers::updateBuffers(ObjData objData) {
  gl.glGenVertexArrays(1, &VAO);
  gl.glBindVertexArray(VAO);
  gl.glGenBuffers(1, &VBO);
  gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);
  gl.glBufferData(GL_ARRAY_BUFFER,
                  sizeof(float) * objData.getVerticesVector().size(),
                  objData.getVerticesVector().data(), GL_STATIC_DRAW);
  gl.glGenBuffers(1, &EBO);
  gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                  sizeof(unsigned int) * objData.getIndicesCount(),
                  objData.getIndicesVector().data(), GL_STATIC_DRAW);
  gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                           (void *)0);
  gl.glEnableVertexAttribArray(0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  gl.glEnable(GL_PROGRAM_POINT_SIZE);
  indicesCount = objData.getIndicesCount();
}

unsigned int OpenGLBuffers::getIndicesCount() { return indicesCount; };

GLuint OpenGLBuffers::getVAO() { return VAO; };

OpenGLBuffers::~OpenGLBuffers() {
  if (VAO) gl.glDeleteVertexArrays(1, &VAO);
  if (VBO) gl.glDeleteBuffers(1, &VBO);
}
