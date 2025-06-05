#ifndef POSSYMLINSYSTEM_HEADER
#define POSSYMLINSYSTEM_HEADER

#include "LinearSystem.h"
#include <stdexcept>

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    Vector Solve() const override;

private:
    bool isSymmetric(const Matrix& A) const;
};

#endif
