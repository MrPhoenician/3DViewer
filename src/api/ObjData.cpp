#include "ObjData.h"

using namespace s21;

ObjData::ObjData() {}

void ObjData::setName(std::string string) { name = string; }

void ObjData::setVerticesVector(std::vector<float> vector) {
  vertices.swap(vector);
}

void ObjData::setIndicesVector(std::vector<unsigned int> vector) {
  indices.swap(vector);
}

void ObjData::setIndicesCount(unsigned int count) { indicesCount = count; }

void ObjData::setEdgesCount(unsigned int count) { edgesCount = count; }

void ObjData::setVerticesCount(unsigned int count) { verticesCount = count; }

void ObjData::setStatus(bool status) { this->status = status; }

std::vector<float> ObjData::getVerticesVector() { return vertices; }

std::vector<unsigned int> ObjData::getIndicesVector() { return indices; }

std::string ObjData::getName() { return name; }

unsigned int ObjData::getVerticesCount() { return verticesCount; }

unsigned int ObjData::getEdgesCount() { return edgesCount; }

unsigned int ObjData::getIndicesCount() { return indicesCount; }

bool ObjData::getStatus() { return status; }
