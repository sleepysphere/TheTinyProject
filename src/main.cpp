#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <random>

#include "Vector.h"
#include "Matrix.h"
#include "LinearSystem.h"
#include "PosSymLinSystem.h"

std::vector<std::string> split_string(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

struct DataRecord {
    std::vector<double> features;
    double target;
};


int main() {
    std::string filename = "machine.data";
    std::ifstream data_file(filename);

    if (!data_file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::vector<DataRecord> all_records;
    std::string line;

    std::cout << "Reading data from " << filename << "..." << std::endl;

    int line_count = 0;
    while (std::getline(data_file, line)) {
        line_count++;
        std::vector<std::string> values = split_string(line, ',');
        if (values.size() == 10) {
            try {
                DataRecord record;
                record.features.push_back(std::stod(values[2]));
                record.features.push_back(std::stod(values[3]));
                record.features.push_back(std::stod(values[4]));
                record.features.push_back(std::stod(values[5]));
                
                record.features.push_back(std::stod(values[7]));
                record.target = std::stod(values[8]);
                all_records.push_back(record);
            } catch (const std::invalid_argument& ia) {
                std::cerr << "Warning: Invalid argument for stod at line " << line_count << ": " << line << ". Skipping." << std::endl;
            } catch (const std::out_of_range& oor) {
                std::cerr << "Warning: Out of range for stod at line " << line_count << ": " << line << ". Skipping." << std::endl;
            }
        } else {
            std::cerr << "Warning: Line " << line_count << " does not have 10 columns: " << line << ". Skipping." << std::endl;
        }
    }
    data_file.close();
    std::cout << "Successfully read " << all_records.size() << " records." << std::endl;

    if (all_records.empty()) {
        std::cerr << "Error: No data records were read. Exiting." << std::endl;
        return 1;
    }
    if (all_records.size() < 2) {
        std::cerr << "Error: Not enough data for train/test split. Need at least 2 records." << std::endl;
        return 1;
    }

    size_t total_samples = all_records.size();
    size_t train_size = static_cast<size_t>(total_samples * 0.8);
    size_t test_size = total_samples - train_size;

    if (train_size == 0 || test_size == 0) {
        std::cerr << "Error: Train or test set size is 0. Adjust data or split ratio." << std::endl;
        return 1;
    }
    
    std::cout << "Total samples: " << total_samples << std::endl;
    std::cout << "Training samples: " << train_size << std::endl;
    std::cout << "Testing samples: " << test_size << std::endl;

    int num_features = 5;

    Matrix X_train(train_size, num_features);
    Vector y_train(train_size);

    for (size_t i = 0; i < train_size; ++i) {
        for (int j = 0; j < num_features; ++j) {
            X_train(i + 1, j + 1) = all_records[i].features[j];
        }
        y_train(i + 1) = all_records[i].target;
    }

    Matrix X_test(test_size, num_features);
    Vector y_test(test_size);

    for (size_t i = 0; i < test_size; ++i) {
        for (int j = 0; j < num_features; ++j) {
            X_test(i + 1, j + 1) = all_records[train_size + i].features[j];
        }
        y_test(i + 1) = all_records[train_size + i].target;
    }

    std::cout << "Training and testing sets created." << std::endl;

    std::cout << "Formulating linear system..." << std::endl;
    Matrix X_train_T = X_train.Transpose();
    Matrix A_ls = X_train_T * X_train;
    Vector b_ls = X_train_T * y_train;

    std::cout << "Matrix A_ls (X_train^T * X_train):\n" << A_ls << std::endl;
    std::cout << "Vector b_ls (X_train^T * y_train):\n" << b_ls << std::endl;
    
    if (A_ls.GetNumberOfRows() == 0 || b_ls.GetSize() == 0) {
        std::cerr << "Error: A_ls or b_ls is empty. Check data and matrix operations." << std::endl;
        return 1;
    }


    std::cout << "Solving linear system for model parameters..." << std::endl;
    
    LinearSystem lin_sys(A_ls, b_ls); 
    Vector parameters_x = lin_sys.Solve();

    std::cout << "\nModel Parameters (x1 to x5):" << std::endl;
    std::vector<std::string> feature_names = {"MYCT", "MMIN", "MMAX", "CACH", "CHMAX"};
    if (parameters_x.GetSize() == num_features) {
        for (int i = 0; i < num_features; ++i) {
            std::cout << "x" << (i + 1) << " (" << feature_names[i] << "): "
                      << std::fixed << std::setprecision(4) << parameters_x(i + 1) << std::endl;
        }
    } else {
        std::cerr << "Error: Number of solved parameters (" << parameters_x.GetSize() 
                  << ") does not match expected number of features (" << num_features << ")." << std::endl;
        std::cout << "Solved parameters: " << parameters_x << std::endl;
    }

    std::cout << "\nMaking predictions on the test set..." << std::endl;
    if (X_test.GetNumberOfRows() == 0 || parameters_x.GetSize() == 0) {
         std::cerr << "Error: X_test or parameters_x is empty. Cannot make predictions." << std::endl;
         return 1;
    }
    Vector y_pred_test = X_test * parameters_x;

    if (y_test.GetSize() != y_pred_test.GetSize() || y_test.GetSize() == 0) {
        std::cerr << "Error: Test target vector and prediction vector size mismatch or empty." << std::endl;
        return 1;
    }

    Vector diff = y_test - y_pred_test;
    double sse = 0.0;
    for (int i = 1; i <= diff.GetSize(); ++i) {
        sse += diff(i) * diff(i);
    }
    double mse = sse / static_cast<double>(diff.GetSize());
    double rmse = std::sqrt(mse);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nRoot Mean Square Error (RMSE) on Testing Set: " << rmse << std::endl;

    Vector y_pred_train = X_train * parameters_x;
    Vector diff_train = y_train - y_pred_train;
    double sse_train = 0.0;
    for (int i = 1; i <= diff_train.GetSize(); ++i) {
        sse_train += diff_train(i) * diff_train(i);
    }
    double mse_train = sse_train / static_cast<double>(diff_train.GetSize());
    double rmse_train = std::sqrt(mse_train);
    std::cout << "Root Mean Square Error (RMSE) on Training Set: " << rmse_train << std::endl;

    return 0;
}
