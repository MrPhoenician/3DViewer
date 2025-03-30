#ifndef CPP4_3DVIEWER_V2_0_1_OBJLOADER_H
#define CPP4_3DVIEWER_V2_0_1_OBJLOADER_H

#include <iostream>

#include "../dependencies/tiny_obj_loader.h"
#include "TransformationMatrix.h"

namespace s21 {

typedef struct {
  std::vector<float> vertices;
  unsigned int verticesCount;
  unsigned int edgesCount;
  std::string name;
  std::vector<unsigned int> indices;
} data_t;

class ObjLoader {
 public:
  bool loadObj(
      const char *filename);  // основная функция загрузки данных из файла
  data_t getData();

 private:
  data_t data;
  void parseData(tinyobj::attrib_t attrib,
                 std::vector<tinyobj::shape_t> shapes);
  glm::vec3 getCenter(std::vector<float> &vertices);
  float getSize(const std::vector<float> &vertices);
  void setCenterModel(std::vector<float> &vertices);
  void setScaleModel(std::vector<float> &vertices, float targetSize);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OBJLOADER_H
