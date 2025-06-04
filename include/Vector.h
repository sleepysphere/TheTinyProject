#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <iostream>
#include <stdexcept>

class Vector{
    private:
        int mSize;
        double* mData;

    public:
        Vector();
        Vector(int size);
        Vector(const Vector& other); // Copy constructor
        ~Vector(); // Destructor

        int size() const; // Returns the size of the vector

        Vector& operator=(const Vector& other); // Copy assignment operator
        double& operator[](int index); // Subscript operator (non-const)
        const double& operator[](int index) const; // Subscript operator (const)
        double& operator()(int index); // Parentheses operator (non-const)
        const double& operator()(int index) const; // Parentheses operator (const)

        Vector operator+() const; // Unary plus operator
        Vector operator-() const; // Unary minus operator

        Vector operator+(const Vector& other) const; // Addition operator
        Vector operator-(const Vector& other) const; // Subtraction operator
        Vector operator*(double scalar) const; // Scalar multiplication operator

        friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
        friend Vector operator*(double scalar, const Vector& v);

        double Norm(int p = 2) const; // Computes the norm of the vector
};
#endif