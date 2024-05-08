#include "s21_matrix_oop.h"

void S21Matrix::allocate_memory_() {
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++)
    this->matrix_[i] = new double[this->cols_];
}

const double& S21Matrix::get_matrix_element(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0 || !matrix_)
    throw std::out_of_range("Incorrect input for (), index is out of range.");
  return this->matrix_[row][col];
}