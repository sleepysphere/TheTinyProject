#include "../include/DataParser.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

std::pair<Matrix, Vector> DataParser::LoadFullData(const std::string& filename) {
    std::ifstream file("../data/machine.data");
    std::string line;
    std::vector<std::vector<double>> features;
    std::vector<double> targets;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> tokens;

        while (std::getline(ss, value, ',')) {
            tokens.push_back(value);
        }

        if (tokens.size() >= 9) {
            std::vector<double> row;
            for (int i = 2; i <= 7; ++i) { // MYCT to CHMAX
                row.push_back(std::stod(tokens[i]));
            }
            features.push_back(row);
            targets.push_back(std::stod(tokens[8])); // PRP
        }
    }

    size_t n = features.size();
    Matrix A(n, 6);
    Vector b(n);

    for (size_t i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            A(i + 1, j + 1) = features[i][j];
        }
        b(i + 1) = targets[i];
    }

    return { A, b };
}

void DataParser::TrainTestSplit(const Matrix& A, const Vector& b,
                                Matrix& A_train, Vector& b_train,
                                Matrix& A_test, Vector& b_test,
                                double train_ratio) {
    size_t n = A.numRows();
    std::vector<size_t> indices(n);
    for (size_t i = 0; i < n; ++i) indices[i] = i;

    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(static_cast<unsigned>(std::time(0))));

    size_t train_size = static_cast<size_t>(train_ratio * n);

    A_train = Matrix(train_size, 6);
    b_train = Vector(train_size);
    A_test = Matrix(n - train_size, 6);
    b_test = Vector(n - train_size);

    for (size_t i = 0; i < train_size; ++i) {
        for (int j = 0; j < 6; ++j) {
            A_train(i + 1, j + 1) = A(indices[i] + 1, j + 1);
        }
        b_train(i + 1) = b(indices[i] + 1);
    }

    for (size_t i = train_size; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            A_test(i - train_size + 1, j + 1) = A(indices[i] + 1, j + 1);
        }
        b_test(i - train_size + 1) = b(indices[i] + 1);
    }
}
