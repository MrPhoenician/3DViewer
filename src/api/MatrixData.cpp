#include "MatrixData.h"

using namespace s21;

MatrixData::MatrixData() {
  translateXYZ[0] = 0;
  translateXYZ[1] = 0;
  translateXYZ[2] = 0;
  rotateXYZ[0] = 0;
  rotateXYZ[1] = 0;
  rotateXYZ[2] = 0;
  scale = 1;
}

void MatrixData::setTranslate(glm::vec3 vector) { translateXYZ = vector; }
void MatrixData::setRotate(glm::vec3 vector) { rotateXYZ = vector; }
void MatrixData::setScale(float value) { scale = value; }
glm::vec3 MatrixData::getTranslate() { return translateXYZ; }
glm::vec3 MatrixData::getRotate() { return rotateXYZ; }
float MatrixData::getScale() { return scale; }
