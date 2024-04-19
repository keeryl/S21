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

#endif