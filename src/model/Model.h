#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_H
#define CPP4_3DVIEWER_V2_0_1_MODEL_H

#include "../api/ModelApi.h"
#include "ObjLoader.h"
#include "TransformationMatrix.h"

namespace s21 {
class Model {
 public:
  Model();

  glm::mat4 getMatrix(MatrixData data);
  ObjData parsData(std::string string);
  glm::mat4 getProjection(bool projection, float aspect);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_H
