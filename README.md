
# The Tiny Project

**VGU - CSE - Programming 2**

---

**Members**

- *Võ Minh Duy           -   10423028*
- *Đỗ Minh Triết         -   10423114*
- *Phạm Nguyên Phương    -   10423094*

**Instructor**

- *Professor Huỳnh Trung Hiếu*

## Objectives

This project is divided into two main parts and focuses on implementing mathematical structures and solving real-world linear algebra problems, both analytically and in application to data.

### Part A

<span style="color:white;">

> You are required to build the ***Vector*** class and ***Matrix*** class. These classes are then combined into a ***LinearSystem*** class (or alternative classes derived from it) which has methods for solving systems of the form ***Ax = b*** for ***x***. You are required to define files *.h* or *.hpp* and *.cpp* for ***Vector***, ***Matrix*** and ***LinearSystem*** classes.

</span>

<span style="color:white;">

1. > You are required to develop a class of matrices called ***Vector***. It will include constructors anddestructors that handle memory management. It will overload the assignment, unary and binary operators to allow addition, subtraction, and multiplication of vectors and scalars. The square bracket operator will be overloaded for the vector class to provide a check that the index of the array lies within the correct range, and the round bracket operator will be overloaded to allow the entries of the vector to be accessed, indexing from 1 rather than from zero. The class should have private members mSize (the size of the array) and mData that is a pointer to a data element of array.

2. > You are required develop a class of matrices called ***Matrix***. It should include the features listed below. Your class should have private members *mNumRows* and *mNumCols* that are integers and store the number of rows and columns, and *mData* that is a pointer to a pointer to a data element of matrix, which stores the address of the pointer to the first entry of the first row:
    >>- An overridden copy constructor that copies the variables *mNumRows* and *mNumCols*, allocates memory for a new matrix, and copies the entries of the original matrix into the new matrix.
    >>- A constructor that accepts two positive integers *numRows* and *numCols* as input, assigns these values to the class members *mNumRows* and *mNumCols*, allocates memory for a matrix of sizee*mNumRows* bth*mNumCols*, and initialises all entries to zero.
    >>- An overridden destructor that frees the memory that has been allocated to the matrix.
    >>- Public methods for accessing the number of rows, and the number of columns.
    >>- An overloaded round bracket operator with one-based indexing for accessing the entries ofthe matrix so that, provided i and j are valid indices for the matrix, *A(i,j)* may be used to access *mData[i-1][j-1]*.
    >>- Overloaded assignment, unary and binary operators to allow addition, subtraction and multiplication of suitably sized matrices, vectors and scalars. You should use assert statements to ensure the matrices and vectors are of the correct size.
    >>- A public method that computes the determinant of a given square matrix.
    >>- A public method that computes the inverse of a given square matrix.
    >>- A public method that computes the pseudo-inverse (Moore-Penrose inverse) of a given matrix

3. > You are required to develop a class called ***LinearSystem*** that may be used to solve linear systems. Assuming the system is nonsingular, a linear system is defined by the size of the linear system, a square matrix, and vector (representing the right-hand side), with the matrix and vector being of compatible sizes. The data associated with this class may be specified 2 through an integer variable mSize, a pointer to a matrix mpA, and a pointer to the vector on the right-hand side of the linear system mpb. We suggest only allowing the user to set up a linear system using a constructor that requires specification of the matrix and vector: the member mSize may then be determined from these two members. If you do not wish to provide a copy constructor, then the automatically generated copy constructor should be overridden and made private to prevent its use. As with the class of vectors, we recommend that use of the automatically generated default constructor is prevented by providing a specialised constructor but no default constructor. A public method Solve should be written to solve this linear system by Gaussian elimination with pivoting. This method should return a vector that contains the solution of the linear system. Derive a class called ***PosSymLinSystem*** (or similar) from the class ***LinearSystem*** that may be used for the solution of positive definite symmetric linear systems. Make the method Solve a virtual method of the class ***LinearSystem***, and override this method in the class ***PosSymLinSystem*** so that it uses the conjugate gradient method for solving linear systems. If you declared ***LinearSystem*** member data as private, then this should now be declared protected. Your class ***PosSymLinSystem*** should perform a check that the matrix used is symmetric: testing that the matrix is positive definite would be rather difficult and so we don’t suggest performing a check for this property. Test your class using suitable examples.

4. > You will develop the solutions for under-determined or over-determined linear system, where the matrix **A** is not square. The solutions can use the Moore-Penrose inverse and/or Tikhonov regularization to deal with the Ill-posed problem.

</span>

### Part B

> You will develop a linear regression prediction of relative cpu performance. Dataset could be downloaded from UCI: <ins>*<https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware>*</ins>. The number of instances is 209. Every instance has 10 features (6 predictive attributes, 2 non-predictive, 1 goal field, and the linear regression's guess):
>> 1.   Vendor name
>> 2.   Model Name: many unique symbols
>> 3.   MYCT: machine cycle time in nanoseconds (integer)
>> 4.   MMIN: minimum main memory in kilobytes (integer)
>> 5.   MMAX: maximum main memory in kilobytes (integer)
>> 6.   CACH: cache memory in kilobytes (integer)
>> 7.   CHMIN: minimum channels in units (integer)
>> 8.   CHMAX: maximum channels in units (integer)
>> 9.   PRP: published relative performance (integer)
>> 10.  ERP: estimated relative performance from the original article (integer)

> We assume that there is a linear regression model for determining the relative performance as ***PRP=x1\*MYCT+ x2\*MMIN+ x3\*MMAX+ x4\*CACH+ x5\*CHMIN+ x6\*CHMAX*** *(1)* where xi’s are parameters of model. You utilize the above methods for solving systems to find theparameters of *(1)*. The dataset is divided into two sets, training set (80%) is used to determine model parameters and testing set (20%) is used for evaluation. The evaluation can use the criterion of root mean square errors (RMSEs).

## Execution

### File Structure
```
TheTinyProject./
        .
        │   CMakeLists.txt
        │   LICENSE
        │   README.md
        │   REPORT.tex
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
                runLinearSystem.bat
                runMatrix.bat
                runVector.bat
                TestLinearSystem.cpp
                TestLinearSystem.exe
                TestMatrix.cpp
                TestMatrix.exe
                TestVector.cpp
                TestVector.exe
```
### Compile and Execute

#### Part A

- **Vector**

    - Run this in your terminal at `TheTinyProject/test` *`./runVector.bat`*

        **`runVector.bat`**

        ```
        @echo off
        echo Compiling...
        cd .. 
        g++ -Iinclude src\Vector.cpp test\TestVector.cpp -o test\TestVector.exe

        if %errorlevel% equ 0 (
            echo Running...
            test\TestVector.exe
        ) else (
            echo Compilation failed.
        )
        ```
- **Matrix**

    - Run this in your terminal at `TheTinyProject/test` *`./runMatrix.bat`*

        **`runMatrix.bat`**

        ```
        @echo off
        echo Compiling...
        cd .. 
        g++ -Iinclude src\Vector.cpp src\Matrix.cpp test\TestMatrix.cpp -o test\TestMatrix.exe

        if %errorlevel% equ 0 (
            echo Running...
            test\TestMatrix.exe
        ) else (
            echo Compilation failed.
        )
        ```
- **Linear System**

    - Run this in your terminal at `TheTinyProject/test` *`./runLinearSystem.bat`*

        **`runLinearSystem.bat`**

        ```
        @echo off
        echo Compiling...
        cd .. 
        g++ -Iinclude src\Vector.cpp src\Matrix.cpp src\LinearSystem.cpp test\TestLinearSystem.cpp -o test\TestLinearSystem.exe

        if %errorlevel% equ 0 (
            echo Running...
            test\TestLinearSystem.exe
        ) else (
            echo Compilation failed.
        )
        ```

#### Part B

- **CPU performance prediction**

    - Run this in your terminal at `TheTinyProject/test` *`./runLinearSystem.bat`*

        **`runLinearSystem.bat`**

        ```
        @echo off
        echo Compiling...
        g++ -Iinclude src\Vector.cpp src\Matrix.cpp src\LinearSystem.cpp src\PosSymLinSystem.cpp src\main.cpp -o test\main.exe

        if %errorlevel% equ 0 (
            echo Running...
            test\main.exe
        ) else (
            echo Compilation failed.
        )
        ```

### Expected Results

#### Part A

- **Vector**

    ```
    Compiling...
    Running...
    Test 1: PASSED
    Test 2: PASSED
    Test 3: PASSED
    Test 4: PASSED
    Test 5: PASSED
    Test 6: PASSED
    Test 7: PASSED
    Test 8: PASSED
    Test 9: PASSED
    Test 10: PASSED
    Test 11: PASSED
    Test 12: PASSED
    Test 13: PASSED
    Test 14: PASSED
    Test 15: PASSED
    Test 16: PASSED
    Test 17: PASSED
    Test 18: PASSED
    Test 19: PASSED
    Test 20: PASSED`
    ```

- **Matrix**

    ```
    Compiling...
    Running...
    Test 1: PASSED
    Test 2: PASSED
    Test 3: PASSED
    Test 4: PASSED
    Test 5: PASSED
    Test 6: PASSED
    Test 7: PASSED
    Test 8: PASSED
    Test 9: PASSED
    Test 10: PASSED
    Test 11: PASSED
    Test 12: PASSED
    Test 13: PASSED
    Test 14: PASSED
    Test 15: PASSED
    Test 16: PASSED
    Test 17: PASSED
    Test 18: PASSED
    Test 19: PASSED
    Test 20: PASSED`
    ```

- **Linear System**

    ```
    Compiling...
    Running...
    Test 1: PASSED
    Test 2: PASSED
    Test 3: PASSED
    Test 4: PASSED
    Test 5: PASSED
    Test 6: PASSED
    Test 7: PASSED
    Test 8: PASSED
    Test 9: PASSED
    Test 10: PASSED
    Test 11: PASSED
    Test 12: PASSED
    Test 13: PASSED
    Test 14: PASSED
    Test 15: PASSED
    Test 16: PASSED
    Test 17: PASSED
    Test 18: PASSED
    Test 19: PASSED
    Test 20: PASSED`
    ```

#### Part B

- **CPU performance prediction**

    ```
    Compiling...
    Running...
    Epoch 1: RMSE(new)=68.6661, RMSE(old)=170.075, chosen RMSE=68.6661
    Epoch 2: RMSE(new)=49.0501, RMSE(old)=46.6874, chosen RMSE=46.6874
    Epoch 3: RMSE(new)=70.6047, RMSE(old)=55.6425, chosen RMSE=55.6425
    Epoch 4: RMSE(new)=59.1485, RMSE(old)=49.7234, chosen RMSE=49.7234
    Epoch 5: RMSE(new)=51.0362, RMSE(old)=45.7375, chosen RMSE=45.7375
    Epoch 6: RMSE(new)=69.2015, RMSE(old)=67.2499, chosen RMSE=67.2499
    Epoch 7: RMSE(new)=62.8874, RMSE(old)=61.336, chosen RMSE=61.336
    Epoch 8: RMSE(new)=84.5208, RMSE(old)=61.1962, chosen RMSE=61.1962
    Epoch 9: RMSE(new)=90.8814, RMSE(old)=78.9153, chosen RMSE=78.9153
    Epoch 10: RMSE(new)=77.4125, RMSE(old)=73.7294, chosen RMSE=73.7294
    Epoch 11: RMSE(new)=81.2553, RMSE(old)=62.3176, chosen RMSE=62.3176
    Epoch 12: RMSE(new)=45.3672, RMSE(old)=43.007, chosen RMSE=43.007
    Epoch 13: RMSE(new)=67.3192, RMSE(old)=63.6839, chosen RMSE=63.6839
    Epoch 14: RMSE(new)=91.1538, RMSE(old)=63.3319, chosen RMSE=63.3319
    Epoch 15: RMSE(new)=69.9663, RMSE(old)=56.4522, chosen RMSE=56.4522
    Epoch 16: RMSE(new)=57.7508, RMSE(old)=50.6403, chosen RMSE=50.6403
    Epoch 17: RMSE(new)=68.0081, RMSE(old)=58.5714, chosen RMSE=58.5714
    Epoch 18: RMSE(new)=70.8213, RMSE(old)=55.9451, chosen RMSE=55.9451
    Epoch 19: RMSE(new)=104.847, RMSE(old)=92.9856, chosen RMSE=92.9856
    Epoch 20: RMSE(new)=63.5254, RMSE(old)=53.3509, chosen RMSE=53.3509
    ```

    **Notes:** Results may vary 

### Remarks

- This project was developed using **C++17** and compiled using **G++** on Windows. Portability was considered, but minor adjustments may be needed for Unix-like systems (e.g., file paths or batch scripts).
- While the core mathematical operations were implemented manually, external libraries (such as Eigen or Armadillo) were intentionally avoided to encourage understanding of foundational principles.
- The performance of the regression model in Part B could be improved through additional preprocessing (e.g., feature scaling or normalization), but such enhancements were beyond the project's scope.


## References
 * UCI Machine Learning Dataset: [*<ins>Computer Hardware Data</ins>*](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
 * Programming 2 Course Materials (VGU - CSE)

## Notes

- All test files and results are reproducible assuming the same data and environment; however, stochastic variations in RMSE may occur due to data shuffling.

- Memory management was handled manually—no smart pointers were used—providing a deeper understanding of heap allocation and destructor behavior.

- Proper assertion checks were added throughout the implementation to ensure stability and prevent silent runtime errors due to dimension mismatches.

- Code is modular and extensible, allowing easy integration with future numerical or machine learning projects.

## Conclusion

This project provided hands-on experience in implementing core numerical methods and data structures from scratch in C++. By developing ***Vector***, ***Matrix***, and ***LinearSystem*** classes, we deepened our understanding of memory management, operator overloading, and linear algebra algorithms like Gaussian elimination and the conjugate gradient method.

Furthermore, applying these methods to real-world data through linear regression showcased the power and relevance of these foundational techniques in practical machine learning scenarios.

The project not only reinforced our programming skills but also demonstrated the value of mathematical modeling and numerical computation in solving complex problems efficiently and accurately.
