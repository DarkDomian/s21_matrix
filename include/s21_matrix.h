#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <stdlib.h>

/*======================================================
    ERRORS CODE
========================================================*/

#define S21_SUCCESS 0  // success code. realy good to be returned
#define S21_ERROR 1    // default error code or incorrect matrix
/**
 * @brief calculation error (musmatched matrix sizes; matrix for which
 * calculations cannot be performed, etc)
 */
#define S21_CALCERR 2

/*======================================================
    BOOL CODE ETC.
========================================================*/

#define S21_TRUE 1
#define S21_FALSE 0

#define S21_EPSILON 1e-6  // 10^-6

/*======================================================
    MATRIX ITSELF
========================================================*/

/**
 * @brief Structure to store a pointer to a matrix and its meta-data.
 *
 * This structure contains the matrix data and its dimensions.
 *
 * @param matrix Pointer to a 2D array representing the matrix.
 * @param rows Number of rows in the matrix.
 * @param columns Number of columns in the matrix.
 */
typedef struct matrix_struct {
  double **matrix; /**< Pointer to a 2D array representing the matrix. */
  int rows;        /**< Number of rows in the matrix. */
  int columns;     /**< Number of columns in the matrix. */
} matrix_t;

/*======================================================
    CORE OPERATIONS
========================================================*/

/**
 * @brief Initialize matrix and store pointer on it into `result`
 * @param rows Number of rows to initialize
 * @param columns Number of columns to initialize
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if matrix was initialized successfully, `S21_ERROR` if
 * any error occurred
 *
 * @note The function allocates memory for the matrix. Use s21_remove_matrix to
 * free the memory.
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief Clean matrix memory
 * @param A Pointer to matrix to remove
 *
 * @note This function frees all memory allocated for the matrix and sets
 * pointers to NULL.
 */
void s21_remove_matrix(matrix_t *A);

/**
 * @brief Compare two matrices for equality
 * @param A Pointer to first matrix
 * @param B Pointer to second matrix
 * @return `S21_TRUE` if matrices are equal, `S21_FALSE` if not
 *
 * @note Matrices are considered equal if they have the same dimensions and
 * corresponding elements are identical (compared up to 6 decimal places).
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/*======================================================
    ARITHMETIC OPERATIONS
========================================================*/

/**
 * @brief Add two matrices
 * @param A Pointer to first matrix
 * @param B Pointer to second matrix
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrices are
 * incorrect, `S21_CALCERR` if matrix sizes don't match for addition
 *
 * @note Performs element-wise addition: `result[i][j] = A[i][j] + B[i][j]`
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Subtract two matrices
 * @param A Pointer to first matrix
 * @param B Pointer to second matrix
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrices are
 * incorrect, `S21_CALCERR` if matrix sizes don't match for subtraction
 *
 * @note Performs element-wise subtraction: `result[i][j] = A[i][j] - B[i][j]`
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Multiply matrix by a scalar number
 * @param A Pointer to source matrix
 * @param number Scalar value to multiply by
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrix is
 * incorrect
 *
 * @note Performs scalar multiplication: `result[i][j] = A[i][j] * number`
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/**
 * @brief Multiply two matrices
 * @param A Pointer to first matrix
 * @param B Pointer to second matrix
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrices are
 * incorrect, `S21_CALCERR` if matrix dimensions are incompatible for
 * multiplication
 *
 * @note Number of columns in `A` must equal number of rows in `B`.
 * Result matrix dimensions will be: `rows = A->rows`, `columns = B->columns`
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/*======================================================
    LINEAR ALGEBRA OPERATIONS
========================================================*/

/**
 * @brief Transpose a matrix
 * @param A Pointer to source matrix
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrix is
 * incorrect
 *
 * @note Transpose operation swaps rows with columns: `result[i][j] = A[j][i]`
 */
int s21_transpose(matrix_t *A, matrix_t *result);

/**
 * @brief Calculate inverse of a matrix
 * @param A Pointer to source matrix
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrix is
 * incorrect, `S21_CALCERR` if matrix is not square or determinant is zero
 *
 * @note The source matrix must be square and have non-zero determinant.
 * Inverse is calculated as: `A^(-1) = (1/det(A)) * adjugate(A)^T`
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/**
 * @brief Calculate determinant of a matrix
 * @param A Pointer to source matrix
 * @param result Pointer to double where the determinant value will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrix is
 * incorrect, `S21_CALCERR` if matrix is not square
 *
 * @note The source matrix must be square. Uses recursive Laplace expansion.
 */
int s21_determinant(matrix_t *A, double *result);

/*======================================================
    AUXILIARY OPERATIONS
========================================================*/

/**
 * @brief Calculate matrix of algebraic complements (cofactor matrix)
 * @param A Pointer to source matrix
 * @param result Pointer to matrix structure where the result will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrix is
 * incorrect, `S21_CALCERR` if matrix is not square
 *
 * @note The source matrix must be square. Algebraic complement is calculated as
 * `C(i,j) = (-1)^(i+j) * M(i,j)`, where `M(i,j)` is the minor of element
 * `A[i][j]`
 */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/*======================================================
    HELPERS
========================================================*/

/**
 * @brief Check if two matrices have equal dimensions
 * @param A Pointer to first matrix
 * @param B Pointer to second matrix
 * @return `S21_TRUE` if matrices have same dimensions, `S21_FALSE` otherwise
 * @see Implementation can be found in `eq_matrix.c`
 *
 * @note Two matrices have equal dimensions if they have the same number of rows
 * and the same number of columns. This is a prerequisite for many matrix
 * operations like addition and subtraction.
 *
 * @see Implementation can be found in `eq_matrix.c`
 */
int _has_equal_demensions(matrix_t *A, matrix_t *B);

/**
 * @brief Extract a minor matrix by excluding specified row and column
 * @param A Pointer to source matrix
 * @param excluded_row Index of row to exclude (0-based)
 * @param excluded_col Index of column to exclude (0-based)
 * @param result Pointer to matrix structure where the minor will be stored
 * @return `S21_SUCCESS` if operation successful, `S21_ERROR` if matrix is
 * incorrect or indices are invalid, `S21_CALCERR` if matrix is too small
 *
 * @note The minor matrix is obtained by removing the specified row and column
 * from the original matrix. The resulting matrix has dimensions (n-1) x (m-1).
 * @note This is an internal helper function used for determinant calculation
 * and cofactor matrix computation.
 * @note The source matrix must be at least 2x2 to create a valid minor.
 * @note Indices must be within bounds: `0 <= excluded_row < rows` and
 * `0 <= excluded_col < columns`
 *
 * @see Used by `s21_determinant()` and `s21_calc_complements()`. Implementation
 * can be found in `determinant.c`
 */
int _get_minor(matrix_t *A, int excluded_row, int excluded_col,
               matrix_t *result);

/**
 * @return S21_TRUE if matrix is square and S21_FALSE otherwise
 */
int _matrix_is_square(matrix_t *A);

/**
 * @brief check does the matrix are good
 *
 * @see implemented in `create_matrix.c`
 */
int _is_valid_source(const matrix_t *A);

#endif  // S21_MATRIX_H