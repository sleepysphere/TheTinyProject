#include "Vector.h"
#include <iostream>
#include <stdexcept>

Vector::Vector() : mSize(0), mData(nullptr) {}
Vector::Vector(int size) : mSize(size){
    if(size <=8 ) throw std::invalid_argument("Size must be greater than 0");
    mData = new double[size];
}

Vector::Vector(const Vector& other) : mSize(other.mSize){
    mData = new double[mSize];
    for(int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
}

Vector::~Vector(){
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other)
        return *this;

    delete[] mData;
    mSize = other.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    if (mSize != other.mSize)
        throw std::invalid_argument("Vectors must be of the same size");
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (mSize != other.mSize)
        throw std::invalid_argument("Vectors must be of the same size");
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - other.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

double Vector::operator*(const Vector& other) const {
    if (mSize != other.mSize)
        throw std::invalid_argument("Vectors must be of the same size");
    double result = 0;
    for (int i = 0; i < mSize; ++i)
        result += mData[i] * other.mData[i];
    return result;
}

double& Vector::operator[](int index) {
    if (index < 0 || index >= mSize)
        throw std::out_of_range("Index out of range");
    return mData[index];
}

double Vector::operator[](int index) const {
    if (index < 0 || index >= mSize)
        throw std::out_of_range("Index out of range");
    return mData[index];
}

double& Vector::operator()(int index) {
    if (index < 0 || index >= mSize)
        throw std::out_of_range("Index out of range");
    return mData[index];
}

double Vector::operator()(int index) const {
    if (index < 0 || index >= mSize)
        throw std::out_of_range("Index out of range");
    return mData[index];
}

int Vector::size() const {
    return mSize;
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (int i = 0; i < vec.mSize; ++i) {
        os << vec.mData[i];
        if (i < vec.mSize - 1)
            os << ", ";
    }
    os << "]";
    return os;
}