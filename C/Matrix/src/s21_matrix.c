#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status_code = OK;
  if (rows < 1 || columns < 1 || !result)
    status_code = INCORRECT;
  else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix)
      for (int i = 0; i < rows; i++)
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
  }
  return status_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(const matrix_t *A, const matrix_t *B) {
  int status_code = SUCCESS;
  if (is_incorrect_mat(A) || is_incorrect_mat(B))
    status_code = FAILURE;
  else if (is_diff_size(A, B))
    status_code = FAILURE;
  else if (is_inf_or_nan(A) || is_inf_or_nan(B))
    status_code = FAILURE;
  else {
    for (int i = 0; i < A->rows && status_code; i++)
      for (int j = 0; j < A->columns && status_code; j++)
        status_code = is_equal(A, B, i, j);
  }
  return status_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status_code = OK;
  if (is_incorrect_mat(A) || is_incorrect_mat(B) || !result)
    status_code = INCORRECT;
  else if (is_diff_size(A, B))
    status_code = CALC_ERR;
  else if (is_inf_or_nan(A) || is_inf_or_nan(B))
    status_code = CALC_ERR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }
  return status_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status_code = OK;
  if (is_incorrect_mat(A) || is_incorrect_mat(B) || !result)
    status_code = INCORRECT;
  else if (is_diff_size(A, B))
    status_code = CALC_ERR;
  else if (is_inf_or_nan(A) || is_inf_or_nan(B))
    status_code = CALC_ERR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }
  return status_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status_code = OK;
  if (is_incorrect_mat(A) || !result)
    status_code = INCORRECT;
  else if (isnan(number) || isinf(number))
    status_code = CALC_ERR;
  else if (is_inf_or_nan(A))
    status_code = CALC_ERR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }
  return status_code;
}