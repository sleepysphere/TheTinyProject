#include "../include/Vector.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <cassert>

const double EPS = 1e-9;

bool test1() {
    Vector v(5);
    return v.size() == 5;
}

bool test2() {
    Vector v;
    return v.size() == 0;
}

bool test3() {
    Vector v(3);
    v[0] = 1.0;
    v[1] = 2.0;
    v[2] = 3.0;
    return std::abs(v[1] - 2.0) < EPS;
}

bool test4() {
    Vector v(3);
    v(1) = 4.0;
    return std::abs(v(1) - 4.0) < EPS;
}

bool test5() {
    Vector v1(3), v2(3);
    v1[0] = 1.0; v2[0] = 2.0;
    Vector v3 = v1 + v2;
    return std::abs(v3[0] - 3.0) < EPS;
}

bool test6() {
    Vector v1(3), v2(3);
    v1[1] = 5.0; v2[1] = 3.0;
    Vector v3 = v1 - v2;
    return std::abs(v3[1] - 2.0) < EPS;
}

bool test7() {
    Vector v(3);
    v[0] = 2.0;
    Vector s = v * 3.0;
    return std::abs(s[0] - 6.0) < EPS;
}

bool test8() {
    Vector v(3);
    v[1] = 2.0;
    Vector s = 4.0 * v;
    return std::abs(s[1] - 8.0) < EPS;
}

bool test9() {
    Vector v1(3);
    for (int i = 0; i < 3; ++i) v1[i] = i + 1;
    Vector v2(v1);
    for (int i = 0; i < 3; ++i)
        if (std::abs(v1[i] - v2[i]) > EPS) return false;
    return true;
}

bool test10() {
    Vector v1(3), v2(3);
    v1[0] = 1.0;
    v2 = v1;
    return std::abs(v2[0] - 1.0) < EPS;
}

bool test11() {
    Vector v1(3);
    v1 = v1;
    return v1.size() == 3;
}

bool test12() {
    Vector v(3);
    for (int i = 0; i < 3; ++i) v[i] = -i;
    Vector neg = -v;
    for (int i = 0; i < 3; ++i)
        if (std::abs(neg[i] + i) > EPS) return false;
    return true;
}

bool test13() {
    Vector v(3);
    for (int i = 0; i < 3; ++i) v[i] = i;
    Vector id = +v;
    for (int i = 0; i < 3; ++i)
        if (std::abs(id[i] - i) > EPS) return false;
    return true;
}

bool test14() {
    Vector v(3);
    v[0] = -3.0; v[1] = 4.0; v[2] = 0.0;
    return std::abs(v.Norm(2) - 5.0) < EPS;
}

bool test15() {
    Vector v(3);
    v[0] = 1.0; v[1] = -2.0; v[2] = 3.0;
    return std::abs(v.Norm(1) - 6.0) < EPS;
}

bool test16() {
    Vector v(3);
    v[0] = 2.0; v[1] = 0.0; v[2] = -2.0;
    double n = v.Norm(4);
    return std::abs(n - std::pow(2.0 * 2.0 * 2.0 * 2.0 + 2.0 * 2.0 * 2.0 * 2.0, 1.0/4)) < EPS;
}

bool test17() {
    Vector v(3);
    std::ostringstream oss;
    oss << v;
    std::string out = oss.str();
    return out.find("[") == 0 && out.find("]") == out.size() - 1;
}

bool test18() {
    Vector v(3);
    try {
        double x = v[5];
        return false;
    } catch (std::exception& e) {
        //std::cout << "Caught expected exception: " << e.what() << "\n";
        return true;
    }
}

bool test19() {
    Vector v(3);
    try {
        double x = v(0); // 1-based access
        return false;
    } catch (std::exception& e) {
        //std::cout << "Caught expected exception: " << e.what() << "\n";
        return true;
    }
}

bool test20() {
    Vector v1(3), v2(4);
    try {
        Vector v3 = v1 + v2;
        return false;
    } catch (const std::invalid_argument&) {
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
        std::cout << "Test " << i << ": " << (result ? "PASSED" : "FAILED") << "\n";
    }
}
