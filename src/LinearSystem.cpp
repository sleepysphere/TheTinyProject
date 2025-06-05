#include "../include/LinearSystem.h"
#include <cmath>
#include <algorithm>

// now allow any A with matching b.length()
LinearSystem::LinearSystem(const Matrix& A, const Vector& b, double lambda)
  : mSize(A.numRows()),
    mpA(new Matrix(A)),
    mpb(new Vector(b)),
    mLambda(lambda)
{
    if (static_cast<int>(b.size()) != A.numRows())
        throw std::invalid_argument("Size mismatch between A.rows and b.size");
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

void LinearSystem::swapRows(Matrix& M, Vector& v, int i, int j) const {
    for (int col = 1; col <= mSize; ++col)
        std::swap(M(i,col), M(j,col));
    std::swap(v[i-1], v[j-1]);
}

Vector LinearSystem::Solve() const {
    int rows = mpA->numRows();
    int cols = mpA->numCols();

    // 1) square & no regularization → classic elimination
    if (mLambda == 0.0 && rows == cols) {
        Matrix A = *mpA;
        Vector b = *mpb;
        // forward elimination
        for(int k=1; k<=rows; ++k){
            // pivot
            int piv = k;
            double maxv = std::fabs(A(k,k));
            for(int i=k+1; i<=rows; ++i){
                double v = std::fabs(A(i,k));
                if (v>maxv) { maxv=v; piv=i; }
            }
            if (std::fabs(maxv) < 1e-12)
                throw std::runtime_error("Singular matrix");
            if (piv!=k) swapRows(A,b,k,piv);
            // eliminate
            for(int i=k+1; i<=rows; ++i){
                double f = A(i,k)/A(k,k);
                for(int j=k; j<=rows; ++j) A(i,j)-=f*A(k,j);
                b[i-1] -= f*b[k-1];
            }
        }
        // back-sub
        Vector x(rows);
        for(int i=rows; i>=1; --i){
            double sum=0;
            for(int j=i+1; j<=rows; ++j)
                sum += A(i,j)*x[j-1];
            x[i-1] = (b[i-1]-sum)/A(i,i);
        }
        return x;
    }

    // 2) λ==0 but rectangular → Moore–Penrose
    if (mLambda == 0.0) {
        Matrix Aplus = mpA->pseudoInverse();
        return Aplus * *mpb;
    }

    // 3) λ>0 → Tikhonov: x=(AᵀA+λI)⁻¹ Aᵀ b
    {
        Matrix At = mpA->transpose();          // dim: cols×rows
        Matrix ATA = At * *mpA;                // cols×cols
        // add λI
        for(int i=1; i<=ATA.numRows(); ++i)
            ATA(i,i) += mLambda;
        Vector rhs = At * *mpb;                // length cols
        Matrix inv = ATA.inverse();            // cols×cols
        return inv * rhs;                      // length cols
    }
}
