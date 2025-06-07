<table align="center">
  <tr>
    <td><img src="./assets/logo.png" alt="logo" height="80"></td>
    <td><h1 style="margin-left: 20px;">The Tiny Project</h1></td>
  </tr>
</table>

---

# 📘 Project Report: The Tiny Project

**Course**: Programming 2 — VGU - CSE  
**Instructor**: Professor Huỳnh Trung Hiếu  
**Group Members**:  
- Võ Minh Duy — 10423028  
- Đỗ Minh Triết — 10423114  
- Phạm Nguyên Phương — 10423094  

---

## 1. Introduction

**The Tiny Project** is a two-part initiative combining object-oriented C++ design with numerical linear algebra to address a real-world regression task.

- **Part A**: Develop a custom linear algebra library using C++.  
- **Part B**: Apply the library to perform multiple linear regression on CPU performance data.

This project demonstrates proficiency in dynamic memory management, class design, operator overloading, and numerical algorithms.

---

## 2. Objectives

### 🔹 Part A: Linear Algebra Library

- Implement:
  - `Vector` class
  - `Matrix` class
  - `LinearSystem` and `PosSymLinSystem` classes
- Support:
  - Arithmetic operations for vectors and matrices
  - Determinant, inverse, and pseudo-inverse calculations
  - Gaussian elimination and conjugate gradient methods
- Handle:
  - Regularization techniques for non-square systems

### 🔹 Part B: Regression with CPU Data

- Perform multiple linear regression on the [UCI Computer Hardware dataset](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
- Predict target values using the custom solver
- Evaluate accuracy using Root Mean Squared Error (RMSE)

---

## 3. Project Structure
```
.
│   build.bat
│   CMakeLists.txt
│   LICENSE
│   README.md
│   REPORT.md
│   run.bat
│   
├───.vscode
│       launch.json
│       settings.json
│       tasks.json
│       
├───data
│       Index
│       machine.data
│       machine.names
│       
├───include
│       LinearSystem.h
│       Matrix.h
│       PosSymLinSystem.h
│       Vector.h
│       
├───prediction
│       model.txt
│       rmse.log
│       
├───src
│       LinearSystem.cpp
│       main.cpp
│       Matrix.cpp
│       PosSymLinSystem.cpp
│       Vector.cpp
│       
└───test
        TestLinearSystem.cpp
        TestMatrix.cpp
        TestVector.cpp
```

- `include/`: Header files for all core classes  
- `src/`: Source code implementations  
- `test/`: Unit and integration test cases  
- `data/`: Raw dataset for regression  
- `main.cpp`: Entry point for the regression application  
- `report.md`: This project report  

---

## 4. Design & Implementation

### 4.1 Vector Class

- Dynamic 1D array with proper memory management
- Features:
  - Operator overloading (`+`, `-`, `*`, etc.)
  - 1-based indexing with bounds checking
  - Constructors, destructor, and copy semantics

### 4.2 Matrix Class

- 2D array using row-pointer representation
- Capabilities:
  - Matrix arithmetic and scalar ops
  - Determinant and (pseudo-)inverse
  - Copy constructor, deep copy, destructor

### 4.3 Linear System Solvers

- **LinearSystem**:  
  - Solves general square systems using Gaussian Elimination with partial pivoting
- **PosSymLinSystem**:  
  - Inherits from `LinearSystem`, optimized for symmetric positive-definite matrices
  - Uses the Conjugate Gradient method for efficiency

---

## 5. Regression Model on CPU Data

### Dataset

- Source: [**<p style="color:rgb(127,255,255);">UCI Computer Hardware</p>**](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
- Features: `MYCT`, `MMIN`, `MMAX`, `CACH`, `CHMIN`, `CHMAX`  
- Target: `PRP` (Published Relative Performance)

### Approach

1. Normalize input features  
2. Construct system `Ax = b` for regression  
3. Solve using custom solvers (`LinearSystem` or `PosSymLinSystem`)  
4. Split data 80/20 into training and test sets  
5. Evaluate prediction with RMSE:

\[
RMSE = \sqrt{\frac{1}{n} \sum_{i=1}^{n} (y_i - \hat{y}_i)^2}
\]

---

## 6. Testing & Validation

> 🔧 **Status**: _In Progress_

Planned testing includes:

- 20+ test functions per class in the `test/` folder
- Boundary, arithmetic, and memory leak checks
- Regression accuracy on known CPU entries

---

## 7. Results

> 📊 **Status**: _In Progress_

Will include:

- Learned model coefficients  
- RMSE score  
- Visual comparison between predicted vs actual values

---

## 8. Conclusion

This project provided practical experience in both C++ systems programming and applied mathematics. We developed core computational tools from scratch and applied them to meaningful data.

### Key Learnings:

- Translating mathematical models into C++ class hierarchies
- Memory-safe implementation of linear algebra tools
- Application of theoretical methods (like Gaussian Elimination and CG) to solve real regression problems

---

## 9. References

- UCI Machine Learning Repository: [Computer Hardware Data](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)  
- Programming 2 course materials (VGU)  
- Numerical Linear Algebra — Lecture Notes & Supplemental Readings
