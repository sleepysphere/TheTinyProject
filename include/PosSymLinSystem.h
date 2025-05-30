#ifndef POSSYMLINSYSTEM_HEADER
#define POSSYMLINSYSTEM_HEADER

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);

    // Override Solve with Conjugate Gradient
    Vector Solve() const override;

private:
    bool isSymmetric(const Matrix& A) const;
};

#endif
