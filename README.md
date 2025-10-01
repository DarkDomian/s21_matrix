# <span><a href="https://21-school.ru/?utm_source=school21&utm_medium=student_nino&utm_campaign=trelawnm___"><img style="height: 1em;" src="misc/heart.gif"></a></span> The 21 School project - `Matrix Library`

A C library for matrix operations including basic arithmetic, linear algebra functions, and matrix manipulations.

![decimal](misc/s21_matrix.png)

## Features

- **Basic Operations**: Create, remove, and compare matrices
- **Arithmetic**: Addition, subtraction, scalar and matrix multiplication
- **Linear Algebra**: Determinant, transpose, inverse, cofactor matrix
- **Error Handling**: Comprehensive error codes for robust operation

## Quick Start

### Dependencies

Install required tools on Ubuntu:
```bash
sudo apt-get install clang-format cppcheck valgrind lcov pkg-config check
```

### Available Make Targets

- `all` - Execute *style_check* and *gcov_report*
- `clean` - Remove all build artifacts
- `test` - Run test suite under Valgrind
- `s21_matrix.a` - Build only the static library
- `gcov_report` - Generate code coverage report
- `style_check` - Check code style compliance and static code analysis

### Usage Example

```c
#include "s21_matrix.h"

int main() {
    matrix_t A, B, result;
    
    // Create two 2x2 matrices
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    
    // Initialize matrix values
    A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0;
    A.matrix[1][0] = 3.0; A.matrix[1][1] = 4.0;
    
    B.matrix[0][0] = 5.0; B.matrix[0][1] = 6.0;
    B.matrix[1][0] = 7.0; B.matrix[1][1] = 8.0;
    
    // Add matrices
    s21_sum_matrix(&A, &B, &result);
    
    // Clean up
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    
    return 0;
}
```

## Project Structure

```
├── src/           # Source implementation
├── include/       # Header files
├── tests/         # Test suites
├── build/         # Build output
└── coverage/      # Coverage reports
```

## Error Codes

- `S21_SUCCESS` (0) - Operation successful
- `S21_ERROR` (1) - General error or invalid matrix
- `S21_CALCERR` (2) - Calculation error (size mismatch, etc.)

## License

This project is part of the 21 School curriculum.
