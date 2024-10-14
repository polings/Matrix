#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// Constructors and destructor

TEST(Constructors, default_constructor) {
  S21Matrix A;
  EXPECT_EQ(3, A.GetRows());
  EXPECT_EQ(3, A.GetCols());
}

TEST(Constructors, parametrized) {
  S21Matrix A(5, 11);
  EXPECT_EQ(5, A.GetRows());
  EXPECT_EQ(11, A.GetCols());
}

TEST(Constructors, exeption) {
  EXPECT_ANY_THROW({ S21Matrix A(-1, 11); });
  EXPECT_ANY_THROW({ S21Matrix A(11, -1); });
  EXPECT_ANY_THROW({ S21Matrix A(0, 11); });
  EXPECT_ANY_THROW({ S21Matrix A(11, 0); });
}

TEST(Constructors, copy_1) {
  S21Matrix A(4, 4);
  A.RandomFillMatrix();
  S21Matrix B(A);
  EXPECT_TRUE(A == B);
}

TEST(Constructors, copy_2) {
  S21Matrix A = S21Matrix(3, 4);
  S21Matrix B(A);
  EXPECT_EQ(A.GetRows(), B.GetRows());
  EXPECT_EQ(A.GetCols(), B.GetCols());
}

TEST(Constructors, move_1) {
  S21Matrix A(2, 2);
  S21Matrix B(std::move(A));
  EXPECT_EQ(2, B.GetRows());
  EXPECT_EQ(2, B.GetCols());
  EXPECT_EQ(0, A.GetRows());
  EXPECT_EQ(0, A.GetCols());
}

TEST(Constructors, move_2) {
  S21Matrix A(2, 2);
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      A(i, j) = 21;
    }
  }
  S21Matrix B(std::move(A));
  EXPECT_EQ(2, B.GetRows());
  EXPECT_EQ(2, B.GetCols());
  EXPECT_EQ(0, A.GetRows());
  EXPECT_EQ(0, A.GetCols());
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      EXPECT_EQ(A(i, j), 0);
    }
  }
}

// Operators overloads

TEST(Operators, assignment_1) {
  S21Matrix A(2, 2);
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      A(i, j) = 21;
    }
  }
  S21Matrix B(7, 7);
  A = B;
  EXPECT_TRUE(A == B);
  EXPECT_EQ(7, B.GetRows());
  EXPECT_EQ(7, B.GetCols());
}

TEST(Operators, assignment_2) {
  S21Matrix A;
  A.RandomFillMatrix();
  S21Matrix B;
  A = B;
  EXPECT_TRUE(A == B);
}

TEST(Operators, assignment_3) {
  S21Matrix A(5, 5);
  A.RandomFillMatrix();
  S21Matrix B = A;
  EXPECT_TRUE(A == B);
}

TEST(Operators, assignment_4) {
  S21Matrix A;
  A.NumberFillMatrix(1.1);
  S21Matrix B;
  B.NumberFillMatrix(2.2);
  S21Matrix C;
  C.NumberFillMatrix(3.3);
  A = B = C;
  EXPECT_TRUE(A == B);
  EXPECT_TRUE(A == C);
  EXPECT_TRUE(C == B);
  EXPECT_EQ(A(0, 0), B(0, 0));
  EXPECT_EQ(A(0, 0), C(0, 0));
}

TEST(Operators, index_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(3, 3);
    A(-1, 2);
  });
  EXPECT_ANY_THROW({
    S21Matrix B(3, 3);
    B(2, -1);
  });
  EXPECT_ANY_THROW({
    S21Matrix C(7, 7);
    C(7, 7);
  });
}

TEST(Operators, index_ok) {
  EXPECT_NO_THROW({
    S21Matrix A(9, 9);
    A.NumberFillMatrix(21);
    EXPECT_EQ(A(2, 7), 21);
  });
}

TEST(Operators, sum_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    A.NumberFillMatrix(21);
    A = A + A;
    S21Matrix B(2, 2);
    B.NumberFillMatrix(42);
    EXPECT_EQ(A(0, 0), 42);
    EXPECT_TRUE(A == B);
  });
}

TEST(Operators, sum_2) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    S21Matrix D(2, 2);
    B.NumberFillMatrix(9);
    A.NumberFillMatrix(21);
    S21Matrix C = B + A;
    D.NumberFillMatrix(30);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Operators, sum_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(4, 4);
    A = A + B;
  });
}

TEST(Operators, sub_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    A.RandomFillMatrix();
    A = A - A;
    EXPECT_EQ(A(0, 0), 0);
    EXPECT_TRUE(A == B);
  });
}

TEST(Operators, sub_2) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    S21Matrix D(2, 2);
    B.NumberFillMatrix(7);
    A.NumberFillMatrix(27);
    S21Matrix C = B - A;
    D.NumberFillMatrix(-20);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Operators, sub_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(4, 4);
    A = A + B;
  });
}

TEST(Operators, mul_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    A.NumberFillMatrix(3);
    B.NumberFillMatrix(18);
    A = A * A;
    EXPECT_EQ(A(0, 0), 18);
    EXPECT_TRUE(A == B);
  });
}

TEST(Operators, mul_2) {
  EXPECT_NO_THROW({
    S21Matrix A(3, 2);
    S21Matrix B(2, 3);
    S21Matrix D(3, 3);
    B.NumberFillMatrix(5);
    A.NumberFillMatrix(2);
    S21Matrix C = A * B;
    D.NumberFillMatrix(20);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Operators, mul_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 3);
    S21Matrix B(4, 3);
    A = A * B;
  });
}

TEST(Operators, mul_num_1) {
  S21Matrix A;
  S21Matrix B;
  A.NumberFillMatrix(3);
  A = A * 5;
  B.NumberFillMatrix(15);
  EXPECT_EQ(A(0, 0), 15);
  EXPECT_TRUE(A == B);
}

TEST(Operators, mul_num_2) {
  S21Matrix A;
  S21Matrix B;
  A.NumberFillMatrix(3);
  A = A * 0;
  EXPECT_EQ(A(0, 0), 0);
  EXPECT_TRUE(A == B);
}

TEST(Operators, eq_1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A.NumberFillMatrix(5);
  B.NumberFillMatrix(5);
  EXPECT_TRUE(A == B);
}

TEST(Operators, eq_2) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  B.NumberFillMatrix(5);
  A.NumberFillMatrix(5);
  EXPECT_FALSE(A == B);
}

TEST(Operators, eq_3) {
  S21Matrix A;
  S21Matrix B;
  B.NumberFillMatrix(2);
  A.NumberFillMatrix(5);
  EXPECT_FALSE(A == B);
}

TEST(Operators, sum_assign_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    A.NumberFillMatrix(21);
    A += A;
    S21Matrix B(2, 2);
    B.NumberFillMatrix(42);
    EXPECT_EQ(A(0, 0), 42);
    EXPECT_TRUE(A == B);
  });
}

TEST(Operators, sum_assign_2) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    S21Matrix D(2, 2);
    B.NumberFillMatrix(9);
    A.NumberFillMatrix(21);
    B += A;
    S21Matrix C = B;
    D.NumberFillMatrix(30);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Operators, sum_assign_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(4, 4);
    A += B;
  });
}

TEST(Operators, sub_assign_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    A.RandomFillMatrix();
    A -= A;
    EXPECT_EQ(A(0, 0), 0);
    EXPECT_TRUE(A == B);
  });
}

TEST(Operators, sub_assign_2) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    S21Matrix D(2, 2);
    B.NumberFillMatrix(7);
    A.NumberFillMatrix(27);
    B -= A;
    S21Matrix C = B;
    D.NumberFillMatrix(-20);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Operators, sub_assign_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(4, 4);
    A += B;
  });
}

TEST(Operators, mul_assign_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    A.NumberFillMatrix(3);
    B.NumberFillMatrix(18);
    A *= A;
    EXPECT_EQ(A(0, 0), 18);
    EXPECT_TRUE(A == B);
  });
}

TEST(Operators, mul_assign_2) {
  EXPECT_NO_THROW({
    S21Matrix A(3, 2);
    S21Matrix B(2, 3);
    S21Matrix D(3, 3);
    B.NumberFillMatrix(5);
    A.NumberFillMatrix(2);
    A *= B;
    S21Matrix C = A;
    D.NumberFillMatrix(20);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Operators, mul_assign_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 3);
    S21Matrix B(4, 3);
    A *= B;
  });
}

TEST(Operators, mul_assign_num_1) {
  S21Matrix A;
  S21Matrix B;
  A.NumberFillMatrix(3);
  A *= 5;
  B.NumberFillMatrix(15);
  EXPECT_EQ(A(0, 0), 15);
  EXPECT_TRUE(A == B);
}

TEST(Operators, mul_assign_num_2) {
  S21Matrix A;
  S21Matrix B;
  A.NumberFillMatrix(3);
  A *= 0;
  EXPECT_EQ(A(0, 0), 0);
  EXPECT_TRUE(A == B);
}

// Setters and Getters

TEST(Setters, set_1) {
  EXPECT_NO_THROW({
    S21Matrix A(3, 3);
    A.SetCols(4);
    A.SetRows(4);
    S21Matrix B(4, 4);
    EXPECT_EQ(A(3, 3), 0);
    EXPECT_EQ(A.GetRows(), 4);
    EXPECT_EQ(A.GetCols(), 4);
    EXPECT_TRUE(A == B);
  });
}

TEST(Setters, set_2) {
  EXPECT_NO_THROW({
    S21Matrix A(10, 10);
    A.RandomFillMatrix();
    A.SetCols(4);
    A.SetRows(4);
    EXPECT_EQ(A.GetRows(), 4);
    EXPECT_EQ(A.GetCols(), 4);
  });
}

TEST(Setters, set_exeption) {
  S21Matrix A(3, 3);
  A.RandomFillMatrix();
  EXPECT_ANY_THROW({ A.SetRows(-2); });
  EXPECT_ANY_THROW({ A.SetCols(0); });
}

TEST(Getters, get_1) {
  S21Matrix A(11, 5);
  int row = A.GetRows();
  int col = A.GetCols();
  EXPECT_EQ(row, 11);
  EXPECT_EQ(col, 5);
}

// Matrix operations

TEST(Matrix_operations, SumMatrix_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    A.NumberFillMatrix(21);
    A.SumMatrix(A);
    S21Matrix B(2, 2);
    B.NumberFillMatrix(42);
    EXPECT_EQ(A(0, 0), 42);
    EXPECT_TRUE(A == B);
  });
}

TEST(Matrix_operations, SumMatrix_2) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    S21Matrix D(2, 2);
    B.NumberFillMatrix(9);
    A.NumberFillMatrix(21);
    B.SumMatrix(A);
    S21Matrix C(B);
    D.NumberFillMatrix(30);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Matrix_operations, SumMatrix_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(4, 4);
    A.SumMatrix(B);
  });
}

TEST(Matrix_operations, SubMatrix_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    A.RandomFillMatrix();
    A.SubMatrix(A);
    EXPECT_EQ(A(0, 0), 0);
    EXPECT_TRUE(A == B);
  });
}

TEST(Matrix_operations, SubMatrix_2) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    S21Matrix D(2, 2);
    B.NumberFillMatrix(7);
    A.NumberFillMatrix(27);
    B.SubMatrix(A);
    S21Matrix C(B);
    D.NumberFillMatrix(-20);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Matrix_operations, SubMatrix_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(4, 4);
    A.SubMatrix(B);
  });
}

TEST(Matrix_operations, MulMatrix_1) {
  EXPECT_NO_THROW({
    S21Matrix A(2, 2);
    S21Matrix B(2, 2);
    A.NumberFillMatrix(3);
    B.NumberFillMatrix(18);
    A.MulMatrix(A);
    EXPECT_EQ(A(0, 0), 18);
    EXPECT_TRUE(A == B);
  });
}

TEST(Matrix_operations, MulMatrix_2) {
  EXPECT_NO_THROW({
    S21Matrix A(3, 2);
    S21Matrix B(2, 3);
    S21Matrix D(3, 3);
    B.NumberFillMatrix(5);
    A.NumberFillMatrix(2);
    A.MulMatrix(B);
    S21Matrix C(A);
    D.NumberFillMatrix(20);
    EXPECT_EQ(C(0, 0), D(0, 0));
    EXPECT_TRUE(C == D);
  });
}

TEST(Matrix_operations, MulMatrix_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(2, 3);
    S21Matrix B(4, 3);
    A.MulMatrix(B);
  });
}

TEST(Matrix_operations, MulNumber_1) {
  S21Matrix A;
  S21Matrix B;
  A.NumberFillMatrix(3);
  A.MulNumber(5);
  B.NumberFillMatrix(15);
  EXPECT_EQ(A(0, 0), 15);
  EXPECT_TRUE(A == B);
}

TEST(Matrix_operations, MulNumber_2) {
  S21Matrix A;
  S21Matrix B;
  A.NumberFillMatrix(3);
  A.MulNumber(0);
  EXPECT_EQ(A(0, 0), 0);
  EXPECT_TRUE(A == B);
}

TEST(Matrix_operations, EqMatrix_1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  A.NumberFillMatrix(5);
  B.NumberFillMatrix(5);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(Matrix_operations, EqMatrix_2) {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  B.NumberFillMatrix(5);
  A.NumberFillMatrix(5);
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(Matrix_operations, EqMatrix_3) {
  S21Matrix A;
  S21Matrix B;
  B.NumberFillMatrix(2);
  A.NumberFillMatrix(5);
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(Matrix_operations, Transpose_1) {
  S21Matrix A(3, 2);
  S21Matrix C(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 4;
  A(1, 0) = 2;
  A(1, 1) = 5;
  A(2, 0) = 3;
  A(2, 1) = 6;
  C(0, 0) = 1;
  C(0, 1) = 2;
  C(0, 2) = 3;
  C(1, 0) = 4;
  C(1, 1) = 5;
  C(1, 2) = 6;
  S21Matrix B = A.Transpose();
  EXPECT_TRUE(B == C);
}

TEST(Matrix_operations, Transpose_2) {
  S21Matrix A(8, 15);
  S21Matrix C(15, 8);
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      A(i, j) = i;
    }
  }
  for (int i = 0; i < C.GetRows(); i++) {
    for (int j = 0; j < C.GetCols(); j++) {
      C(i, j) = j;
    }
  }
  S21Matrix B = A.Transpose();
  EXPECT_TRUE(B == C);
}

TEST(Matrix_operations, Determinant_1) {
  S21Matrix A(1, 1);
  A(0, 0) = 21.21212121;
  double res = A.Determinant();
  EXPECT_EQ(res, 21.21212121);
}

TEST(Matrix_operations, Determinant_2) {
  S21Matrix A;
  A(0, 0) = 0.25;
  A(0, 1) = 1.25;
  A(0, 2) = 2.25;
  A(1, 0) = 3.25;
  A(1, 1) = 10;
  A(1, 2) = 5.25;
  A(2, 0) = 6.25;
  A(2, 1) = 7.25;
  A(2, 2) = 8.25;
  double res = A.Determinant();
  EXPECT_EQ(res, -69);
}

TEST(Matrix_operations, Determinant_exeption) {
  EXPECT_ANY_THROW({
    S21Matrix A(6, 10);
    A.Determinant();
  });
}

TEST(Matrix_operations, CalcComplements_1) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;
  A(2, 0) = 7.0;
  A(2, 1) = 8.0;
  A(2, 2) = 9.0;
  S21Matrix result = A.CalcComplements();
  EXPECT_EQ(result(0, 0), -3.0);
  EXPECT_EQ(result(0, 1), 6.0);
  EXPECT_EQ(result(0, 2), -3.0);
  EXPECT_EQ(result(1, 0), 6.0);
  EXPECT_EQ(result(1, 1), -12.0);
  EXPECT_EQ(result(1, 2), 6.0);
  EXPECT_EQ(result(2, 0), -3.0);
  EXPECT_EQ(result(2, 1), 6.0);
  EXPECT_EQ(result(2, 2), -3.0);
}

TEST(Matrix_operations, CalcComplements_2) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{-3, 6, -3}, {6, -12, 6}, {-3, 6, -3}};
  S21Matrix A = S21Matrix(3, 3);
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      A(i, j) = matrix[i][j];
    }
  }
  S21Matrix result = A.CalcComplements();
  for (int i = 0; i < result.GetRows(); i++) {
    for (int j = 0; j < result.GetCols(); j++) {
      EXPECT_EQ(result(i, j), expected[i][j]);
    }
  }
}

TEST(Matrix_operations, CalcComplements_exception) {
  S21Matrix A(3, 2);
  EXPECT_ANY_THROW({
    S21Matrix A(6, 10);
    A.CalcComplements();
  });
}

TEST(Matrix_operations, InverseMatrix_1) {
  double matrix[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double matrix_throw[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double result[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(2, 3);
    check.InverseMatrix();
  });
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(3, 3);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = matrix_throw[i][j];
      }
    }
    check.InverseMatrix();
  });
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(3, 3);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = matrix[i][j];
      }
    }
    S21Matrix res = check.InverseMatrix();
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        EXPECT_EQ(res(i, j), result[i][j]);
      }
    }
  });
}

int main(int argc, char **argv) {
  srand(time(NULL));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
