#include "../include/LinearSystem.h"
#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <iostream>
#include <cmath>
#include <cassert>

const double EPS = 1e-9;

bool test1() {
    Matrix A(2, 2);
    A(1, 1) = 2; A(1, 2) = 1;
    A(2, 1) = 1; A(2, 2) = 3;
    Vector b(2); b(0) = 8; b(1) = 13;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(0) - 3.0) < EPS && std::abs(x(1) - 2.0) < EPS;
}

bool test2() {
    Matrix A(1, 1); A(1, 1) = 4;
    Vector b(1); b(0) = 8;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(0) - 2.0) < EPS;
}

bool test3() {
    try {
        Matrix A(2, 2); A(1,1)=1; A(1,2)=2; A(2,1)=2; A(2,2)=4;
        Vector b(2); b(0)=5; b(1)=10;
        LinearSystem sys(A, b);
        sys.Solve(); // Singular matrix
        return false;
    } catch (...) {
        return true;
    }
}

bool test4() {
    try {
        Matrix A(2, 2); Vector b(3);
        LinearSystem sys(A, b);
        return false;
    } catch (...) {
        return true;
    }
}

bool test5() {
    Matrix A(3, 3);
    A(1,1)=1; A(1,2)=1; A(1,3)=1;
    A(2,1)=0; A(2,2)=2; A(2,3)=5;
    A(3,1)=2; A(3,2)=5; A(3,3)=-1;
    Vector b(3); b(0)=6; b(1)=-4; b(2)=27;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(0) - 5) < EPS && std::abs(x(1) - 3) < EPS && std::abs(x(2) - -2) < EPS;
}

bool test6() {
    Matrix A(2, 2); A(1,1)=3; A(1,2)=2; A(2,1)=1; A(2,2)=2;
    Vector b(2); b(0)=12; b(1)=8;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(0) - 2) < EPS && std::abs(x(1) - 3) < EPS;
}

bool test7() {
    Matrix A(3, 3); A(1,1)=1; A(2,2)=1; A(3,3)=1;
    Vector b(3); b(0)=1; b(1)=2; b(2)=3;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(0) - 1) < EPS && std::abs(x(1) - 2) < EPS && std::abs(x(2) - 3) < EPS;
}

bool test8() {
    Matrix A(2, 2); A(1,1)=0; A(1,2)=1; A(2,1)=1; A(2,2)=0;
    Vector b(2); b(0)=4; b(1)=7;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(0) - 7) < EPS && std::abs(x(1) - 4) < EPS;
}

bool test9() {
    Matrix A(2, 2); A(1,1)=1e-12; A(2,2)=1;
    Vector b(2); b(0)=1; b(1)=1;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(1) - 1) < EPS;
}

bool test10() {
    Matrix A(2, 2); A(1,1)=1; A(1,2)=2; A(2,1)=3; A(2,2)=4;
    Vector b(2); b(0)=5; b(1)=11;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x(0) - 1) < EPS && std::abs(x(1) - 2) < EPS;
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
