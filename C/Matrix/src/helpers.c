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