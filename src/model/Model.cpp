#include "Model.h"

using namespace s21;

ObjData Model::parsData(std::string string) {
  ObjData result;
  ObjLoader obj;
  if (!obj.loadObj(string.c_str())) {
    return result;
  }
  result.setVerticesVector(obj.getData().vertices);
  result.setIndicesVector(obj.getData().indices);
  result.setName(obj.getData().name);
  result.setEdgesCount(obj.getData().edgesCount);
  result.setVerticesCount(obj.getData().verticesCount);
  result.setIndicesCount(obj.getData().indices.size());

  return result;
}

Model::Model() {}

glm::mat4 Model::getMatrix(MatrixData data) {
  TransformationMatrix matrix(data.getTranslate(), data.getRotate(),
                              data.getScale());

  return matrix.getMatrix();
}

glm::mat4 Model::getProjection(bool projection, float aspect) {
  TransformationMatrix matrix;

  return matrix.getProjection(projection, aspect);
  ;
}
