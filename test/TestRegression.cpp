#include "../include/Regression.h"
#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <iostream>
#include <cmath>

const double EPS = 1e-6;

bool test1() {
    // Perfect linear relationship: y = 2x
    Matrix A(3, 1);
    A(1,1)=1; A(2,1)=2; A(3,1)=3;
    Vector b(3); b(0)=2; b(1)=4; b(2)=6;
    Vector x = Regression::Fit(A, b);
    return std::abs(x(0) - 2.0) < EPS;
}

bool test2() {
    // Linear regression with two features: y = 2x + 3z
    Matrix A(2, 2);
    A(1,1)=1; A(1,2)=1;
    A(2,1)=2; A(2,2)=2;
    Vector b(2); b(0)=5; b(1)=10;
    Vector x = Regression::Fit(A, b);
    return std::abs(x(0)-2) < EPS && std::abs(x(1)-3) < EPS;
}

bool test3() {
    // Predict test
    Matrix A(3, 1);
    A(1,1)=1; A(2,1)=2; A(3,1)=3;
    Vector b(3); b(0)=3; b(1)=6; b(2)=9;
    Vector x = Regression::Fit(A, b);
    Vector pred = Regression::Predict(A, x);
    for (int i = 0; i < 3; ++i)
        if (std::abs(pred(i) - b(i)) > EPS) return false;
    return true;
}

bool test4() {
    // RMSE should be zero on perfect fit
    Matrix A(2, 1);
    A(1,1)=1; A(2,1)=2;
    Vector b(2); b(0)=2; b(1)=4;
    Vector x = Regression::Fit(A, b);
    Vector pred = Regression::Predict(A, x);
    double rmse = Regression::RMSE(pred, b);
    return rmse < EPS;
}

bool test5() {
    // Non-perfect fit: check RMSE > 0
    Matrix A(2, 1);
    A(1,1)=1; A(2,1)=2;
    Vector b(2); b(0)=2.5; b(1)=3.0;
    Vector x = Regression::Fit(A, b);
    Vector pred = Regression::Predict(A, x);
    double rmse = Regression::RMSE(pred, b);
    return rmse > 0 && rmse < 1.0;
}

bool test6() {
    // All zeros
    Matrix A(3, 1); Vector b(3);
    Vector x = Regression::Fit(A, b);
    return std::abs(x(0)) < EPS;
}

bool test7() {
    // Under-determined (more columns than rows)
    Matrix A(2, 3);
    A(1,1)=1; A(1,2)=2; A(1,3)=3;
    A(2,1)=4; A(2,2)=5; A(2,3)=6;
    Vector b(2); b(0)=14; b(1)=32;
    Vector x = Regression::Fit(A, b);
    Vector pred = Regression::Predict(A, x);
    double rmse = Regression::RMSE(pred, b);
    return rmse < EPS;
}

bool test8() {
    // Overdetermined system (more rows than columns)
    Matrix A(4, 2);
    A(1,1)=1; A(1,2)=0;
    A(2,1)=2; A(2,2)=0;
    A(3,1)=3; A(3,2)=0;
    A(4,1)=4; A(4,2)=0;
    Vector b(4);
    for (int i = 0; i < 4; ++i) b(i) = (i+1) * 2;
    Vector x = Regression::Fit(A, b);
    return std::abs(x(0) - 2.0) < EPS && std::abs(x(1)) < EPS;
}

bool test9() {
    // Predict with zero vector
    Matrix A(2, 2);
    A(1,1)=1; A(1,2)=2;
    A(2,1)=3; A(2,2)=4;
    Vector x(2); x(0)=0; x(1)=0;
    Vector pred = Regression::Predict(A, x);
    return std::abs(pred(0)) < EPS && std::abs(pred(1)) < EPS;
}

bool test10() {
    // RMSE with different vectors
    Vector a(3); a(0)=1; a(1)=2; a(2)=3;
    Vector b(3); b(0)=2; b(1)=2; b(2)=4;
    double rmse = Regression::RMSE(a, b);
    return std::abs(rmse - std::sqrt((1+0+1)/3.0)) < EPS;
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        bool result = false;
        switch (i) {
            case 1: result = test1(); break;
            case 2: result = test2(); break;
            case 3: result = test3(); break;
            case 4: result = test4(); break;
            case 5: result = test5(); break;
            case 6: result = test6(); break;
            case 7: result = test7(); break;
            case 8: result = test8(); break;
            case 9: result = test9(); break;
            case 10: result = test10(); break;
        }
        std::cout << "test" << i << ": " << (result ? "PASSED" : "FAILED") << "\n";
    }
}
