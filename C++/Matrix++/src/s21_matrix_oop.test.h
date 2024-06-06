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

TEST(Constructors, move_operator) {
  S21Matrix matrix_1(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.2;
  S21Matrix matrix_2 = std::move(matrix_1);
  EXPECT_EQ(matrix_2.get_rows(), 2);
  EXPECT_EQ(matrix_2.get_cols(), 2);
  EXPECT_EQ(matrix_1.get_matrix(), nullptr);
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++)
      EXPECT_EQ(matrix_2(i, j), 2.2);
}

// EQUALITY TEST

TEST(EqMatrix, equal_check) {
  S21Matrix matrix_1(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.2;
  S21Matrix matrix_2 = matrix_1;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_TRUE(res);
}

TEST(EqMatrix, operator_check) {
  S21Matrix matrix_1(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.2;
  S21Matrix matrix_2 = matrix_1;
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(EqMatrix, not_equal_check) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.2;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2.1;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_FALSE(res);
}

TEST(EqMatrix, not_equal_check_epsilon_1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1.0000001;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_2(i, j) = 1.0000002;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_FALSE(res);
}

TEST(EqMatrix, not_equal_check_epsilon_2) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1.00000021;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_2(i, j) = 1.00000022;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_TRUE(res);
}

TEST(EqMatrix, not_equal_check_epsilon_3) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1.00000022;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_2(i, j) = 1.00000021;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_TRUE(res);
}

TEST(EqMatrix, nan_check) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1.00000022;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_2(i, j) = NAN;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_FALSE(res);
}

TEST(EqMatrix, inf_check) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1.00000022;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_2(i, j) = INFINITY;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_FALSE(res);
}

TEST(EqMatrix, diff_rows_check) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(1, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1.00000022;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1.00000022;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_FALSE(res);
}

TEST(EqMatrix, diff_cols_check) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1.00000022;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1.00000022;
  bool res = matrix_1.EqMatrix(matrix_2);
  EXPECT_FALSE(res);
}

// ADDITION TEST

TEST(SumMatrix, addition_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  matrix_1.SumMatrix(matrix_2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) EXPECT_EQ(matrix_1(i, j), 2);
}

TEST(SumMatrix, operator_sum_test_1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  matrix_1 += matrix_2;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) EXPECT_EQ(matrix_1(i, j), 2);
}

TEST(SumMatrix, operator_sum_test_2) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  matrix_1 = matrix_1 + matrix_2;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) EXPECT_EQ(matrix_1(i, j), 2);
}

TEST(SumMatrix, diff_rows_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(1, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

TEST(SumMatrix, diff_cols_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

TEST(SumMatrix, nan_test_1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = NAN;

  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

TEST(SumMatrix, nan_test_2) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = NAN;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

TEST(SumMatrix, infinity_test_1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = INFINITY;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

TEST(SumMatrix, infinity_test_2) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = INFINITY;
  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

// SUBSTRACTION TEST

TEST(SubMatrix, substraction_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  matrix_1.SubMatrix(matrix_2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) EXPECT_EQ(matrix_1(i, j), 1);
}

TEST(SubMatrix, operator_sub_test_1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  matrix_1 -= matrix_2;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) EXPECT_EQ(matrix_1(i, j), 1);
}

TEST(SubMatrix, operator_sub_test_2) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 2;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  matrix_1 = matrix_1 - matrix_2;
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) EXPECT_EQ(matrix_1(i, j), 1);
}

TEST(SubMatrix, diff_rows_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(1, 2);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  EXPECT_THROW(matrix_1.SubMatrix(matrix_2), std::logic_error);
}

TEST(SubMatrix, diff_cols_test) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  EXPECT_THROW(matrix_1.SubMatrix(matrix_2), std::logic_error);
}

TEST(SubMatrix, nan_test_1) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = 1;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = NAN;
  EXPECT_THROW(matrix_1.SubMatrix(matrix_2), std::logic_error);
}

TEST(SubMatrix, nan_test_2) {
  S21Matrix matrix_1(2, 2);
  S21Matrix matrix_2(2, 1);
  for (int i = 0; i < matrix_1.get_rows(); i++)
    for (int j = 0; j < matrix_1.get_cols(); j++) matrix_1(i, j) = NAN;
  for (int i = 0; i < matrix_2.get_rows(); i++)
    for (int j = 0; j < matrix_2.get_cols(); j++) matrix_2(i, j) = 1;
  EXPECT_THROW(matrix_1.SubMatrix(matrix_2), std::logic_error);
}

#endif