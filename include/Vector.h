#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

class Vector {
private:
    std::size_t mSize;
    double*     mData;
public:
    Vector();                    // ← add this
    Vector(std::size_t size);

    // copy ctor
    Vector(const Vector& other);

    // copy assignment
    Vector& operator=(const Vector& other);

    // dtor
    ~Vector();

    std::size_t size() const { return mSize; }

    // zero-based indexing
    double&       operator[](std::size_t idx);
    const double& operator[](std::size_t idx) const;

    // one-based indexing
    double&       operator()(std::size_t idx);
    const double& operator()(std::size_t idx) const;

    // vector + vector, vector – vector
    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;

    // unary plus/minus
    Vector operator+() const;
    Vector operator-() const;

    // p‐norm (p > 0)
    double Norm(int p) const;

    // scalar multiply
    Vector operator*(double s) const;

    // dot product
    double operator*(const Vector& rhs) const;

    // chainable assignment
    // (friend to allow scalar*vector syntax)
    friend Vector operator*(double s, const Vector& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};

#endif