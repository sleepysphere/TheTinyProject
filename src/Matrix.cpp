#include "../include/Matrix.h"
#include <stdexcept>
#include <cmath>

Matrix::Matrix() : mNumRows(0), mNumCols(0), mData(nullptr) {}

Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
    if (numRows <= 0 || numCols <= 0)
        throw std::invalid_argument("Matrix dimensions must be positive");
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols]{};
    }
}

Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i)
        delete[] mData[i];
    delete[] mData;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    // Free old memory
    for (int i = 0; i < mNumRows; ++i)
        delete[] mData[i];
    delete[] mData;

    // Copy new data
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    }

    return *this;
}

int Matrix::numRows() const { return mNumRows; }
int Matrix::numCols() const { return mNumCols; }

double& Matrix::operator()(int i, int j) {
    assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

double Matrix::operator()(int i, int j) const {
    assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] - other.mData[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < other.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result.mData[i][j] += mData[i][k] * other.mData[k][j];
    return result;
}

Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.size());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; ++i) {
        result(i) = 0;
        for (int j = 0; j < mNumCols; ++j)
            result(i) += mData[i][j] * vec(j);
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] * scalar;
    return result;
}

// --- Determinant, Inverse, Pseudo-Inverse placeholders ---

double Matrix::determinant() const {
    assert(mNumRows == mNumCols);
    // Basic determinant using Laplace expansion (for small matrices only)
    if (mNumRows == 1) return mData[0][0];
    if (mNumRows == 2) return mData[0][0]*mData[1][1] - mData[0][1]*mData[1][0];

    throw std::runtime_error("Determinant not implemented for large matrices");
}

Matrix Matrix::transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            result(j, i) = (*this)(i, j);
    return result;
}

Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols); // Must be square
    int n = mNumRows;
    Matrix aug(n, 2 * n);

    // Initialize augmented matrix [A | I]
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            aug(i, j) = (*this)(i, j);
        aug(i, n + i) = 1.0;
    }

    // Forward elimination
    for (int i = 1; i <= n; ++i) {
        // Pivot
        double pivot = aug(i, i);
        if (fabs(pivot) < 1e-12)
            throw std::runtime_error("Matrix is singular or near-singular");
        for (int j = 1; j <= 2 * n; ++j)
            aug(i, j) /= pivot;

        // Eliminate column i in other rows
        for (int k = 1; k <= n; ++k) {
            if (k == i) continue;
            double factor = aug(k, i);
            for (int j = 1; j <= 2 * n; ++j)
                aug(k, j) -= factor * aug(i, j);
        }
    }

    // Extract inverse from augmented matrix
    Matrix inv(n, n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            inv(i, j) = aug(i, n + j);

    return inv;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.mNumRows; ++i) {
        os << "[ ";
        for (int j = 0; j < mat.mNumCols; ++j) {
            os << mat.mData[i][j] << " ";
        }
        os << "]\n";
    }
    return os;
}
