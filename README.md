# BigInteger
This project provides a basic implementation of a BigInteger class in C++, allowing for arithmetic operations on arbitrarily large integers.

## Features

*   Arbitrary Precision Arithmetic: Handles integers larger than the built-in integer types.
*   Basic Arithmetic Operations: Supports addition, subtraction, multiplication, and division. (Implementation may vary based on completeness).
*   Comparison Operators: Supports comparison operations (>, <, ==, !=, >=, <=).
*   String Conversion: Can be constructed from and converted to strings.
*   Basic Validation: Includes checks to prevent invalid input.
*   Unit Tests: Contains a suite of unit tests to ensure correctness.
*   Static Analysis: Uses Clang-Tidy for static code analysis.
*   Memory Leak Detection: Uses Valgrind to detect memory leaks.

## Project Structure

```plaintext
BigInteger/
├── CMakeLists.txt         # CMake build configuration file
├── README.md              # This file
├── src/                    # Source code directory
│   └── biginteger.cpp       # Implementation of the BigInteger class
├── include/                # Header file directory
│   └── biginteger.hpp      # Header file for the BigInteger class
├── main.cpp                # Example usage of the BigInteger class
└── test.cpp                # Unit tests for the BigInteger class
```

## Prerequisites:

 *   CMake (version 3.14 or higher)
 *   A C++ compiler (GCC, Clang, or similar)
 *   (Optional) Valgrind for memory leak detection
