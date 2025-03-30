#ifndef CPP4_3DVIEWER_TRANSFORMATION_H
#define CPP4_3DVIEWER_TRANSFORMATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace s21 {

class TransformationMatrix {
 private:
  glm::mat4 transform;
  glm::vec3 translateXYZ;
  glm::vec3 rotateXYZ;
  float scale;
  glm::mat4 projectionMat;

 public:
  TransformationMatrix();
  TransformationMatrix(glm::vec3 transVec, glm::vec3 rotVec,
                       float incomingScale);
  glm::mat4 getMatrix();
  void update();
  glm::mat4 getProjection(bool projection, float aspect);
  void setOrthographic();
  void setPerspective(float aspect);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_TRANSFORMATION_H
