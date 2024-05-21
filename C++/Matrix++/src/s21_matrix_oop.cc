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

bool S21Matrix::isinf_or_nan() const {
  bool res = false;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (isnan((*this)(i, j)) || isinf((*this)(i, j))) res = true;
  return res;
}

S21Matrix S21Matrix::get_minor(int ex_row, int ex_col) {
  S21Matrix res(rows_ - 1, cols_ - 1);
  for (int i = 0, temp_row = 0; i < rows_; i++) {
    for (int j = 0, temp_col = 0; j < cols_; j++) {
      if (i != ex_row && j != ex_col) {
        res(temp_row, temp_col) = (*this)(i, j);
        temp_col++;
      }
    }
    if (i != ex_row) temp_row++;
  }
  return res;
}

S21Matrix::S21Matrix() {
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::length_error("Invalid rows/cols size - can't be less than 1");
  this->rows_ = rows;
  this->cols_ = cols;
  this->allocate_memory_();
}

S21Matrix::S21Matrix(const S21Matrix& other) { *this = other; }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->allocate_memory_();
    for (int i = 0; i < this->rows_; i++)
      for (int j = 0; j < this->cols_; j++) (*this)(i, j) = other(i, j);
  }
  return *this;
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  this->matrix_ = nullptr;
  this->rows_ = 0;
  this->cols_ = 0;
  *this = std::move(other);
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < this->rows_; i++) delete[] this->matrix_[i];
    delete[] this->matrix_;
    this->matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < this->rows_; i++) delete[] this->matrix_[i];
  delete[] this->matrix_;
  this->matrix_ = nullptr;
  this->rows_ = 0;
  this->cols_ = 0;
}

double& S21Matrix::operator()(int i, int j) {
  return const_cast<double&>(this->get_matrix_element(i, j));
}

double S21Matrix::operator()(int i, int j) const {
  return this->get_matrix_element(i, j);
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  (*this) += other;
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  (*this) -= other;
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  (*this) *= other;
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  (*this) *= num;
  return *this;
}

int S21Matrix::get_cols() { return this->cols_; }

int S21Matrix::get_rows() { return this->rows_; }

void S21Matrix::set_rows(int rows) {
  if (rows < 1)
    throw std::length_error("Invalid rows size - can't be less than 1");
  S21Matrix temp(rows, this->cols_);
  for (int i = 0; i < temp.get_rows(); i++)
    for (int j = 0; j < temp.get_cols(); j++) {
      if (i < rows_)
        temp(i, j) = (*this)(i, j);
      else
        temp(i, j) = 0;
    }
  *this = std::move(temp);
}

void S21Matrix::set_cols(int cols) {
  if (cols < 1)
    throw std::length_error("Invalid cols size - can't be less than 1");
  S21Matrix temp(this->rows_, cols);
  for (int i = 0; i < temp.get_rows(); i++)
    for (int j = 0; j < temp.get_cols(); j++) {
      if (j < cols_)
        temp(i, j) = (*this)(i, j);
      else
        temp(i, j) = 0;
    }
  *this = std::move(temp);
}

double** S21Matrix::get_matrix() { return this->matrix_; }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    res = false;
  }
  for (int i = 0; i < this->rows_ && res; i++) {
    for (int j = 0; j < this->cols_ && res; j++) {
      if (this->isinf_or_nan() || other.isinf_or_nan()) {
        res = false;
        continue;
      }
      if (fabs((*this)(i, j) - other(i, j)) > 1e-08) {
        res = false;
      }
    }
  }
  return res;
}