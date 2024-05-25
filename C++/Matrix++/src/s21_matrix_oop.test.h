#ifndef S21_MATRIX_OOP_TEST_H
#define S21_MATRIX_OOP_TEST_H

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// CONSTRUCTORS TEST

TEST(Constructors, default_constructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.get_rows(), 0);
  EXPECT_EQ(matrix.get_cols(), 0);
  EXPECT_EQ(matrix.get_matrix(), nullptr);
}

TEST(Constructors, param_constructor) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.get_rows(), 3);
  EXPECT_EQ(matrix.get_cols(), 3);
  EXPECT_NE(matrix.get_matrix(), nullptr);
}

TEST(Constructors, param_constructor_exception) {
  EXPECT_THROW(S21Matrix matrix(3, 0), std::length_error);
}

TEST(Constructors, copy_constructor) {
  S21Matrix matrix_1(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.2;
  S21Matrix matrix_2(matrix_1);
  EXPECT_EQ(matrix_2.get_rows(), 2);
  EXPECT_EQ(matrix_2.get_cols(), 2);
  EXPECT_NE(matrix_2.get_matrix(), nullptr);
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++)
      EXPECT_EQ(matrix_1(i, j), matrix_2(i, j));
}

TEST(Constructors, copy_operator) {
  S21Matrix matrix_1(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.2;
  S21Matrix matrix_2 = matrix_1;
  EXPECT_EQ(matrix_2.get_rows(), 2);
  EXPECT_EQ(matrix_2.get_cols(), 2);
  EXPECT_NE(matrix_2.get_matrix(), nullptr);
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++)
      EXPECT_EQ(matrix_1(i, j), matrix_2(i, j));
}

TEST(Constructors, move_constructor) {
  S21Matrix matrix_1(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.2;
  S21Matrix matrix_2(std::move(matrix_1));
  EXPECT_EQ(matrix_2.get_rows(), 2);
  EXPECT_EQ(matrix_2.get_cols(), 2);
  EXPECT_EQ(matrix_1.get_matrix(), nullptr);
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++)
      EXPECT_EQ(matrix_2(i, j), 2.2);
}

#endif