#include "../include/Vector.h"
#include <bits/stdc++.h>

const double EPS = 1e-9;

bool test1() {
    try {
        Vector v(9);
        return v.size() == 9;
    } catch (...) {
        return false;
    }
}

bool test2() {
    try {
        Vector v(5); // Should throw
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test3() {
    Vector v(9);
    v[0] = 1.5;
    return std::abs(v[0] - 1.5) < EPS;
}

bool test4() {
    Vector v(9);
    v(1) = 2.3;
    return std::abs(v(1) - 2.3) < EPS;
}

bool test5() {
    try {
        Vector v(9);
        v[10] = 5.0; // out of bounds
        return false;
    } catch (const std::out_of_range&) {
        return true;
    }
}

bool test6() {
    try {
        Vector v(9);
        double x = v(-1); // out of bounds
        return false;
    } catch (const std::out_of_range&) {
        return true;
    }
}

bool test7() {
    Vector v1(9), v2(9);
    for (int i = 0; i < 9; ++i) v1[i] = i;
    v2 = v1;
    for (int i = 0; i < 9; ++i)
        if (v2[i] != v1[i]) return false;
    return true;
}

bool test8() {
    Vector v1(9), v2(9);
    for (int i = 0; i < 9; ++i) {
        v1[i] = i;
        v2[i] = i * 2;
    }
    Vector v3 = v1 + v2;
    for (int i = 0; i < 9; ++i)
        if (v3[i] != v1[i] + v2[i]) return false;
    return true;
}

bool test9() {
    Vector v1(9), v2(9);
    for (int i = 0; i < 9; ++i) {
        v1[i] = i;
        v2[i] = i * 3;
    }
    Vector v3 = v2 - v1;
    for (int i = 0; i < 9; ++i)
        if (v3[i] != v2[i] - v1[i]) return false;
    return true;
}

bool test10() {
    Vector v(9);
    for (int i = 0; i < 9; ++i) v[i] = i + 1;
    Vector v2 = v * 2.0;
    for (int i = 0; i < 9; ++i)
        if (std::abs(v2[i] - 2 * v[i]) > EPS) return false;
    return true;
}

bool test11() {
    Vector v1(9), v2(9);
    for (int i = 0; i < 9; ++i) {
        v1[i] = i + 1;
        v2[i] = 1.0;
    }
    return std::abs(v1 * v2 - 45.0) < EPS; // sum of 1 to 9 = 45
}

bool test12() {
    try {
        Vector v1(9), v2(10);
        auto v3 = v1 + v2;
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test13() {
    try {
        Vector v1(9), v2(10);
        auto v3 = v1 - v2;
        return false;
    } catch (const std::invalid_argument&) {
        return true;
    }
}

bool test14() {
    try {
        Vector v1(9), v2(10);
        auto dot = v1 * v2;
        return false;
    } catch (const std::invalid_argument&) {
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
    return output.find("[") == 0 && output.find("]") == output.size() - 1;
}

bool test17() {
    Vector v(9);
    for (int i = 0; i < 9; ++i) v(i) = i * 3.0;
    for (int i = 0; i < 9; ++i)
        if (v(i) != i * 3.0) return false;
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
