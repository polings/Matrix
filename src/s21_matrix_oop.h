#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <utility>  // for std::move

const double kEps = 1e-7;

class S21Matrix {
 public:
  // Constructors and destructor
  S21Matrix();                                   // Default constructor
  S21Matrix(int rows, int cols);                 // Parametrized constructor
  S21Matrix(const S21Matrix &other);             // Copy constructor
  S21Matrix(S21Matrix &&other);                  // Move constructor
  S21Matrix &operator=(const S21Matrix &other);  // Assignment operator
  S21Matrix &operator=(S21Matrix &&other);       // Assignment move operator
  ~S21Matrix();                                  // Destructor

  // Matrix operations
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  bool EqMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Setters and Getters
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);

  // Operators overloads
  double &operator()(int row, int col);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);

  // Additional functions
  void PrintMatrix();
  void RandomFillMatrix();
  void NumberFillMatrix(double num);

 private:
  // Attributes
  int rows_, cols_;
  double **matrix_;

  // Additional private functions
  void MemoryAllocation();
  bool CheckSizeMatrix(const S21Matrix &other);
  void MinorMatrix(int row, int col, S21Matrix &smaller);
};

#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H
