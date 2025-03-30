#ifndef CPP4_3DVIEWER_V2_0_1_MATRIXDATA_H
#define CPP4_3DVIEWER_V2_0_1_MATRIXDATA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace s21 {
class MatrixData {
 public:
  MatrixData();
  void setTranslate(glm::vec3 vector);
  void setRotate(glm::vec3 vector);
  void setScale(float value);
  glm::vec3 getTranslate();
  glm::vec3 getRotate();
  float getScale();

 private:
  glm::vec3 translateXYZ;
  glm::vec3 rotateXYZ;
  float scale;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MATRIXDATA_H
