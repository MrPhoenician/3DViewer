#include "TransformationMatrix.h"

using namespace s21;

TransformationMatrix::TransformationMatrix() : projectionMat{1.0f} {}

TransformationMatrix::TransformationMatrix(const glm::vec3 transVec,
                                           const glm::vec3 rotVec,
                                           const float incomingScale) {
  translateXYZ = transVec;
  rotateXYZ = rotVec;
  scale = incomingScale;
  update();
}

glm::mat4 TransformationMatrix::getMatrix() const { return transform; }

void TransformationMatrix::update() {
  transform = glm::mat4(1.0f);  // что бы избежать накопления преобразований
  transform = glm::translate(transform, translateXYZ);
  transform = glm::rotate(transform, rotateXYZ[0], glm::vec3(1.0f, 0.0f, 0.0f));
  transform = glm::rotate(transform, rotateXYZ[1], glm::vec3(0.0f, 1.0f, 0.0f));
  transform = glm::rotate(transform, rotateXYZ[2], glm::vec3(0.0f, 0.0f, 1.0f));
  transform = glm::scale(transform, glm::vec3(scale));
}

glm::mat4 TransformationMatrix::getProjection(const bool projection,
                                              const float aspect) {
  if (projection) {
    setOrthographic();
  } else {
    setPerspective(aspect);
  }

  return projectionMat;
}

void TransformationMatrix::setOrthographic() {
  constexpr float left = -1.0f, right = 1.0f;
  constexpr float bottom = -1.0f, top = 1.0f;
  constexpr float near = -1.0f, far = 1.0f;

  projectionMat = glm::ortho(left, right, bottom, top, near, far);
}

void TransformationMatrix::setPerspective(const float aspect) {
  constexpr float fov = glm::radians(45.0f);  // Угол обзора (45 градусов)
  constexpr float near = 0.1f;   // Ближняя плоскость
  constexpr float far = 100.0f;  // Дальняя плоскость

  projectionMat = glm::perspective(fov, aspect, near, far);
}