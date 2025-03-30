#include "../api/MatrixData.h"
#include "../api/ModelApi.h"
#include "../api/ObjData.h"
#include "../api/RawMatrixData.h"
#include "../model/Model.h"
#include "test.h"

TEST(Model_, LoadObj) {
  s21::Model model;
  s21::ObjData p = model.parsData("../data-samples/cube.obj");

  EXPECT_EQ(8, p.getVerticesCount());
  EXPECT_EQ(12, p.getEdgesCount());
}

TEST(Model_, Rotate_X) {
  s21::Model model;
  s21::RawMatrixData data;
  glm::mat4 matrix_data;
  float ugol = 60 * M_PI / 180;
  data.setRotate(ugol, 0);
  data.setRotate(0, 1);
  data.setRotate(0, 2);

  s21::MatrixData trans_data;
  trans_data.setRotate(data.getRotate());
  matrix_data = model.getMatrix(trans_data);

  // for (int i = 0; i < 4; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     printf(" %5.4f", matrix_data[i][j]);
  //   }
  //   printf("\n");
  // }

  EXPECT_NEAR(matrix_data[0][0], 1, 0.1);
  EXPECT_NEAR(matrix_data[0][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][1], cos(ugol), 0.1);
  EXPECT_NEAR(matrix_data[1][2], sin(ugol), 0.1);
  EXPECT_NEAR(matrix_data[1][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][1], -sin(ugol), 0.1);
  EXPECT_NEAR(matrix_data[2][2], cos(ugol), 0.1);
  EXPECT_NEAR(matrix_data[2][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][3], 1, 0.1);
}

TEST(Model_, Rotate_Y) {
  s21::Model model;
  s21::RawMatrixData data;
  glm::mat4 matrix_data;
  float ugol = 60 * M_PI / 180;
  data.setRotate(0, 0);
  data.setRotate(ugol, 1);
  data.setRotate(0, 2);

  s21::MatrixData trans_data;
  trans_data.setRotate(data.getRotate());
  matrix_data = model.getMatrix(trans_data);

  EXPECT_NEAR(matrix_data[0][0], cos(ugol), 0.1);
  EXPECT_NEAR(matrix_data[0][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][2], -sin(ugol), 0.1);
  EXPECT_NEAR(matrix_data[0][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][1], 1, 0.1);
  EXPECT_NEAR(matrix_data[1][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][0], sin(ugol), 0.1);
  EXPECT_NEAR(matrix_data[2][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][2], cos(ugol), 0.1);
  EXPECT_NEAR(matrix_data[2][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][3], 1, 0.1);
}

TEST(Model_, Rotate_Z) {
  s21::Model model;
  s21::RawMatrixData data;
  glm::mat4 matrix_data;
  float ugol = 60 * M_PI / 180;
  data.setRotate(0, 0);
  data.setRotate(0, 1);
  data.setRotate(ugol, 2);

  s21::MatrixData trans_data;
  trans_data.setRotate(data.getRotate());
  matrix_data = model.getMatrix(trans_data);

  EXPECT_NEAR(matrix_data[0][0], cos(ugol), 0.1);
  EXPECT_NEAR(matrix_data[0][1], sin(ugol), 0.1);
  EXPECT_NEAR(matrix_data[0][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][0], -sin(ugol), 0.1);
  EXPECT_NEAR(matrix_data[1][1], cos(ugol), 0.1);
  EXPECT_NEAR(matrix_data[1][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][2], 1, 0.1);
  EXPECT_NEAR(matrix_data[2][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][3], 1, 0.1);
}

TEST(Model_, Scale) {
  s21::Model model;
  s21::RawMatrixData raw_matrix_data;
  glm::mat4 matrix_data;
  float scale = 4;
  raw_matrix_data.setScale(scale);
  model.getProjection(false, 1);

  s21::MatrixData trans_data;
  trans_data.setScale(raw_matrix_data.getScale());
  matrix_data = model.getMatrix(trans_data);

  EXPECT_NEAR(matrix_data[0][0], scale, 0.1);
  EXPECT_NEAR(matrix_data[0][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][1], scale, 0.1);
  EXPECT_NEAR(matrix_data[1][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][2], scale, 0.1);
  EXPECT_NEAR(matrix_data[2][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][3], 1, 0.1);
}

TEST(Model_, Move_X) {
  s21::Model model;
  s21::RawMatrixData raw_matrix_data;
  glm::mat4 matrix_data;
  float shift = 100;
  raw_matrix_data.setTranslate(shift, 0);
  raw_matrix_data.setTranslate(0, 1);
  raw_matrix_data.setTranslate(0, 2);

  s21::MatrixData trans_data;
  trans_data.setTranslate(raw_matrix_data.getTranslate());
  model.getProjection(true, 1);
  matrix_data = model.getMatrix(trans_data);

  EXPECT_NEAR(matrix_data[0][0], 1, 0.1);
  EXPECT_NEAR(matrix_data[0][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][1], 1, 0.1);
  EXPECT_NEAR(matrix_data[1][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][2], 1, 0.1);
  EXPECT_NEAR(matrix_data[2][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][0], shift, 0.1);
  EXPECT_NEAR(matrix_data[3][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][3], 1, 0.1);
}

TEST(Model_, Move_Y) {
  s21::Model model;
  s21::RawMatrixData raw_matrix_data;
  glm::mat4 matrix_data;
  float shift = 100;
  raw_matrix_data.setTranslate(0, 0);
  raw_matrix_data.setTranslate(shift, 1);
  raw_matrix_data.setTranslate(0, 2);

  s21::MatrixData trans_data;
  trans_data.setTranslate(raw_matrix_data.getTranslate());
  matrix_data = model.getMatrix(trans_data);

  EXPECT_NEAR(matrix_data[0][0], 1, 0.1);
  EXPECT_NEAR(matrix_data[0][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][1], 1, 0.1);
  EXPECT_NEAR(matrix_data[1][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][2], 1, 0.1);
  EXPECT_NEAR(matrix_data[2][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][1], shift, 0.1);
  EXPECT_NEAR(matrix_data[3][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][3], 1, 0.1);
}

TEST(Model_, Move_Z) {
  s21::Model model;
  s21::RawMatrixData raw_matrix_data;
  glm::mat4 matrix_data;
  float shift = 100;
  raw_matrix_data.setTranslate(0, 0);
  raw_matrix_data.setTranslate(0, 1);
  raw_matrix_data.setTranslate(shift, 2);

  s21::MatrixData trans_data;
  trans_data.setTranslate(raw_matrix_data.getTranslate());
  matrix_data = model.getMatrix(trans_data);

  EXPECT_NEAR(matrix_data[0][0], 1, 0.1);
  EXPECT_NEAR(matrix_data[0][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[0][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][1], 1, 0.1);
  EXPECT_NEAR(matrix_data[1][2], 0, 0.1);
  EXPECT_NEAR(matrix_data[1][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[2][2], 1, 0.1);
  EXPECT_NEAR(matrix_data[2][3], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][0], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][1], 0, 0.1);
  EXPECT_NEAR(matrix_data[3][2], shift, 0.1);
  EXPECT_NEAR(matrix_data[3][3], 1, 0.1);
}
