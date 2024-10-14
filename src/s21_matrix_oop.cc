#include "s21_matrix_oop.h"

// Default constructor

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

// Parametrized constructor

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if ((rows_ < 1) || (cols_ < 1)) {
    throw std::out_of_range("Error: rows and columns must be more than 0.");
  } else {
    MemoryAllocation();
  }
}

// Copy constructor

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  MemoryAllocation();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Move constructor

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Assignment operator

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) return *this;
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = other.rows_;
  cols_ = other.cols_;
  MemoryAllocation();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

// Assignment move operator

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this == &other) return *this;
  rows_ = other.rows_;
  cols_ = other.cols_;
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  return *this;
}

// Destructor

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

// Matrix operations

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (this == &other) return result;
  if (CheckSizeMatrix(other)) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > kEps) {
          result = false;
          i = rows_;
          break;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!CheckSizeMatrix(other)) {
    throw std::out_of_range("Different matrix dimensions.");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!CheckSizeMatrix(other)) {
    throw std::out_of_range("Different matrix dimensions.");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "The number of columns of the first matrix does not equal the number "
        "of rows of the second matrix.");
  } else {
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < cols_; k++) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = result;
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

void S21Matrix::MinorMatrix(int row, int col, S21Matrix &smaller) {
  int x = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == row) continue;
    int y = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == col) continue;
      smaller.matrix_[x][y] = matrix_[i][j];
      y++;
    }
    x++;
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::out_of_range("The matrix is not square.");
  }
  S21Matrix result(*this);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix smaller_matrix(rows_ - 1, cols_ - 1);
      MinorMatrix(i, j, smaller_matrix);
      double minor_determinant = smaller_matrix.Determinant();
      result.matrix_[i][j] = pow((-1), i + j) * minor_determinant;
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::out_of_range("The matrix is not square.");
  }
  double determinant = 0;
  S21Matrix temp(*this);
  if (rows_ == 1) {
    determinant = temp(0, 0);
  } else {
    for (int i = 0; i < cols_; ++i) {
      double minor_determinant = 0.0;
      S21Matrix smaller_matrix(rows_ - 1, cols_ - 1);
      MinorMatrix(0, i, smaller_matrix);
      minor_determinant = smaller_matrix.Determinant();
      determinant += pow((-1), i) * temp.matrix_[0][i] * minor_determinant;
    }
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (cols_ != rows_) {
    throw std::out_of_range("The matrix is not square.");
  }
  S21Matrix result(*this);
  double determinant = Determinant();
  if (determinant == 0) {
    throw std::out_of_range("Matrix determinant is 0.");
  } else {
    result = result.CalcComplements().Transpose();
    result *= 1 / determinant;
  }
  return result;
}

// Setters and Getters

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("Error: rows must be more than 0.");
  }
  S21Matrix temp(rows, cols_);
  for (int i = 0; i < rows; ++i) {
    if (i >= rows_) break;
    for (int j = 0; j < cols_; ++j) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::out_of_range("Error: cols must be more than 0.");
  }
  S21Matrix temp(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j >= cols_) break;
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp;
}

// Operators overloads

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index is outside the matrix.");
  }
  return matrix_[row][col];
}

// Additional functions

void S21Matrix::MemoryAllocation() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::RandomFillMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = rand() % 10;
  }
}

void S21Matrix::NumberFillMatrix(double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = num;
  }
}

bool S21Matrix::CheckSizeMatrix(const S21Matrix &other) {
  return (rows_ == other.rows_) && (cols_ == other.cols_);
}
