#include "RawMatrixData.h"

using namespace s21;

RawMatrixData::RawMatrixData() {
  translateXYZ = glm::vec3(50.0f);
  rotateXYZ = glm::vec3(180.0f);
  scale = 50.0f;
}

void RawMatrixData::setTranslate(float value, int id) {
  translateXYZ[id] = value;
}

void RawMatrixData::setRotate(float value, int id) { rotateXYZ[id] = value; }
void RawMatrixData::setScale(float value) { scale = value; }
glm::vec3 RawMatrixData::getTranslate() { return translateXYZ; }
glm::vec3 RawMatrixData::getRotate() { return rotateXYZ; }
float RawMatrixData::getScale() { return scale; }
