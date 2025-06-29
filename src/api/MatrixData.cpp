#include "MatrixData.h"

using namespace s21;

MatrixData::MatrixData() {
  translateXYZ = glm::vec3{0};
  rotateXYZ = glm::vec3{0};
  scale = 1;
}

void MatrixData::setTranslate(const glm::vec3 vector) { translateXYZ = vector; }
void MatrixData::setRotate(const glm::vec3 vector) { rotateXYZ = vector; }
void MatrixData::setScale(const float value) { scale = value; }
glm::vec3 MatrixData::getTranslate() const { return translateXYZ; }
glm::vec3 MatrixData::getRotate() const { return rotateXYZ; }
float MatrixData::getScale() const { return scale; }
