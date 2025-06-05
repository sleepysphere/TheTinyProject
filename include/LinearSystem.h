#ifndef LINEARSYSTEM_HEADER
#define LINEARSYSTEM_HEADER

#include "Matrix.h"
#include "Vector.h"
#include <stdexcept>

class LinearSystem {
public:
    LinearSystem() = delete;
    // now accepts rectangular A.  lambda==0 → pseudo-inverse; lambda>0 → Tikhonov
    LinearSystem(const Matrix& A, const Vector& b, double lambda = 0.0);

    // no copy
    LinearSystem(const LinearSystem&) = delete;
    LinearSystem& operator=(const LinearSystem&) = delete;

    virtual ~LinearSystem();

    // virtual so you can override if desired
    virtual Vector Solve() const;

protected:
    int     mSize;    // #rows of A
    Matrix* mpA;
    Vector* mpb;
    double  mLambda;  // regularization parameter

    // keep for square-case elimination
    void swapRows(Matrix& M, Vector& v, int i, int j) const;
};

#endif
