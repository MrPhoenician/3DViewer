#define TINYOBJLOADER_IMPLEMENTATION
#include "ObjLoader.h"

using namespace s21;

bool ObjLoader::loadObj(const char *filename) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::string err;
  tinyobj::LoadObj(&attrib, &shapes, NULL, &err, filename, NULL, false);
  if (attrib.vertices.empty()) {
    return false;
  }

  parseData(attrib, shapes);
  setCenterModel(data.vertices);
  setScaleModel(data.vertices, 2.0f);

  return true;
}

void ObjLoader::parseData(tinyobj::attrib_t attrib,
                          std::vector<tinyobj::shape_t> shapes) {
  this->data.verticesCount = attrib.vertices.size() / 3;
  this->data.vertices.swap(attrib.vertices);
  this->data.name = shapes.begin()->name;
  unsigned int facesCount = 0;
  for (const auto &shape : shapes) {
    const auto &mesh = shape.mesh;

    int j = 0;
    int count = 0;
    for (size_t i = 0; i < mesh.indices.size(); ++i) {
      int temp = mesh.num_face_vertices[j];
      this->data.indices.push_back(mesh.indices[i].vertex_index);
      count++;
      if (count != 1) {
        this->data.indices.push_back(mesh.indices[i].vertex_index);
      }
      if (temp == count) {
        this->data.indices.push_back(mesh.indices[i - count + 1].vertex_index);
        count = 0;
        j++;
      }
    }
    facesCount += j;
  }
  this->data.edgesCount = facesCount + this->data.verticesCount - 2;
}

glm::vec3 ObjLoader::getCenter(std::vector<float> &vertices) {
  glm::vec3 minVertex(std::numeric_limits<float>::max());
  glm::vec3 maxVertex(std::numeric_limits<float>::lowest());

  for (size_t i = 0; i < vertices.size(); i += 3) {
    glm::vec3 vertex(vertices[i], vertices[i + 1], vertices[i + 2]);
    minVertex = glm::min(minVertex, vertex);
    maxVertex = glm::max(maxVertex, vertex);
  }

  return (minVertex + maxVertex) / 2.0f;
}

float ObjLoader::getSize(const std::vector<float> &vertices) {
  glm::vec3 minVertex(std::numeric_limits<float>::max());
  glm::vec3 maxVertex(std::numeric_limits<float>::lowest());

  for (size_t i = 0; i < vertices.size(); i += 3) {
    glm::vec3 vertex(vertices[i], vertices[i + 1], vertices[i + 2]);
    minVertex = glm::min(minVertex, vertex);
    maxVertex = glm::max(maxVertex, vertex);
  }

  return glm::distance(minVertex, maxVertex);
}

void ObjLoader::setCenterModel(std::vector<float> &vertices) {
  glm::vec3 center = getCenter(vertices);

  for (size_t i = 0; i < vertices.size(); i += 3) {
    vertices[i] -= center.x;
    vertices[i + 1] -= center.y;
    vertices[i + 2] -= center.z;
  }
}

void ObjLoader::setScaleModel(std::vector<float> &vertices, float targetSize) {
  float size = getSize(vertices);
  float scale = targetSize / size;

  for (size_t i = 0; i < vertices.size(); i += 3) {
    vertices[i] *= scale;
    vertices[i + 1] *= scale;
    vertices[i + 2] *= scale;
  }
}

data_t ObjLoader::getData() { return this->data; }