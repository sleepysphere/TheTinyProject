#include "../include/Vector.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cmath>

// default ctor
Vector::Vector()
  : mSize(0), mData(nullptr)
{}

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
Vector Vector::operator-(const Vector& rhs) const {
    if (mSize != rhs.mSize) throw std::invalid_argument("Size mismatch");
    Vector tmp(mSize);
    for (std::size_t i = 0; i < mSize; ++i)
        tmp.mData[i] = mData[i] - rhs.mData[i];
    return tmp;
}

// unary plus/minus
Vector Vector::operator+() const {
    return *this;
}
Vector Vector::operator-() const {
    Vector tmp(mSize);
    for (std::size_t i = 0; i < mSize; ++i)
        tmp.mData[i] = -mData[i];
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

// p‐norm
double Vector::Norm(int p) const {
    if (p <= 0) throw std::invalid_argument("Norm order must be > 0");
    double sum = 0.0;
    for (std::size_t i = 0; i < mSize; ++i)
        sum += std::pow(std::abs(mData[i]), double(p));
    return std::pow(sum, 1.0 / p);
}

// non-member scalar*vector
Vector operator*(double s, const Vector& v) {
    return v * s;
}

// stream output
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(";
    for (std::size_t i = 0; i < v.mSize; ++i) {
        os << v.mData[i];
        if (i + 1 < v.mSize) os << ", ";
    }
    os << ")";
    return os;
}