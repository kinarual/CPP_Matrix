#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes (implement the access to private fields `rows_` and `cols_`
  // via accessor and mutator. If the matrix increases in size, it is filled
  // with zeros. If it decreases in size, the excess is simply discarded)
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();   // Default constructor
  ~S21Matrix();  // Destructor
  S21Matrix(
      int rows,
      int cols);  // Parametrized constructor with number of rows and columns
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor

  // accessors
  int getRows() const { return rows_; }
  int getCols() const { return cols_; }
  double** getMatrix() const { return matrix_; }

  // mutators
  void setRows(int rows) { rows_ = rows; }
  void setCols(int cols) { cols_ = cols; }

  // matrix operations
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // operators overload
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int row, int col) &;

  // helpers
  void memAlloc(int rows, int cols);
  void memFree();
  void setValue();
  void resizeMatrix(int oldRows, int oldCols, int newRows, int newCols);
  void setGivenValues(double* values, int numValues);
  S21Matrix cut_matrix(int ban_row, int ban_col);
};

#endif
