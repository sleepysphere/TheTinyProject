#ifndef REGRESSION_H
#define REGRESSION_H

#include "Matrix.h"
#include "Vector.h"

class Regression {
public:
    // Compute regression coefficients using normal equation
    static Vector Fit(const Matrix& A, const Vector& b);

    // Predict b from A and learned coefficients x
    static Vector Predict(const Matrix& A, const Vector& x);

    // Compute root mean square error between predictions and actual b
    static double RMSE(const Vector& predictions, const Vector& actual);
};

#endif // REGRESSION_H
