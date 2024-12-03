#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

TEST(CreateMatrix, CreateMatrix_DefaultArgs) {
  S21Matrix* matrix = new S21Matrix();
  EXPECT_FALSE(matrix == NULL);
  EXPECT_EQ(matrix->getCols(), 5);
  EXPECT_EQ(matrix->getRows(), 5);
  delete matrix;
}

TEST(CreateMatrix, CreateMatrix_WithArgs) {
  S21Matrix* matrix;
  EXPECT_ANY_THROW(matrix = new S21Matrix(0, 0));
  EXPECT_ANY_THROW(matrix = new S21Matrix(-2, 8));
  EXPECT_ANY_THROW(matrix = new S21Matrix(8, -3));
  EXPECT_TRUE(matrix = new S21Matrix(65, 56));
  EXPECT_TRUE(matrix = new S21Matrix(42, 21));
  delete matrix;
}

TEST(CopyMatrix, CopyMatrix_are_you_ok) {
  S21Matrix initial;
  initial.setValue();

  S21Matrix copied(initial);

  for (int i = 0; i < initial.getRows(); i++) {
    for (int j = 0; j < initial.getCols(); j++) {
      EXPECT_DOUBLE_EQ(initial.getMatrix()[i][j], copied.getMatrix()[i][j]);
    }
  }
}

TEST(MoveMatrix, MoveMatrix_are_you_ok) {
  S21Matrix initial;
  initial.setValue();

  S21Matrix copied(initial);

  S21Matrix temp(std::move(initial));
  EXPECT_TRUE(initial.getMatrix() == nullptr);

  for (int i = 0; i < temp.getRows(); i++) {
    for (int j = 0; j < temp.getCols(); j++) {
      EXPECT_DOUBLE_EQ(copied.getMatrix()[i][j], temp.getMatrix()[i][j]);
    }
  }
}

TEST(MoveMatrix, MoveMatrix_when_they_are_different_are_you_ok) {
  S21Matrix initial(6, 7);
  initial.setValue();

  S21Matrix copied(initial);

  S21Matrix temp(std::move(initial));
  EXPECT_TRUE(initial.getMatrix() == nullptr);

  for (int i = 0; i < temp.getRows(); i++) {
    for (int j = 0; j < temp.getCols(); j++) {
      EXPECT_DOUBLE_EQ(copied.getMatrix()[i][j], temp.getMatrix()[i][j]);
    }
  }
  // std::cout << '\n' << temp.getRows() << ' ' << temp.getCols() << '\n';
}

TEST(EqMatrix, EqMatrix_True) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(8, 9);

  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      EXPECT_DOUBLE_EQ(matrix1.getMatrix()[i][j], matrix2.getMatrix()[i][j]);
    }
  }
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, EqMatrix_False) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(8, 9);
  matrix1.setValue();
  matrix2.setValue();
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, EqMatrix_Different_Size) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, EqMatrix_with_minus_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(SumMatrix, SumMatrix_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double values2[] = {5.7, 4.8, 3.9, 2.8, 1.7, 2.5};
  double values3[] = {6.9, 7.1, 7.3, 7.3, 7.3, 9.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(SumMatrix, SumMatrix_with_minus_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};
  double values2[] = {-5.7, 4.8, 3.9, 2.8, 1.7, -2.5};
  double values3[] = {-4.5, 7.1, 7.3, -1.7, 7.3, 4.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1.SumMatrix(matrix2);

  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(SumMatrix, SumMatrix_Different_Size) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
}

TEST(SubMatrix, SubMatrix_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double values2[] = {5.7, 4.8, 3.9, 2.8, 1.7, 2.5};
  double values3[] = {-4.5, -2.5, -0.5, 1.7, 3.9, 4.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1.SubMatrix(matrix2);

  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(SubMatrix, SubMatrix_with_minus_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};
  double values2[] = {-5.7, 4.8, 3.9, 2.8, 1.7, -2.5};
  double values3[] = {6.9, -2.5, -0.5, -7.3, 3.9, 9.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1.SubMatrix(matrix2);

  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(SubMatrix, SubMatrix_Different_Size) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
}

TEST(MulNumber, MulNumber_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = 2.5;
  double values2[] = {3, 5.75, 8.5, 11.25, 14, 16.75};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  matrix1.MulNumber(num);
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulNumber, MulNumber_with_minus_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = -2.5;
  double values2[] = {-3, -5.75, -8.5, -11.25, -14, -16.75};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  matrix1.MulNumber(num);
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulNumber, MulNumber_with_zero_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = 0;

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix1.MulNumber(num);
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulMatrix, MulMatrix_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 4);
  S21Matrix control(2, 4);
  double values1[] = {2.4, 1.2, 3.4, 4.5, 1.5, 5.4};
  double values2[] = {2.3, 1.4, 3, 2, 2.1, 1.1, 4, 7, 0.2, 0.14, 1.4, 1.5};
  double values3[] = {8.72, 5.156, 16.76, 18.3, 14.58, 8.706, 27.06, 27.6};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1.MulMatrix(matrix2);

  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulMatrix, MulMatrix_with_minus_test) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix control(2, 2);
  double values1[] = {-2.3, 1.5, -2, -0.75};
  double values2[] = {-5.7, 4.8, 3.9, 2.8};
  double values3[] = {18.96, -6.84, 8.475, -11.7};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulMatrix, MulMatrix_with_zero_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  S21Matrix control(2, 2);
  double values1[] = {-2.3, 1.5, -2, -0.75, 1.4, 4.15};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulMatrix, MulMatrix_with_wrong_dims) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  EXPECT_ANY_THROW(matrix1.MulMatrix(matrix2));
}

TEST(TransposeMatrix, TransposeMatrix_test) {
  S21Matrix matrix1(3, 2);
  S21Matrix control(2, 3);
  double values1[] = {-2.3, 1.5, -2, -0.75, 2.1, 2.2};
  double values3[] = {-2.3, -2, 2.1, 1.5, -0.75, 2.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  S21Matrix result = matrix1.Transpose();

  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(TransposeMatrix, TransposeMatrix_sq_test) {
  S21Matrix matrix1(2, 2);
  S21Matrix control(2, 2);
  double values1[] = {-2.3, 1.5, -2, -0.75};
  double values3[] = {-2.3, -2, 1.5, -0.75};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  S21Matrix result = matrix1.Transpose();

  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(Determinant, Determinant_1x1_test) {
  S21Matrix matrix1(1, 1);
  double values1[] = {5};
  double control = 5;
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  double check = matrix1.Determinant();

  EXPECT_EQ(control, check);
}

TEST(Determinant, Determinant_2x2_test) {
  S21Matrix matrix1(2, 2);
  double values1[] = {1, 2, 3, 4};
  double control = -2;
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  double check = matrix1.Determinant();

  EXPECT_EQ(control, check);
}

TEST(Determinant, Determinant_usual_test) {
  S21Matrix matrix1(3, 3);
  double values1[] = {-9, 8, -7, -4, -5, -6, 7, -8, 9};
  double control = 320;
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  double check = matrix1.Determinant();

  EXPECT_EQ(control, check);
}

TEST(Determinant, Determinant_not_square_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1, 2, 3, 4, 5, 6};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  EXPECT_ANY_THROW(matrix1.Determinant());
}

TEST(InverseMatrix, InverseMatrix_1x1_test) {
  S21Matrix matrix1(1, 1);
  S21Matrix check(1, 1);
  double values1[] = {5};
  double values2[] = {0.2};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  check.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  S21Matrix result = matrix1.InverseMatrix();
  EXPECT_TRUE(check.EqMatrix(result));
}

TEST(InverseMatrix, InverseMatrix_test) {
  S21Matrix matrix1(3, 3);
  S21Matrix check(3, 3);
  double values1[] = {6, 4, 4, 1, 2, 4, 2, 4, -2};
  double values2[] = {0.25, -0.3, -0.1, -0.125, 0.25, 0.25, 0, 0.2, -0.1};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  check.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  S21Matrix result = matrix1.InverseMatrix();

  // std::cout << "Check matrix\n";
  // for (int a = 0; a < check.getRows(); a++) {
  //   for (int b = 0; b < check.getCols(); b++) {
  //     std::cout << check.getMatrix()[a][b] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // std::cout << "Result matrix\n";
  // for (int a = 0; a < result.getRows(); a++) {
  //   for (int b = 0; b < result.getCols(); b++) {
  //     std::cout << result.getMatrix()[a][b] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  EXPECT_TRUE(check.EqMatrix(result));
}

TEST(InverseMatrix, InverseMatrix_1x1_zero_test) {
  S21Matrix matrix1(1, 1);
  EXPECT_ANY_THROW(matrix1.InverseMatrix());
}

TEST(InverseMatrix, InverseMatrix_not_square_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1, 2, 3, 4, 5, 6};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  EXPECT_ANY_THROW(matrix1.InverseMatrix());
}

TEST(CalcComplements, CalcComplements_test) {
  S21Matrix matrix1(4, 4);
  double values1[] = {-1.0, 2.0,  7.0,  9.0,  1.0,  0.0, 0.0, 0.0,
                      47.0, 13.0, 17.0, 21.0, 22.0, 7.0, 1.0, 3.0};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  S21Matrix result = matrix1.CalcComplements();

  S21Matrix check(4, 4);
  double values2[] = {0.0, -30.0, -108.0, 106.0, 138.0, -726.0, -1137.0, 1061.0,
                      0.0, 12.0,  57.0,   -47.0, 0.0,   6.0,    -75.0,   57.0};
  check.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(CalcComplements, CalcComplements_not_sq_test) {
  S21Matrix matrix1(4, 2);
  double values1[] = {-1.0, 2.0, 7.0, 9.0, 1.0, 0.0, 0.0, 0.0};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  EXPECT_ANY_THROW(matrix1.CalcComplements());
}

TEST(PlusOperator, Plus_operator) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double values2[] = {5.7, 4.8, 3.9, 2.8, 1.7, 2.5};
  double values3[] = {6.9, 7.1, 7.3, 7.3, 7.3, 9.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  S21Matrix result = matrix1 + matrix2;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(PlusOperator, Plus_operator_with_minus) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};
  double values2[] = {-5.7, 4.8, 3.9, 2.8, 1.7, -2.5};
  double values3[] = {-4.5, 7.1, 7.3, -1.7, 7.3, 4.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  S21Matrix result = matrix1 + matrix2;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(PlusOperator, Plus_operator_with_wrong_dims) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_ANY_THROW(matrix1 + matrix2);
}

TEST(MinusOperator, Minus_operator) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double values2[] = {5.7, 4.8, 3.9, 2.8, 1.7, 2.5};
  double values3[] = {-4.5, -2.5, -0.5, 1.7, 3.9, 4.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  S21Matrix result = matrix1 - matrix2;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(MinusOperator, Minus_operator_with_minus) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};
  double values2[] = {-5.7, 4.8, 3.9, 2.8, 1.7, -2.5};
  double values3[] = {6.9, -2.5, -0.5, -7.3, 3.9, 9.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  S21Matrix result = matrix1 - matrix2;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(MinusOperator, Minus_operator_with_wrong_dims) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_ANY_THROW(matrix1 - matrix2);
}

TEST(MulOperator, MulMatrix_operator_test) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix control(2, 2);
  double values1[] = {-2.3, 1.5, -2, -0.75};
  double values2[] = {-5.7, 4.8, 3.9, 2.8};
  double values3[] = {18.96, -6.84, 8.475, -11.7};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  S21Matrix result = matrix1 * matrix2;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(MulOperator, MulMatrix_operator_zero_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  S21Matrix control(2, 2);
  double values1[] = {-2.3, 1.5, -2, -0.75, 1.4, 4.15};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  S21Matrix result = matrix1 * matrix2;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(MulOperator, MulMatrix_operator_with_wrong_dims) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  EXPECT_ANY_THROW(matrix1 * matrix2);
}

TEST(MulNumberOperator, MulNumber_operator_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = 2.5;
  double values2[] = {3, 5.75, 8.5, 11.25, 14, 16.75};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  S21Matrix result = matrix1 * num;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(MulNumberOperator, MulNumber_operator_with_minus_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = -2.5;
  double values2[] = {-3, -5.75, -8.5, -11.25, -14, -16.75};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  S21Matrix result = matrix1 * num;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(MulNumberOperator, MulNumber_operator_with_zero_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = 0;

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  S21Matrix result = matrix1 * num;
  EXPECT_TRUE(result.EqMatrix(control));
}

TEST(EqOperator, EqOperator_True) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(8, 9);

  for (int i = 0; i < matrix1.getRows(); i++) {
    for (int j = 0; j < matrix1.getCols(); j++) {
      EXPECT_DOUBLE_EQ(matrix1.getMatrix()[i][j], matrix2.getMatrix()[i][j]);
    }
  }
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(EqOperator, EqOperator_False) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(8, 9);
  matrix1.setValue();
  matrix2.setValue();
  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(EqOperator, EqOperator_Different_Size) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(EqOperator, EqOperator_with_minus_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(AssignOperator, Assign_operator_eq_dims) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {2.4, 1.2, 3.4, 4.5, 1.5, 5.4};
  double values2[] = {2.3, 1.4, 3, 2, 2.1, 1.1};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  matrix1 = matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(AssignOperator, Assign_operator_diff_dims) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 4);
  S21Matrix control(3, 4);
  double values1[] = {2.3, 1.4, 3, 2, 2.1, 1.1};
  double values2[] = {2.4, 1.2, 3.4, 4.5, 1.5, 5.4,
                      2.4, 1.2, 3.4, 4.5, 1.5, 5.4};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  matrix1 = matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(PlusAssignOperator, PlusAssign_operator) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double values2[] = {5.7, 4.8, 3.9, 2.8, 1.7, 2.5};
  double values3[] = {6.9, 7.1, 7.3, 7.3, 7.3, 9.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1 += matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(PlusAssignOperator, PlusAssign_operator_with_minus) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};
  double values2[] = {-5.7, 4.8, 3.9, 2.8, 1.7, -2.5};
  double values3[] = {-4.5, 7.1, 7.3, -1.7, 7.3, 4.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1 += matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(PlusAssignOperator, PlusAssign_operator_with_wrong_dims) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_ANY_THROW(matrix1 += matrix2);
}

TEST(MinusAssignOperator, MinusAssign_operator) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double values2[] = {5.7, 4.8, 3.9, 2.8, 1.7, 2.5};
  double values3[] = {-4.5, -2.5, -0.5, 1.7, 3.9, 4.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1 -= matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MinusAssignOperator, MinusAssign_operator_with_minus) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, -4.5, 5.6, 6.7};
  double values2[] = {-5.7, 4.8, 3.9, 2.8, 1.7, -2.5};
  double values3[] = {6.9, -2.5, -0.5, -7.3, 3.9, 9.2};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1 -= matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MinusAssignOperator, MinusAssign_operator_with_wrong_dims) {
  S21Matrix matrix1(8, 9);
  S21Matrix matrix2(9, 10);
  EXPECT_ANY_THROW(matrix1 -= matrix2);
}

TEST(MulAssignOperator, MulAssign_operator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix control(2, 2);
  double values1[] = {-2.3, 1.5, -2, -0.75};
  double values2[] = {-5.7, 4.8, 3.9, 2.8};
  double values3[] = {18.96, -6.84, 8.475, -11.7};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix2.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  control.setGivenValues(values3, sizeof(values3) / sizeof(values3[0]));
  matrix1 *= matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulAssignOperator, MulAssign_operator_with_zero) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  S21Matrix control(2, 2);
  double values1[] = {-2.3, 1.5, -2, -0.75, 1.4, 4.15};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix1 *= matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulAssignOperator, MulAssign_operator_with_wrong_dims) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  EXPECT_ANY_THROW(matrix1 *= matrix2);
}

TEST(MulNumAssignOperator, MulNum_Assign_operator_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = 2.5;
  double values2[] = {3, 5.75, 8.5, 11.25, 14, 16.75};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  matrix1 *= num;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulNumAssignOperator, MulNum_Assign_operator_with_minus_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = -2.5;
  double values2[] = {-3, -5.75, -8.5, -11.25, -14, -16.75};

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  control.setGivenValues(values2, sizeof(values2) / sizeof(values2[0]));
  matrix1 *= num;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(MulNumAssignOperator, MulNum_Assign_operator_with_zero_test) {
  S21Matrix matrix1(2, 3);
  S21Matrix control(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double num = 0;

  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  matrix1 *= num;
  EXPECT_TRUE(matrix1.EqMatrix(control));
}

TEST(BracketsOperator, Brackets_operator_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double control = 6.7;
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));
  double check = matrix1(1, 2);

  EXPECT_EQ(control, check);
}

TEST(BracketsOperator, Brackets_operator_outofscope_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  EXPECT_ANY_THROW(matrix1(2, 3));
}

TEST(BracketsOperator, Brackets_operator_outofscope2_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  EXPECT_ANY_THROW(matrix1(4, 2));
}

TEST(BracketsOperator, Brackets_operator_outofscope3_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  EXPECT_ANY_THROW(matrix1(1, 3));
}

TEST(BracketsOperator, Brackets_operator_negative_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  EXPECT_ANY_THROW(matrix1(1, -2));
}

TEST(BracketsOperator, Brackets_operator_zero_test) {
  S21Matrix matrix1(2, 3);
  double values1[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  double control = 1.2;
  matrix1.setGivenValues(values1, sizeof(values1) / sizeof(values1[0]));

  double check = matrix1(0, 0);

  EXPECT_EQ(control, check);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}