#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_matrix.h"

int is_inf_or_nan(const matrix_t *A);
int is_equal(const matrix_t *A, const matrix_t *B, int row, int col);
int is_incorrect_mat(const matrix_t *A);
int is_diff_size(const matrix_t *A, const matrix_t *B);
void mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void get_minor(matrix_t *A, matrix_t *temp, int ex_row, int ex_col);

#endif