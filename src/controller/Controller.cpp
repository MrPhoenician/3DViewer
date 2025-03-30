#include "Controller.h"

using namespace s21;

Controller::Controller(Model model) : model(model) {}

MatrixData Controller::getData(RawMatrixData data) {
  for (int i = 0; i < 3; i++) {
    data.setTranslate(-(1 - data.getTranslate()[i] / 50.0f), i);
    data.setRotate(data.getRotate()[i] * M_PI / 180.0f, i);
  }
  data.setScale(data.getScale() / 50.0f);
  MatrixData transData;
  transData.setTranslate(data.getTranslate());
  transData.setRotate(data.getRotate());
  transData.setScale(data.getScale());
  return transData;
}

glm::mat4 Controller::signal(RawMatrixData data) {
  return model.getMatrix(getData(data));
}

ObjData Controller::signal(std::string path) { return model.parsData(path); }

glm::mat4 Controller::signal(float aspect, bool projection) {
  return model.getProjection(projection, aspect);
}