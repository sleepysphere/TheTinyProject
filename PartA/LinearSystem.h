#ifndef LINEARSYSTEM_HEADER
#define LINEARSYSTEM_HEADER

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    LinearSystem() = delete; // Disallow default constructor
    LinearSystem(const Matrix& A, const Vector& b); // Main constructor
    virtual ~LinearSystem(); // Destructor

    virtual Vector Solve() const; // Gaussian elimination

protected:
    void swapRows(Matrix& mat, Vector& vec, int i, int j) const;
};

#endif
