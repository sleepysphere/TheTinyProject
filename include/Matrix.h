#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <iostream>
#include <cassert>
#include "Vector.h"

class Matrix {
    private:
        int mNumRows;
        int mNumCols;
        double** mData;

    public:
        // Constructors and Destructor
        Matrix(); // Default constructor (disabled)
        Matrix(int numRows, int numCols); // Zero-initialized matrix
        Matrix(const Matrix& other); // Copy constructor
        ~Matrix(); // Destructor

        // Assignment operator
        Matrix& operator=(const Matrix& other);

        // Accessors
        int numRows() const;
        int numCols() const;

        // Element access using 1-based indexing
        double& operator()(int i, int j);
        double operator()(int i, int j) const;

        // Arithmetic operators
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const; // Matrix multiplication
        Vector operator*(const Vector& vec) const;   // Matrix-vector multiplication
        Matrix operator*(double scalar) const;       // Scalar multiplication

        // Determinant, Tranpose and Inverse
        double determinant() const;
        Matrix transpose() const;
        Matrix inverse() const;
        Matrix pseudoInverse() const;

        // Stream insertion
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};

#endif
