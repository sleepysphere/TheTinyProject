#include "../include/Vector.h"
#include <iostream>
#include <sstream>
#include <cmath>        // for std::abs
#include <stdexcept>    // for std::invalid_argument, std::out_of_range
#include <string>       // for std::string

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
    try {
        Vector v(9);
        double x = v(-1); // out of bounds
        (void)x;
        return false;
    } catch (const std::out_of_range&) {
        return true;
    }
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
    try {
        Vector v1(9), v2(10);
        auto v3 = v1 + v2;
        (void)v3;
        return false;
    } catch (std::exception& e) {
        //std::cout << "Caught expected exception: " << e.what() << "\n";
        return true;
    }
}

bool test19() {
    Vector v(3);
    try {
        Vector v1(9), v2(10);
        auto v3 = v1 - v2;
        (void)v3;
        return false;
    } catch (std::exception& e) {
        //std::cout << "Caught expected exception: " << e.what() << "\n";
        return true;
    }
}

bool test20() {
    Vector v1(3), v2(4);
    try {
        Vector v1(9), v2(10);
        auto dot = v1 * v2;
        (void)dot;
        return false;
    } catch (const std::exception& e) {
        //std::cout << "Caught expected exception: " << e.what() << "\n";
        return true;
    }
}

bool test15() {
    Vector v1(9);
    for (int i = 0; i < 9; ++i) v1[i] = i;
    Vector v2(v1);
    for (int i = 0; i < 9; ++i)
        if (v1[i] != v2[i]) return false;
    return true;
}

bool test16() {
    Vector v1(9);
    for (int i = 0; i < 9; ++i) v1[i] = i;
    std::ostringstream oss;
    oss << v1;
    std::string output = oss.str();
    return output.front() == '[' && output.back() == ']';
}

bool test17() {
    Vector v(9);
    for (int i = 1; i <= 9; ++i) v(i) = i * 3.0;
    for (int i = 1; i <= 9; ++i)
        if (std::abs(v(i) - i * 3.0) > EPS) return false;
    return true;
}

bool test18() {
    Vector v1(9), v2(9);
    v1 = v1 = v2;
    return v1.size() == 9;
}

bool test19() {
    Vector v(9);
    for (int i = 0; i < 9; ++i) v[i] = 1.0;
    double sum = 0;
    for (int i = 0; i < 9; ++i) sum += v[i];
    return std::abs(sum - 9.0) < EPS;
}

bool test20() {
    Vector v(9);
    for (int i = 0; i < 9; ++i) v[i] = 5.0;
    Vector v2 = v * 0.0;
    for (int i = 0; i < 9; ++i)
        if (std::abs(v2[i]) > EPS) return false;
    return true;
}

int main() {
    for (int i = 1; i <= 20; ++i) {
        bool result = false;
        switch (i) {
            case 1:  result = test1();  break;
            case 2:  result = test2();  break;
            case 3:  result = test3();  break;
            case 4:  result = test4();  break;
            case 5:  result = test5();  break;
            case 6:  result = test6();  break;
            case 7:  result = test7();  break;
            case 8:  result = test8();  break;
            case 9:  result = test9();  break;
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
    return 0;
}
