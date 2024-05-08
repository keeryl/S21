#include "s21_matrix_oop.h"

void S21Matrix::allocate_memory_() {
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++)
    this->matrix_[i] = new double[this->cols_];
}