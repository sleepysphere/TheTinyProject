#include "../include/LinearSystem.h"
#include <stdexcept>
#include <cmath>

LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
    : mSize(A.numRows()) {
    if (A.numRows() != A.numCols())
        throw std::invalid_argument("Matrix A must be square");
    if (A.numRows() != b.size())
        throw std::invalid_argument("Matrix and vector size mismatch");
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

void LinearSystem::swapRows(Matrix& mat, Vector& vec, int i, int j) const {
    for (int col = 1; col <= mSize; ++col)
        std::swap(mat(i, col), mat(j, col));
    std::swap((*mpb)(i - 1), (*mpb)(j - 1));
}

Vector LinearSystem::Solve() const {
    Matrix A = *mpA; // Make copies so we don't mutate originals
    Vector b = *mpb;

    // Gaussian elimination with partial pivoting
    for (int k = 1; k <= mSize; ++k) {
        // Pivot
        int pivotRow = k;
        double maxVal = std::fabs(A(k, k));
        for (int i = k + 1; i <= mSize; ++i) {
            if (std::fabs(A(i, k)) > maxVal) {
                pivotRow = i;
                maxVal = std::fabs(A(i, k));
            }
        }
        if (maxVal < 1e-12)
            throw std::runtime_error("Singular matrix detected");

        if (pivotRow != k) {
            swapRows(A, b, k, pivotRow);
        }

        // Eliminate
        for (int i = k + 1; i <= mSize; ++i) {
            double factor = A(i, k) / A(k, k);
            for (int j = k; j <= mSize; ++j) {
                A(i, j) -= factor * A(k, j);
            }
            b(i - 1) -= factor * b(k - 1);
        }
    }

    // Back substitution
    Vector x(mSize);
    for (int i = mSize; i >= 1; --i) {
        double sum = 0;
        for (int j = i + 1; j <= mSize; ++j)
            sum += A(i, j) * x(j - 1);
        x(i - 1) = (b(i - 1) - sum) / A(i, i);
    }

    return x;
}
