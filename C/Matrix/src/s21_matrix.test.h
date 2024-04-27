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

START_TEST(sum_matrix) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
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
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = 1;
  B.matrix[1][2] = 1;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  matrix_t res = {0};
  int status_code = s21_sum_matrix(&A, &B, &res);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) ck_assert_double_eq(res.matrix[i][j], 2.0);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  matrix_t res = {0};
  int status_code = s21_sum_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  int status_code = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = NAN;
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
  matrix_t res = {0};
  int status_code = s21_sum_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = INFINITY;
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
  matrix_t res = {0};
  int status_code = s21_sum_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
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
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = 1;
  B.matrix[1][2] = 1;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 1;
  B.matrix[2][2] = 1;
  matrix_t res = {0};
  int status_code = s21_sub_matrix(&A, &B, &res);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) ck_assert_double_eq(res.matrix[i][j], 0.0);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  matrix_t res = {0};
  int status_code = s21_sub_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  int status_code = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = NAN;
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
  matrix_t res = {0};
  int status_code = s21_sub_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = INFINITY;
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
  matrix_t res = {0};
  int status_code = s21_sub_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_number) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 2;
  matrix_t res = {0};
  int status_code = s21_mult_number(&A, 2.0, &res);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) ck_assert_double_eq(res.matrix[i][j], 4.0);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  int status_code = s21_mult_number(&A, 2.0, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = NAN;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 1;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 1;
  matrix_t res = {0};
  int status_code = s21_mult_number(&A, 2.0, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = INFINITY;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 1;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 1;
  matrix_t res = {0};
  int status_code = s21_mult_number(&A, 2.0, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  matrix_t res = {0};
  int status_code = s21_mult_number(&A, NAN, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_5) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  matrix_t res = {0};
  int status_code = s21_mult_number(&A, INFINITY, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t A = {0};
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  matrix_t B = {0};
  s21_create_matrix(2, 3, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;
  matrix_t etalon_res = {0};
  s21_create_matrix(3, 3, &etalon_res);
  etalon_res.matrix[0][0] = 9;
  etalon_res.matrix[0][1] = 11;
  etalon_res.matrix[0][2] = 17;
  etalon_res.matrix[1][0] = 12;
  etalon_res.matrix[1][1] = 13;
  etalon_res.matrix[1][2] = 22;
  etalon_res.matrix[2][0] = 15;
  etalon_res.matrix[2][1] = 15;
  etalon_res.matrix[2][2] = 27;
  matrix_t res = {0};
  int status_code = s21_mult_matrix(&A, &B, &res);
  for (int i = 0; i < etalon_res.rows; i++)
    for (int j = 0; j < etalon_res.columns; j++)
      ck_assert_double_eq(res.matrix[i][j], etalon_res.matrix[i][j]);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
  s21_remove_matrix(&etalon_res);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  matrix_t B = {0};
  s21_create_matrix(3, 3, &B);
  int status_code = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = NAN;
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
  matrix_t res = {0};
  int status_code = s21_mult_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = INFINITY;
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
  matrix_t res = {0};
  int status_code = s21_mult_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_5) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  matrix_t B = {0};
  s21_create_matrix(3, 2, &B);
  matrix_t res = {0};
  int status_code = s21_mult_matrix(&A, &B, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(transpose_1) {
  // 1 2 3
  // 4 5 6
  // 7 8 9
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  // 1 4 7
  // 2 5 8
  // 3 6 9
  matrix_t etalon_res = {0};
  s21_create_matrix(3, 3, &etalon_res);
  etalon_res.matrix[0][0] = 1;
  etalon_res.matrix[0][1] = 4;
  etalon_res.matrix[0][2] = 7;
  etalon_res.matrix[1][0] = 2;
  etalon_res.matrix[1][1] = 5;
  etalon_res.matrix[1][2] = 8;
  etalon_res.matrix[2][0] = 3;
  etalon_res.matrix[2][1] = 6;
  etalon_res.matrix[2][2] = 9;
  matrix_t res = {0};
  int status_code = s21_transpose(&A, &res);
  for (int i = 0; i < etalon_res.rows; i++)
    for (int j = 0; j < etalon_res.columns; j++)
      ck_assert_double_eq(res.matrix[i][j], etalon_res.matrix[i][j]);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&etalon_res);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  int status_code = s21_transpose(&A, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t res = {0};
  int status_code = s21_transpose(NULL, &res);
  ck_assert_int_eq(status_code, INCORRECT);
}
END_TEST

START_TEST(calc_complements_1) {
  // 1 2 3
  // 0 4 2
  // 5 2 1
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  //  0 10 -20
  //  4 -14 8
  // -8 -2  4
  matrix_t etalon_res = {0};
  s21_create_matrix(3, 3, &etalon_res);
  etalon_res.matrix[0][0] = 0;
  etalon_res.matrix[0][1] = 10;
  etalon_res.matrix[0][2] = -20;
  etalon_res.matrix[1][0] = 4;
  etalon_res.matrix[1][1] = -14;
  etalon_res.matrix[1][2] = 8;
  etalon_res.matrix[2][0] = -8;
  etalon_res.matrix[2][1] = -2;
  etalon_res.matrix[2][2] = 4;
  matrix_t res = {0};
  int status_code = s21_calc_complements(&A, &res);
  for (int i = 0; i < etalon_res.rows; i++)
    for (int j = 0; j < etalon_res.columns; j++)
      ck_assert_double_eq(res.matrix[i][j], etalon_res.matrix[i][j]);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
  s21_remove_matrix(&etalon_res);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = NAN;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  matrix_t res = {0};
  int status_code = s21_calc_complements(&A, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = INFINITY;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  matrix_t res = {0};
  int status_code = s21_calc_complements(&A, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 2, &A);
  matrix_t res = {0};
  int status_code = s21_calc_complements(&A, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_5) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  int status_code = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_6) {
  matrix_t res = {0};
  int status_code = s21_calc_complements(NULL, &res);
  ck_assert_int_eq(status_code, INCORRECT);
}
END_TEST

START_TEST(determinant_1) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  double res = -1, etalon_res = 0.0;
  int status_code = s21_determinant(&A, &res);
  ck_assert_double_eq(res, etalon_res);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 10;
  A.matrix[1][0] = -5;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 7;
  A.matrix[2][2] = 13;
  double res = -1, etalon_res = 161.0;
  int status_code = s21_determinant(&A, &res);
  ck_assert_double_eq(res, etalon_res);
  ck_assert_int_eq(status_code, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  matrix_t A = {0};
  s21_create_matrix(3, 2, &A);
  double res = -1;
  int status_code = s21_determinant(&A, &res);
  ck_assert_int_eq(status_code, CALC_ERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  int status_code = s21_determinant(&A, NULL);
  ck_assert_int_eq(status_code, INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

#endif