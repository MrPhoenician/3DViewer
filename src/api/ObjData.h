#ifndef CPP4_3DVIEWER_V2_0_1_OBJDATA_H
#define CPP4_3DVIEWER_V2_0_1_OBJDATA_H

#include <string>
#include <vector>

namespace s21 {

class ObjData {
 public:
  ObjData();
  void setName(std::string string);
  void setVerticesVector(std::vector<float> vector);
  void setIndicesVector(std::vector<unsigned int> vector);
  void setIndicesCount(unsigned int count);
  void setEdgesCount(unsigned int count);
  void setVerticesCount(unsigned int count);
  void setStatus(bool status);
  std::vector<float> getVerticesVector();
  std::vector<unsigned int> getIndicesVector();
  std::string getName();
  unsigned int getVerticesCount();
  unsigned int getEdgesCount();
  unsigned int getIndicesCount();
  bool getStatus();

 private:
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  std::string name;
  bool status;
  unsigned int verticesCount;
  unsigned int edgesCount;
  unsigned int indicesCount;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_OBJDATA_H
