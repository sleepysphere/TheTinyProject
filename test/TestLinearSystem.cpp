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
    Vector b(2);
    b[0] = 8;
    b[1] = 9;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0] - 3.0) < EPS
        && std::abs(x[1] - 2.0) < EPS;
}

bool test2() {
    Matrix A(1, 1); A(1, 1) = 4;
    Vector b(1); b[0] = 8;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0] - 2.0) < EPS;
}

bool test3() {
    try {
        Matrix A(2, 2);
        A(1,1) = 1;  A(1,2) = 2;
        A(2,1) = 2;  A(2,2) = 4;
        Vector b(2);
        b[0] = 5;  b[1] = 10;
        LinearSystem sys(A, b);
        sys.Solve(); // singular
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
    Vector b(3);
    b[0]=6;  b[1]=-4;  b[2]=27;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0] - 5) < EPS
        && std::abs(x[1] - 3) < EPS
        && std::abs(x[2] + 2) < EPS;
}

bool test6() {
    Matrix A(2, 2);
    A(1,1)=3; A(1,2)=2;
    A(2,1)=1; A(2,2)=2;
    Vector b(2);
    b[0]=12; b[1]=8;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0] - 2) < EPS
        && std::abs(x[1] - 3) < EPS;
}

bool test7() {
    Matrix A(3, 3);
    A(1,1)=1; A(2,2)=1; A(3,3)=1;
    Vector b(3);
    b[0]=1;  b[1]=2;  b[2]=3;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0] - 1) < EPS
        && std::abs(x[1] - 2) < EPS
        && std::abs(x[2] - 3) < EPS;
}

bool test8() {
    Matrix A(2, 2);
    A(1,1)=0; A(1,2)=1;
    A(2,1)=1; A(2,2)=0;
    Vector b(2);
    b[0]=4;  b[1]=7;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0] - 7) < EPS
        && std::abs(x[1] - 4) < EPS;
}

bool test9() {
    Matrix A(2, 2);
    A(1,1)=1e-12; A(2,2)=1;
    Vector b(2);
    b[0]=1;  b[1]=1;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[1] - 1) < EPS;
}

bool test10() {
    Matrix A(2, 2);
    A(1,1)=1; A(1,2)=2;
    A(2,1)=3; A(2,2)=4;
    Vector b(2);
    b[0]=5;  b[1]=11;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0] - 1) < EPS
        && std::abs(x[1] - 2) < EPS;
}

bool test11() {
    // under-determined 2×3, minimal-norm via pseudo-inverse
    Matrix A(2,3);
    A(1,1)=1; A(1,2)=1; A(1,3)=1;
    A(2,1)=2; A(2,2)=3; A(2,3)=4;
    Vector b(2); b[0]=1; b[1]=4;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    Vector Ax = A * x;
    return x.size()==3
        && std::abs(Ax[0]-1) < EPS
        && std::abs(Ax[1]-4) < EPS;
}

bool test12() {
    // over-determined 3×2, least-squares via pseudo-inverse
    Matrix A(3,2);
    A(1,1)=1; A(1,2)=0;
    A(2,1)=0; A(2,2)=1;
    A(3,1)=1; A(3,2)=1;
    Vector b(3); b[0]=1; b[1]=2; b[2]=3;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    // expected x = [1,2]
    return x.size()==2
        && std::abs(x[0]-1) < EPS
        && std::abs(x[1]-2) < EPS;
}

bool test13() {
    // singular square but λ>0 → Tikhonov
    Matrix A(2,2);
    A(1,1)=1; A(1,2)=0;
    A(2,1)=0; A(2,2)=0;
    Vector b(2); b[0]=1; b[1]=0;
    LinearSystem sys(A, b, 0.1);
    Vector x = sys.Solve();
    // x ≈ [1/1.1, 0]
    return std::abs(x[0] - (1.0/1.1)) < 1e-6
        && std::abs(x[1]) < EPS;
}

bool test14() {
    // under-determined + λ>0
    Matrix A(2,3);
    A(1,1)=1; A(1,2)=0; A(1,3)=0;
    A(2,1)=0; A(2,2)=1; A(2,3)=0;
    Vector b(2); b[0]=3; b[1]=4;
    LinearSystem sys(A, b, 5.0);
    Vector x = sys.Solve();
    // normal eq: (I2*5 + I2)x2 = [3;4] → x0=3/6, x1=4/6, x2=0
    return std::abs(x[0]-(3.0/6.0))<1e-6
        && std::abs(x[1]-(4.0/6.0))<1e-6
        && std::abs(x[2])<EPS;
}

bool test15() {
    // over-determined + λ>0
    Matrix A(3,2);
    A(1,1)=1; A(1,2)=0;
    A(2,1)=0; A(2,2)=1;
    A(3,1)=0; A(3,2)=0;
    Vector b(3); b[0]=2; b[1]=4; b[2]=0;
    LinearSystem sys(A, b, 1.0);
    Vector x = sys.Solve();
    // (ATA + I)x = Aᵀb → (I2+I2)x = [2;4] ⇒ 2x=[2;4] ⇒ x=[1;2]
    return std::abs(x[0]-1) < 1e-6
        && std::abs(x[1]-2) < 1e-6;
}

bool test16() {
    // dimension mismatch (rectangular), λ=0
    Matrix A(2,3); Vector b(3);
    try {
        LinearSystem sys(A, b);
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test17() {
    // dimension mismatch, λ>0
    Matrix A(2,3); Vector b(1);
    try {
        LinearSystem sys(A, b, 2.0);
        return false;
    } catch (...) {
        return true;
    }
}

bool test18() {
    // zero RHS ⇒ zero solution
    Matrix A(3,3);
    A(1,1)=2; A(1,2)=0; A(1,3)=0;
    A(2,1)=0; A(2,2)=2; A(2,3)=0;
    A(3,1)=0; A(3,2)=0; A(3,3)=2;
    Vector b(3); b[0]=0; b[1]=0; b[2]=0;
    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    return std::abs(x[0])<EPS
        && std::abs(x[1])<EPS
        && std::abs(x[2])<EPS;
}

bool test19() {
    // identity + λ>0 ⇒ x = b/(1+λ)
    Matrix A(2,2);
    A(1,1)=1; A(1,2)=0;
    A(2,1)=0; A(2,2)=1;
    Vector b(2); b[0]=5; b[1]=-3;
    LinearSystem sys(A, b, 4.0);
    Vector x = sys.Solve();
    return std::abs(x[0] - (5.0/5.0))<EPS
        && std::abs(x[1] - (-3.0/5.0))<EPS;
}

bool test20() {
    // very large λ ⇒ solution → 0
    Matrix A(2,2);
    A(1,1)=1; A(1,2)=0;
    A(2,1)=0; A(2,2)=1;
    Vector b(2); b[0]=7; b[1]=8;
    LinearSystem sys(A, b, 1e6);
    Vector x = sys.Solve();
    return std::abs(x[0]) < 1e-5
        && std::abs(x[1]) < 1e-5;
}

int main() {
    for (int i = 1; i <= 20; ++i) {
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
            case 11: result = test11(); break;
            case 12: result = test12(); break;
            case 13: result = test13(); break;
            case 14: result = test14(); break;
            case 15: result = test15(); break;
            case 16: result = test16(); break;
            case 17: result = test17(); break;
            case 18: result = test18(); break;
            case 19: result = test19(); break;
            case 20: result = test20(); break;
        }
        std::cout << "test" << i << ": " << (result ? "PASSED" : "FAILED") << "\n";
    }
    return 0;
}
