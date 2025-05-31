#include "../include/Regression.h"
#include <cmath>
#include <cassert>

Vector Regression::Fit(const Matrix& A, const Vector& b) {
    Matrix At = A.transpose();
    Matrix AtA = At * A;
    Matrix AtA_inv = AtA.inverse();
    Vector Atb = At * b;
    return AtA_inv * Atb;
}

Vector Regression::Predict(const Matrix& A, const Vector& x) {
    return A * x;
}

double Regression::RMSE(const Vector& predictions, const Vector& actual) {
    assert(predictions.size() == actual.size());
    double sum_sq = 0.0;
    for (int i = 0; i < predictions.size(); ++i) {
        double diff = predictions(i) - actual(i);
        sum_sq += diff * diff;
    }
    return std::sqrt(sum_sq / predictions.size());
}
