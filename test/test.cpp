#include "Vector.h"
#include "Matrix.h"
#include "LinearSystem.h"
#include "PosSymLinSystem.h"
#include <bits/stdc++.h>

using namespace std;

bool test1(){
Vector v1(3);
}
bool test2(){

}
bool test3(){

}
bool test4(){

}
bool test5(){

}

int main(){
    cout<< "Testing Part A" << endl;
    int test = 30;
    int run = 0;
    int passed = 0;
    if(test == 1){
        cout << "Running test 1" << endl;
        if(test1()){
            cout << "Test 1 passed" << endl;
            passed++;
        } else {
            cout << "Test 1 failed" << endl;
        }
        run++;
    }
    if(test == 2){
        cout << "Running test 2" << endl;
        if(test2()){
            cout << "Test 2 passed" << endl;
            passed++;
        } else {
            cout << "Test 2 failed" << endl;
        }
        run++;
    }
    if(test == 3){
        cout << "Running test 3" << endl;
        if(test3()){
            cout << "Test 3 passed" << endl;
            passed++;
        } else {
            cout << "Test 3 failed" << endl;
        }
        run++;
    }
    if(test == 4){
        cout << "Running test 4" << endl;
        if(test4()){
            cout << "Test 4 passed" << endl;
            passed++;
        } else {
            cout << "Test 4 failed" << endl;
        }
        run++;
    }
    if(test == 5){
        cout << "Running test 5" << endl;
        if(test5()){
            cout << "Test 5 passed" << endl;
            passed++;
        } else {
            cout << "Test 5 failed" << endl;
        }
        run++;
    }


}