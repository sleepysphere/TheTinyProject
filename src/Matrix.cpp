#include "../include/Matrix.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>          // for std::fabs
using namespace std;     // bring std::fabs, std::swap, etc. into scope

// Default constructor (disabled)
Matrix::Matrix() {
    assert(false && "Default constructor is disabled");
}

// Zero‐initialized matrix
Matrix::Matrix(int numRows, int numCols)
  : mNumRows(numRows),
    mNumCols(numCols),
    mData(new double*[numRows])
{
   if (numRows <= 0 || numCols <= 0)
       throw std::invalid_argument("Matrix dimensions must be positive");

    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        std::fill(mData[i], mData[i] + mNumCols, 0.0);
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
  : mNumRows(other.mNumRows),
    mNumCols(other.mNumCols),
    mData(new double*[other.mNumRows])
{
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        std::copy(other.mData[i], other.mData[i] + mNumCols, mData[i]);
    }
}

// Destructor
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}

// Assignment
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // free old
        for (int i = 0; i < mNumRows; ++i)
            delete[] mData[i];
        delete[] mData;
        // copy dims
        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        // allocate new
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            std::copy(other.mData[i], other.mData[i] + mNumCols, mData[i]);
        }
    }
    return *this;
}

// Accessors
int Matrix::numRows() const { return mNumRows; }
int Matrix::numCols() const { return mNumCols; }

// 1-based element access
double& Matrix::operator()(int i, int j) {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols)
        throw std::out_of_range("Matrix index out of range");
    return mData[i-1][j-1];
}
double Matrix::operator()(int i, int j) const {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols)
        throw std::out_of_range("Matrix index out of range");
    return mData[i-1][j-1];
}

// Matrix +, -
Matrix Matrix::operator+(const Matrix& other) const {
    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols)
        throw std::invalid_argument("Matrix dimensions must match for addition");
    Matrix R(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
      for (int j = 1; j <= mNumCols; ++j)
        R(i,j) = (*this)(i,j) + other(i,j);
    return R;
}
Matrix Matrix::operator-(const Matrix& other) const {
    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols)
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    Matrix R(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
      for (int j = 1; j <= mNumCols; ++j)
        R(i,j) = (*this)(i,j) - other(i,j);
    return R;
}

// Matrix * Matrix
Matrix Matrix::operator*(const Matrix& other) const {
    if (mNumCols != other.mNumRows)
        throw std::invalid_argument("Inner matrix dimensions must agree for multiplication");
    Matrix R(mNumRows, other.mNumCols);
    for (int i = 1; i <= mNumRows; ++i) {
      for (int j = 1; j <= other.mNumCols; ++j) {
        double sum = 0.0;
        for (int k = 1; k <= mNumCols; ++k)
          sum += (*this)(i,k) * other(k,j);
        R(i,j) = sum;
      }
    }
    return R;
}

// Matrix * Vector
Vector Matrix::operator*(const Vector& vec) const {
    if (mNumCols != static_cast<int>(vec.size()))
        throw std::invalid_argument("Matrix-vector size mismatch");
    Vector out(mNumRows);

    for (int i = 1; i <= mNumRows; ++i) {
         double sum = 0.0;
         for (int j = 1; j <= mNumCols; ++j)
             sum += (*this)(i,j) * vec[j-1];
         out[i-1] = sum;
     }
     return out;
}

// Matrix * scalar
Matrix Matrix::operator*(double scalar) const {
    Matrix R(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
      for (int j = 1; j <= mNumCols; ++j)
        R(i,j) = (*this)(i,j) * scalar;
    return R;
}

// Determinant via LU‐style elimination
double Matrix::determinant() const {
    if (mNumRows != mNumCols)
        throw std::invalid_argument("Matrix must be square");
    int n = mNumRows;
    // copy into a 2D array
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        A[i][j] = mData[i][j];

    double det = 1.0;
    for (int k = 0; k < n; ++k) {
        // pivot search
        int piv = k;
        for (int i = k+1; i < n; ++i)
          if (std::fabs(A[i][k]) > std::fabs(A[piv][k]))
            piv = i;
        // if pivot is effectively zero, throw
        if (std::fabs(A[piv][k]) < 1e-15)
            throw std::runtime_error("Matrix is singular");
        if (piv != k) {
            std::swap(A[k], A[piv]);
            det = -det;
        }
        det *= A[k][k];
        // eliminate below
        for (int i = k+1; i < n; ++i) {
            double f = A[i][k] / A[k][k];
            for (int j = k; j < n; ++j)
                A[i][j] -= f * A[k][j];
        }
    }
    return det;
}

// Transpose
Matrix Matrix::transpose() const {
    Matrix T(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; ++i)
      for (int j = 1; j <= mNumCols; ++j)
        T(j,i) = (*this)(i,j);
    return T;
}

// Inverse via Gauss‐Jordan
Matrix Matrix::inverse() const {
    if (mNumRows != mNumCols)
        throw std::invalid_argument("Matrix must be square");
    int n = mNumRows;
    // build augmented [A | I]
    std::vector<std::vector<double>> aug(n, std::vector<double>(2*n, 0.0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        aug[i][j] = mData[i][j];
      aug[i][n+i] = 1.0;
    }
    // elimination
    for (int k = 0; k < n; ++k) {
        // pivot search
        int piv = k;
        for (int i = k+1; i < n; ++i)
            if (std::fabs(aug[i][k]) > std::fabs(aug[piv][k]))
                piv = i;
        // throw on zero pivot
        if (std::fabs(aug[piv][k]) < 1e-15)
            throw std::runtime_error("Matrix is singular");
        std::swap(aug[k], aug[piv]);
        // normalize row k
        double diag = aug[k][k];
        for (int j = 0; j < 2*n; ++j)
          aug[k][j] /= diag;
        // eliminate others
        for (int i = 0; i < n; ++i) if (i != k) {
          double f = aug[i][k];
          for (int j = 0; j < 2*n; ++j)
            aug[i][j] -= f * aug[k][j];
        }
    }
    // extract inverse
    Matrix inv(n,n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        inv(i+1,j+1) = aug[i][n+j];
    return inv;
}

// Moore‐Penrose pseudo‐inverse via normal equations
Matrix Matrix::pseudoInverse() const {
    // if tall or square: (A^T A)^{-1} A^T
    if (mNumRows >= mNumCols) {
      Matrix At = transpose();
      return ( (At * (*this)).inverse() ) * At;
    }
    // if wide: A^T (A A^T)^{-1}
    else {
      Matrix At = transpose();
      return At * ( (*this * At).inverse() );
    }
}

// Stream insertion
std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 1; i <= mat.mNumRows; ++i) {
        os << "[ ";
        for (int j = 1; j <= mat.mNumCols; ++j) {
            os << mat(i,j);
            if (j < mat.mNumCols) os << ", ";
        }
        os << " ]\n";
    }
    return os;
}
