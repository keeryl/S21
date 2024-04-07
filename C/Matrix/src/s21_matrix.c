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