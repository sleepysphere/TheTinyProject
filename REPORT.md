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

The Tiny Project is a comprehensive application of object-oriented programming and numerical linear algebra. It is divided into two parts: (A) implementing a custom C++ linear algebra library and (B) applying this library to solve a real-world regression problem using CPU performance data.

The project demonstrates practical understanding of C++ features such as dynamic memory allocation, operator overloading, class inheritance, and abstraction through a modular and test-driven development approach.

---

## 2. Objectives

### Part A: Numerical Linear Algebra Library

- Design and implement:
  - `Vector` class
  - `Matrix` class
  - `LinearSystem` and derived `PosSymLinSystem` class
- Support:
  - Vector and matrix arithmetic
  - Determinants, inverse, and pseudo-inverse
  - Gaussian elimination and conjugate gradient method
- Handle:
  - Underdetermined and overdetermined systems using regularization techniques

### Part B: Real-World Application via Regression

- Perform multiple linear regression on the UCI Computer Hardware dataset
- Use the linear system solvers from Part A to compute model parameters
- Evaluate using RMSE on test data

---

## 3. Design & Implementation

### 3.1 Vector Class

- Encapsulates a one-dimensional array with dynamic memory
- Supports arithmetic operations, 1-based indexing, and boundary checks
- Includes:
  - Overloaded operators
  - Specialized constructor and destructor
  - Error-checking mechanisms

### 3.2 Matrix Class

- Represents a 2D dynamic matrix with row pointers
- Key features:
  - Copy constructor and destructor
  - Arithmetic and scalar operations
  - Determinant and inverse methods
  - Pseudo-inverse using SVD or similar techniques

### 3.3 LinearSystem & PosSymLinSystem

- `LinearSystem` solves square systems via Gaussian Elimination with pivoting
- `PosSymLinSystem` extends it for symmetric positive-definite matrices using the conjugate gradient method
- Ensures safe usage through constructor restrictions and protected inheritance

---

## 4. Regression Model on CPU Data

- Dataset: [UCI Computer Hardware](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
- Goal: Predict `PRP` (Published Relative Performance) based on six numerical features
- Model:
  \[
  PRP = x_1 \cdot MYCT + x_2 \cdot MMIN + x_3 \cdot MMAX + x_4 \cdot CACH + x_5 \cdot CHMIN + x_6 \cdot CHMAX
  \]
- Method:
  - Normalize data
  - Formulate as Ax = b
  - Use solver to compute x
  - Evaluate on 20% test split using RMSE

---

## 5. Testing & Validation

<h5 style='color:red'> WORKING ON THIS LATER </h5>

---

## 6. Results

<h5 style='color:red'> WORKING ON THIS LATER </h5>

---

## 7. Conclusion

This project solidified our understanding of both object-oriented C++ and numerical computation. We built foundational tools from the ground up and applied them to a real-world data science problem.

We learned how mathematical theory can be translated into efficient code and how to manage complexity through modular class design. This practical integration of C++ and linear algebra has been both challenging and rewarding.

---

## 8. References

- UCI Machine Learning Repository: [<blue>Computer Hardware Data</blue>](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
- Lecture materials and lab exercises from Programming 2 (VGU)
