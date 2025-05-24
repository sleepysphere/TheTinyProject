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

        Vector& operator=(const Vector& other); // Copy assignment operator
        Vector operator+(const Vector& other) const; // Addition operator
        Vector operator-(const Vector& other) const; // Subtraction operator
        Vector operator*(double scalar) const; // Scalar multiplication operator
        double operator*(const Vector& other) const; // Dot product operator

        double& operator[](int index); // Subscript operator (non-const)
        double operator[](int index) const; // Subscript operator (const)
        double& operator()(int index); // Parentheses operator (non-const)
        double operator()(int index) const; // Parentheses operator (const)

        int size() const; // Returns the size of the vector
        
        friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
};
#endif