#include "../include/DataParser.h"
#include <fstream>
#include <iostream>
#include <cassert>

bool test1() {
    std::ofstream f("data/mock.data");
    f << "x,y,10,20,30,40,5,7,111,0\n";
    f << "a,b,1,2,3,4,1,2,222,0\n";
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/mock.data");
    return A.numRows() == 2 && A.numCols() == 6 && std::abs(b(1) - 222) < 1e-9;
}

bool test2() {
    std::ofstream f("data/empty.data"); f.close();
    auto [A, b] = DataParser::LoadFullData("data/empty.data");
    return A.numRows() == 0 && b.size() == 0;
}

bool test3() {
    std::ofstream f("data/invalid.data");
    f << "only,one,row\n";
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/invalid.data");
    return A.numRows() == 0;
}

bool test4() {
    std::ofstream f("data/partial.data");
    f << "x,y,1,2,3,4,5,6,123\n"; // 9 columns
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/partial.data");
    return A.numRows() == 1 && std::abs(b(0) - 123) < 1e-9;
}

bool test5() {
    std::ofstream f("data/whitespace.data");
    f << "a,b, 1 , 2 ,3,4,5,6,99,0\n";
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/whitespace.data");
    return std::abs(b(0) - 99) < 1e-9;
}

bool test6() {
    std::ofstream f("data/four.data");
    f << "x,y,1,2,3,4,5,6,100,0\n";
    f << "x,y,2,3,4,5,6,7,200,0\n";
    f << "x,y,3,4,5,6,7,8,300,0\n";
    f << "x,y,4,5,6,7,8,9,400,0\n";
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/four.data");
    Matrix A_train, A_test;
    Vector b_train, b_test;
    DataParser::TrainTestSplit(A, b, A_train, b_train, A_test, b_test, 0.5);
    return A_train.numRows() == 2 && A_test.numRows() == 2;
}

bool test7() {
    std::ofstream f("data/one.data");
    f << "x,y,1,2,3,4,5,6,100,0\n";
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/one.data");
    Matrix A_train, A_test;
    Vector b_train, b_test;
    DataParser::TrainTestSplit(A, b, A_train, b_train, A_test, b_test);
    return A_train.numRows() == 1;
}

bool test8() {
    std::ofstream f("data/mix.data");
    f << "x,y,1,2,3,4,5,6,123,0\n";
    f << "junk,row\n";
    f << "x,y,2,3,4,5,6,7,234,0\n";
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/mix.data");
    return A.numRows() == 2 && b.size() == 2;
}

bool test9() {
    try {
        DataParser::LoadFullData("data/does_not_exist.data");
        return false;
    } catch (...) {
        return true;
    }
}

bool test10() {
    std::ofstream f("data/fixed.data");
    f << "x,y,1,2,3,4,5,6,100,0\n";
    f.close();
    auto [A, b] = DataParser::LoadFullData("data/fixed.data");
    return A.numRows() == 1 && A.numCols() == 6;
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
