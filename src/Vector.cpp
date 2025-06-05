#include "../include/Vector.h"
#include <algorithm>

#include <iostream>
#include <stdexcept>

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
// ctor
Vector::Vector(std::size_t size)
  : mSize(size), mData(nullptr)
{
    if (mSize == 0)
        throw std::invalid_argument("Vector size must be > 0");
    mData = new double[mSize];
    std::fill(mData, mData + mSize, 0.0);
}

// copy ctor
Vector::Vector(const Vector& other)
  : mSize(other.mSize),
    mData(new double[other.mSize])
{
    std::copy(other.mData, other.mData + mSize, mData);
}

// copy assignment
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        if (mSize != other.mSize) {
            delete[] mData;
            mSize = other.mSize;
            mData = new double[mSize];
        }
        std::copy(other.mData, other.mData + mSize, mData);
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

// dtor
Vector::~Vector() {
    delete[] mData;
}

// zero-based
double& Vector::operator[](std::size_t idx) {
    if (idx >= mSize) throw std::out_of_range("Index out of range");
    return mData[idx];
}
const double& Vector::operator[](std::size_t idx) const {
    if (idx >= mSize) throw std::out_of_range("Index out of range");
    return mData[idx];
}

// one-based
double& Vector::operator()(std::size_t idx) {
    if (idx < 1 || idx > mSize) throw std::out_of_range("Index out of range");
    return mData[idx-1];
}
const double& Vector::operator()(std::size_t idx) const {
    if (idx < 1 || idx > mSize) throw std::out_of_range("Index out of range");
    return mData[idx-1];
}

// vector sum/diff
Vector Vector::operator+(const Vector& rhs) const {
    if (mSize != rhs.mSize) throw std::invalid_argument("Size mismatch");
    Vector tmp(mSize);
    for (std::size_t i = 0; i < mSize; ++i)
        tmp.mData[i] = mData[i] + rhs.mData[i];
    return tmp;
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

// dtor
Vector::~Vector() {
    delete[] mData;
}

// zero-based
double& Vector::operator[](std::size_t idx) {
    if (idx >= mSize) throw std::out_of_range("Index out of range");
    return mData[idx];
}
const double& Vector::operator[](std::size_t idx) const {
    if (idx >= mSize) throw std::out_of_range("Index out of range");
    return mData[idx];
}

// one-based
double& Vector::operator()(std::size_t idx) {
    if (idx < 1 || idx > mSize) throw std::out_of_range("Index out of range");
    return mData[idx-1];
}
const double& Vector::operator()(std::size_t idx) const {
    if (idx < 1 || idx > mSize) throw std::out_of_range("Index out of range");
    return mData[idx-1];
}

// vector sum/diff
Vector Vector::operator+(const Vector& rhs) const {
    if (mSize != rhs.mSize) throw std::invalid_argument("Size mismatch");
    Vector tmp(mSize);
    for (std::size_t i = 0; i < mSize; ++i)
        tmp.mData[i] = mData[i] + rhs.mData[i];
    return tmp;
}
Vector Vector::operator-(const Vector& rhs) const {
    if (mSize != rhs.mSize) throw std::invalid_argument("Size mismatch");
    Vector tmp(mSize);
    for (std::size_t i = 0; i < mSize; ++i)
        tmp.mData[i] = mData[i] - rhs.mData[i];
    return tmp;
}

// scalar multiply
Vector Vector::operator*(double s) const {
    Vector tmp(mSize);
    for (std::size_t i = 0; i < mSize; ++i)
        tmp.mData[i] = mData[i] * s;
    return tmp;
}

// dot product
double Vector::operator*(const Vector& rhs) const {
    if (mSize != rhs.mSize) throw std::invalid_argument("Size mismatch");
    double sum = 0;
    for (std::size_t i = 0; i < mSize; ++i)
        sum += mData[i] * rhs.mData[i];
    return sum;
}

// non-member scalar*vector
Vector operator*(double s, const Vector& v) {
    return v * s;
}

// stream output
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (std::size_t i = 0; i < v.mSize; ++i) {
        os << v.mData[i];
        if (i + 1 < v.mSize) os << ", ";
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
