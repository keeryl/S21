#ifndef S21_MATRIX_TEST_H
#define S21_MATRIX_TEST_H

#include <check.h>

#include "s21_matrix.h"

START_TEST(create_matrix) {
  matrix_t matrix = {0};
  int status_code = s21_create_matrix(2, 3, &matrix);
  ck_assert_int_eq(status_code, OK);
  ck_assert_int_eq(matrix.rows, 2);
  ck_assert_int_eq(matrix.columns, 3);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_matrix_1) {
  matrix_t matrix = {0};
  int status_code = s21_create_matrix(0, 3, &matrix);
  ck_assert_int_eq(status_code, INCORRECT);
}
END_TEST

START_TEST(create_matrix_2) {
  int status_code = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
}
END_TEST

START_TEST(create_matrix_3) {
  matrix_t matrix = {0};
  int status_code = s21_create_matrix(-1, 3, &matrix);
  ck_assert_int_eq(status_code, INCORRECT);
}
END_TEST

START_TEST(equal_matrix) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  matrix_t B = {0};
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = 1;
  int status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, SUCCESS);
  status_code = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(status_code, FAILURE);
  status_code = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(status_code, FAILURE);
  B.matrix[1][1] = NAN;
  status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, FAILURE);
  B.matrix[1][1] = INFINITY;
  status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, FAILURE);
  A.matrix[1][1] = NAN;
  status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, FAILURE);
  A.matrix[1][1] = INFINITY;
  status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, FAILURE);
  A.rows = 0;
  status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, FAILURE);
  A.rows = 2;
  status_code = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(status_code, FAILURE);
  status_code = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(status_code, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_matrix_1) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.00000012;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 1;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 1;
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1.00000011;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = 1;
  B.matrix[1][2] = 1;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  int status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_matrix_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 2, &A);
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  int status_code = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(status_code, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

#endif