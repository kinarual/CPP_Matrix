#include "s21_matrix_oop.h"

// Default Constructor
S21Matrix::S21Matrix() : rows_(5), cols_(5) { memAlloc(rows_, cols_); }

// Destructor
S21Matrix::~S21Matrix() {
  if (matrix_) {
    memFree();
  }
}

// Parametrized constructor
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Wrong parameters for matrix");
  } else {
    memAlloc(rows_, cols_);
  }
}

// Copy contructor
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.getRows()), cols_(other.getCols()) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.getRows()), cols_(other.getCols()) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    resizeMatrix(rows_, cols_, other.rows_, other.cols_);
  } else {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  other.matrix_ = nullptr;
}

// are matrices equal
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
      }
    }
  }
  return true;
}

// sum of two matrices
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

// difference between two matrices
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix dimensions");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

// multiply by a number
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

// multiply two matrices
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Wrong dimensions for matrix multiplication");
  } else {
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        double sum = 0.0;
        for (int k = 0; k < cols_; k++) {
          sum += matrix_[i][k] * other.matrix_[k][j];
        }
        result.matrix_[i][j] = sum;
      }
    }
    if (matrix_) memFree();
    rows_ = result.rows_;
    cols_ = result.cols_;
    memAlloc(rows_, cols_);
    *this = result;
  }
}

// trunspose matrix
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

// count matrix determinant
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    double result = 0;
    for (int i = 0; i < cols_; ++i) {
      double subres = 0;
      S21Matrix minor = cut_matrix(0, i);
      subres = minor.Determinant();
      result += matrix_[0][i] * subres * pow(-1, i);
    }
    return result;
  }
}

// count the algebraic addition matrix of the current one
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  S21Matrix result(rows_, cols_);
  for (int x_row = 0; x_row < rows_; x_row++) {
    for (int x_col = 0; x_col < cols_; x_col++) {
      S21Matrix minor_A = cut_matrix(x_row, x_col);
      result.matrix_[x_row][x_col] =
          minor_A.Determinant() * pow(-1, x_row + x_col);
    }
  }

  *this = result;
  return result;
}

// calculates inverse matrix
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix is not square");
  }

  if (rows_ == 1) {
    if (matrix_[0][0] != 0) {
      S21Matrix result(1, 1);
      result.matrix_[0][0] = 1 / matrix_[0][0];
      return result;
    } else {
      throw std::invalid_argument(
          "Scalar matrix is 0. Division by zero can not be done.");
    }
  }

  double res_determinant = this->Determinant();
  if (res_determinant == 0) {
    throw std::invalid_argument("Matrix determinant is 0.");
  }

  S21Matrix cofactor = this->CalcComplements();
  S21Matrix inverse = cofactor.Transpose();
  inverse.MulNumber(1 / res_determinant);

  return inverse;
}

// + operator overloading
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix temp(*this);
  temp.SumMatrix(other);
  return temp;
}

// - operator overloading
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix temp(*this);
  temp.SubMatrix(other);
  return temp;
}

// * operator overloading
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix temp(*this);
  temp.MulMatrix(other);
  return temp;
}

// * num operator overloading
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix temp(*this);
  temp.MulNumber(num);
  return temp;
}

// == operator overloading
bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

// = operator overloading
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      resizeMatrix(rows_, cols_, other.rows_, other.cols_);
    }

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

// += operator overloading
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return (*this);
}

// -= operator overloading
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return (*this);
}

// *= operator overloading
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return (*this);
}

// *= number operator overloading
S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return (*this);
}

// (int i, int j) operator overloading
double& S21Matrix::operator()(int row, int col) & {
  if (row < 0 || col < 0) {
    throw std::invalid_argument("Zero or negative parameters for matrix");
  } else {
    if (row >= rows_ || col >= cols_) {
      throw std::invalid_argument("There are no such parameters for matrix");
    } else {
      return matrix_[row][col];
    }
  }
}

// Allocation of memory for the matrix
void S21Matrix::memAlloc(int rows, int cols) {
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols];
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = 0;
    }
  }
}

// Method to deallocate memory for the matrix
void S21Matrix::memFree() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

// Setting random values for matrix
void S21Matrix::setValue() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = (float)(rand()) / (float)(RAND_MAX);
    }
  }
}

// Resizing matrix
void S21Matrix::resizeMatrix(int oldRows, int oldCols, int newRows,
                             int newCols) {
  double** newMatrix = new double*[newRows];
  for (int i = 0; i < newRows; i++) {
    newMatrix[i] = new double[newCols];
  }

  for (int i = 0; i < std::min(oldRows, newRows); i++) {
    for (int j = 0; j < std::min(oldCols, newCols); j++) {
      newMatrix[i][j] = matrix_[i][j];
    }
  }

  if (newRows > oldRows || newCols > oldCols) {
    for (int i = oldRows; i < newRows; i++) {
      for (int j = 0; j < newCols; j++) {
        newMatrix[i][j] = 0.0;
      }
    }
  }

  // for (int i = 0; i < oldRows; i++) {
  //   delete[] matrix_[i];
  // }
  // delete[] matrix_;

  matrix_ = newMatrix;
  rows_ = newRows;
  cols_ = newCols;
}

void S21Matrix::setGivenValues(double* values, int numValues) {
  if (numValues != rows_ * cols_) {
    throw std::invalid_argument(
        "Number of values does not match the matrix size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = values[i * cols_ + j];
    }
  }
}

S21Matrix S21Matrix::cut_matrix(int ban_row, int ban_col) {
  S21Matrix result(rows_ - 1, cols_ - 1);

  int row_to_skip = 0;
  int col_to_skip = 0;

  for (int row = 0; row < rows_; row++) {
    if (row != ban_row) {
      col_to_skip = 0;
      for (int col = 0; col < cols_; col++) {
        if (col != ban_col) {
          result.matrix_[row - row_to_skip][col - col_to_skip] =
              matrix_[row][col];
        } else {
          col_to_skip = 1;
        }
      }
    } else {
      row_to_skip = 1;
    }
  }
  return result;
}