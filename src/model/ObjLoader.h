#ifndef CPP4_3DVIEWER_V2_0_1_OBJLOADER_H
#define CPP4_3DVIEWER_V2_0_1_OBJLOADER_H

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
  bool loadObj(const char *filename);
  data_t getData();

 private:
  data_t data{};
  void parseData(tinyobj::attrib_t attrib,
                 const std::vector<tinyobj::shape_t> &shapes);
  static glm::vec3 getCenter(const std::vector<float> &vertices);
  static float getSize(const std::vector<float> &vertices);
  static void setCenterModel(std::vector<float> &vertices);
  static void setScaleModel(std::vector<float> &vertices);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OBJLOADER_H
