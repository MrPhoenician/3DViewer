#ifndef CPP4_3DVIEWER_V2_0_1_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_1_CONTROLLER_H

#include "../api/ControllerApi.h"
#include "../api/ModelApi.h"
#include "../model/Model.h"

namespace s21 {

typedef enum { AXIS_X, AXIS_Y, AXIS_Z } Signal;

class Controller {
 public:
  explicit Controller();
  static glm::mat4 signal(RawMatrixData data);
  static ObjData signal(const std::string &str);
  static glm::mat4 signal(float aspect, bool projection);

 private:
  static MatrixData getData(RawMatrixData data);
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_1_CONTROLLER_H
