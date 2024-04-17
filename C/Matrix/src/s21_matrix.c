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

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status_code = OK;
  if (is_incorrect_mat(A) || is_incorrect_mat(B) || !result)
    status_code = INCORRECT;
  else if (A->rows != B->columns)
    status_code = CALC_ERR;
  else if (is_inf_or_nan(A) || is_inf_or_nan(B))
    status_code = CALC_ERR;
  else {
    s21_create_matrix(A->rows, B->columns, result);
    mult_matrix(A, B, result);
  }
  return status_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status_code = OK;
  if (is_incorrect_mat(A) || !result)
    status_code = INCORRECT;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];
  }
  return status_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status_code = OK;
  if (is_incorrect_mat(A) || !result)
    status_code = INCORRECT;
  else if (A->rows != A->columns || is_inf_or_nan(A))
    status_code = CALC_ERR;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        matrix_t temp = {0};
        s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
        get_minor(A, &temp, i, j);
        double det_temp = 0;
        s21_determinant(&temp, &det_temp);
        result->matrix[i][j] = pow(-1, i + j) * det_temp;
        s21_remove_matrix(&temp);
      }
  }
  return status_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int status_code = OK;
  if (is_incorrect_mat(A) || !result)
    status_code = INCORRECT;
  else if (A->rows != A->columns || is_inf_or_nan(A))
    status_code = CALC_ERR;
  else if (A->rows == 1)
    *result = A->matrix[0][0];
  else {
    matrix_t temp = {0};
    double det = 0;
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
      double res = 0;
      s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
      get_minor(A, &temp, i, 0);
      s21_determinant(&temp, &res);
      det += sign * A->matrix[i][0] * res;
      sign *= -1;
      s21_remove_matrix(&temp);
    }
    *result = det;
  }
  return status_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!result) return INCORRECT;
  double determinant = 0;
  int status_code = s21_determinant(A, &determinant);
  if (status_code == OK && determinant == 0)
    status_code = CALC_ERR;
  else if (status_code == OK) {
    matrix_t calc_complements = {0};
    matrix_t transposed_mat = {0};
    s21_calc_complements(A, &calc_complements);
    s21_transpose(&calc_complements, &transposed_mat);
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = transposed_mat.matrix[i][j] * -1;
      }
    s21_remove_matrix(&calc_complements);
    s21_remove_matrix(&transposed_mat);
  }
  return status_code;
}