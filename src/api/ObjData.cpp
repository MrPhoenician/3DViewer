#include "ObjData.h"

using namespace s21;

ObjData::ObjData() = default;

void ObjData::setName(std::string string) { name = std::move(string); }

void ObjData::setVerticesVector(std::vector<float> vector) {
  vertices.swap(vector);
}

void ObjData::setIndicesVector(std::vector<unsigned int> vector) {
  indices.swap(vector);
}

void ObjData::setIndicesCount(const unsigned int count) {
  indicesCount = count;
}

void ObjData::setEdgesCount(const unsigned int count) { edgesCount = count; }

void ObjData::setVerticesCount(const unsigned int count) {
  verticesCount = count;
}

std::vector<float> ObjData::getVerticesVector() { return vertices; }

std::vector<unsigned int> ObjData::getIndicesVector() { return indices; }

std::string ObjData::getName() { return name; }

unsigned int ObjData::getVerticesCount() const { return verticesCount; }

unsigned int ObjData::getEdgesCount() const { return edgesCount; }

unsigned int ObjData::getIndicesCount() const { return indicesCount; }

bool ObjData::getStatus() const { return status; }
