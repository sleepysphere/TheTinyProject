#include "../include/Regression.h"
#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <iostream>
#include <cmath>

const double EPS = 1e-6;

bool test1() {
    Matrix A(3, 1);
    A(1,1)=1; A(2,1)=2; A(3,1)=3;
    Vector b(3); b(0)=2; b(1)=4; b(2)=6;
    Vector x = Regression::Fit(A, b);
    return std::abs(x(0) - 2) < EPS;
}

bool test2() {
    Matrix A(2, 2);
    A(1,1)=1; A(1,2)=2;
    A(2,1)=2; A(2,2)=3;
    Vector b(2); b(0)=8; b(1)=11;
    Vector x = Regression::Fit(A, b);
    return std::abs(x(0)-2) < EPS && std::abs(x(1)-3) < EPS;
}

// ... and so on up to test10 (predictions, RMSE, edge cases, etc.)

int main() {
    for (int i = 1; i <= 10; ++i) {
        bool result = false;
        switch (i) {
            case 1: result = test1(); break;
            case 2: result = test2(); break;
            // ...
        }
        std::cout << "test" << i << ": " << (result ? "PASSED" : "FAILED") << "\n";
    }
}
