#include "helpers.h"

int is_inf_or_nan(const matrix_t *A) {
  int res = 0;
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) {
      if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
        res = 1;
        i = A->rows;
        j = A->columns;
      }
    }
  return res;
}

int is_equal(const matrix_t *A, const matrix_t *B, int row, int col) {
  int res = 1;
  if (fabs(A->matrix[row][col] - B->matrix[row][col]) > 1e-08) res = 0;
  return res;
}

int is_incorrect_mat(const matrix_t *A) {
  int res = 0;
  if (!A || !A->matrix || A->columns < 1 || A->rows < 1) res = 1;
  return res;
}

int is_diff_size(const matrix_t *A, const matrix_t *B) {
  int res = 0;
  if (A->rows != B->rows || A->columns != B->columns) res = 1;
  return res;
}