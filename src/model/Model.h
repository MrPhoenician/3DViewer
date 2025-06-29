#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_H
#define CPP4_3DVIEWER_V2_0_1_MODEL_H

#include "../api/ModelApi.h"
#include "ObjLoader.h"
#include "TransformationMatrix.h"

namespace s21 {
class Model {
 public:
  Model();
  static glm::mat4 getMatrix(const MatrixData &data);
  static ObjData parsData(const std::string &string);
  static glm::mat4 getProjection(bool projection, float aspect);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_H
