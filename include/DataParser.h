#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "Matrix.h"
#include "Vector.h"
#include <string>
#include <utility> // for std::pair

class DataParser {
public:
    // Load data and split into train/test sets
    static std::pair<Matrix, Vector> LoadFullData(const std::string& filename);

    // Splits the data matrix and vector into training and testing sets
    static void TrainTestSplit(const Matrix& A, const Vector& b, 
                               Matrix& A_train, Vector& b_train,
                               Matrix& A_test, Vector& b_test,
                               double train_ratio = 0.8);
};

#endif // DATAPARSER_H
