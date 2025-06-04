#include "../include/Vector.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>

Vector::Vector() : mSize(0), mData(nullptr) {}

Vector::Vector(int size) {
    assert(size >= 0);
    mSize = size;
    if (mSize > 0) {
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i) {
            mData[i] = 0.0;
        }
    } else {
        mData = nullptr;
    }
}

Vector::Vector(const Vector& otherVector) {
    mSize = otherVector.mSize;
    if (mSize > 0) {
        mData = new double[mSize];
        for (int i = 0; i < mSize; i++) {
            mData[i] = otherVector.mData[i];
        }
    } else {
        mData = nullptr;
    }
}

Vector::~Vector(){
    delete[] mData;
}

int Vector::size() const {
    return mSize;
}

Vector& Vector::operator=(const Vector& otherVector) {
    if (this == &otherVector) {
        return *this;
    }
    if (mSize != otherVector.mSize && mData != nullptr) {
        delete[] mData;
        mData = nullptr;
    }
    mSize = otherVector.mSize;
    if (mSize > 0) {
        if (mData == nullptr) {
            mData = new double[mSize];
        }
        for (int i = 0; i < mSize; i++) {
            mData[i] = otherVector.mData[i];
        }
    } else {
        mData = nullptr;
    }
    return *this;
}

double& Vector::operator[](int index) {
    if (index < 0 || index >= mSize) { // Check bounds
        throw std::out_of_range("Index out of bounds (0-based)"); // Throw exception
    }
    return mData[index];
}

const double& Vector::operator[](int index) const {
    if (index < 0 || index >= mSize) { // Check bounds
        throw std::out_of_range("Index out of bounds (0-based)"); // Throw exception
    }
    return mData[index];
}

double& Vector::operator()(int index) {
    if (index < 1 || index > mSize)
        throw std::out_of_range("Index out of bounds (1-based)");
    return mData[index - 1];
}

const double& Vector::operator()(int index) const {
    if (index < 1 || index > mSize)
        throw std::out_of_range("Index out of bounds (1-based)");
    return mData[index - 1];
}


Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = -mData[i];
    }
    return result;
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

Vector operator*(double scalar, const Vector& v) {
    return v * scalar;
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

double Vector::Norm(int p) const {
    assert(p >= 1);
    double sum = 0.0;
    
    if (p == 1) {
        for (int i = 0; i < mSize; ++i) {
            sum += std::abs(mData[i]);
        }
        return sum;
    }

    if (p == 2) {
        for (int i = 0; i < mSize; ++i) {
            sum += mData[i] * mData[i];
        }
        return std::sqrt(sum);
    }

    for (int i = 0; i < mSize; ++i) {
        sum += std::pow(std::abs(mData[i]), p);
    }

    return std::pow(sum, 1.0/p);
}
