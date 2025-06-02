#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <bits/stdc++.h>

const double EPS = 1e-9;

bool test1() {
    Matrix m(3, 4);
    return m.numRows() == 3 && m.numCols() == 4;
}

bool test2() {
    try {
        Matrix m(0, 2);
        return false;
    } catch (...) {
        return true;
    }
}

bool test3() {
    Matrix m(2, 2);
    m(1, 1) = 5.0;
    return std::abs(m(1, 1) - 5.0) < EPS;
}

bool test4() {
    try {
        Matrix m(3, 3);
        double x = m(4, 1);
        return false;
    } catch (...) {
        return true;
    }
}

bool test5() {
    Matrix m1(2, 2), m2(2, 2);
    m1(1, 1) = 1; m2(1, 1) = 2;
    Matrix m3 = m1 + m2;
    return std::abs(m3(1, 1) - 3) < EPS;
}

bool test6() {
    Matrix m1(2, 2), m2(2, 2);
    m1(1, 2) = 5; m2(1, 2) = 3;
    Matrix m3 = m1 - m2;
    return std::abs(m3(1, 2) - 2) < EPS;
}

bool test7() {
    Matrix m1(2, 3), m2(3, 2);
    for (int i = 1; i <= 2; ++i)
        for (int j = 1; j <= 3; ++j)
            m1(i, j) = 1;
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 2; ++j)
            m2(i, j) = 2;
    Matrix m3 = m1 * m2;
    return m3.numRows() == 2 && m3.numCols() == 2 && std::abs(m3(1,1) - 6) < EPS;
}

bool test8() {
    Matrix m(2, 3);
    for (int i = 1; i <= 2; ++i)
        for (int j = 1; j <= 3; ++j)
            m(i, j) = i * j;
    Matrix t = m.transpose();
    return t.numRows() == 3 && t.numCols() == 2 && std::abs(t(3, 2) - 6) < EPS;
}

bool test9() {
    Matrix m(2, 2);
    m(1, 1) = 1; m(1, 2) = 2;
    m(2, 1) = 3; m(2, 2) = 4;
    Vector v(2); v(0) = 1; v(1) = 2;
    Vector res = m * v;
    return std::abs(res(0) - 5) < EPS && std::abs(res(1) - 11) < EPS;
}

bool test10() {
    Matrix m(2, 2);
    m(1, 1) = 1; m(1, 2) = 0;
    m(2, 1) = 0; m(2, 2) = 1;
    Matrix inv = m.inverse();
    return std::abs(inv(1, 1) - 1.0) < EPS && std::abs(inv(2, 2) - 1.0) < EPS;
}

bool test11() {
    Matrix m(2, 2);
    m(1, 1) = 1; m(1, 2) = 2;
    m(2, 1) = 3; m(2, 2) = 4;
    double det = m.determinant();
    return std::abs(det - (-2.0)) < EPS;
}

bool test12() {
    Matrix m(1, 1);
    m(1, 1) = 7;
    return std::abs(m.determinant() - 7.0) < EPS;
}

bool test13() {
    Matrix m(3, 3);
    try {
        double det = m.determinant();
        return false;
    } catch (...) {
        return true;
    }
}

bool test14() {
    Matrix m(2, 2);
    for (int i = 1; i <= 2; ++i)
        for (int j = 1; j <= 2; ++j)
            m(i, j) = 1;
    Matrix s = m * 2.0;
    return std::abs(s(1,1) - 2.0) < EPS;
}

bool test15() {
    Matrix m1(2, 2);
    m1(1, 1) = 5;
    Matrix m2 = m1;
    return std::abs(m2(1, 1) - 5) < EPS;
}

bool test16() {
    Matrix m1(2, 2), m2(2, 2);
    m1(1, 1) = 1;
    m2 = m1;
    return std::abs(m2(1, 1) - 1.0) < EPS;
}

bool test17() {
    Matrix m(2, 2);
    m(1, 2) = 1;
    std::ostringstream oss;
    oss << m;
    std::string s = oss.str();
    return s.find("[") != std::string::npos;
}

bool test18() {
    Matrix m(2, 2);
    m(1,1) = 2; m(1,2) = 0;
    m(2,1) = 0; m(2,2) = 2;
    Matrix inv = m.inverse();
    return std::abs(inv(1,1) - 0.5) < EPS && std::abs(inv(2,2) - 0.5) < EPS;
}

bool test19() {
    try {
        Matrix m(2, 3);
        m.inverse();
        return false;
    } catch (...) {
        return true;
    }
}

bool test20() {
    Matrix m(2, 2);
    m(1,1) = 1; m(1,2) = 2;
    m(2,1) = 2; m(2,2) = 4; // singular
    try {
        m.inverse();
        return false;
    } catch (...) {
        return true;
    }
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
}
