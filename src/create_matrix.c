#include "../include/s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int res = S21_SUCCESS;

  if (rows <= 0 || columns <= 0 || result == NULL) {
    res = S21_ERROR;
  }

  if (!res) {
    result->matrix =
        malloc((rows * columns * sizeof(double)) + (rows * sizeof(double*)));

    if (result->matrix == NULL) {
      res = S21_ERROR;
    }
  }

  if (!res) {
    result->columns = columns;
    result->rows = rows;

    /*
     * point each matrix row to its corresponding column block in contiguous
     * memory
     */
    double* ptr = (double*)(result->matrix + rows);
    for (int i = 0; i < rows; ++i) {
      result->matrix[i] = ptr + columns * i;
    }

    // initialize memory to zeros
    for (int i = 0; i < rows * columns; ++i) result->matrix[0][i] = 0;

#if 0
    for (int i = 0; i < rows; ++i)
      result->matrix[i] = (double*)result->matrix[rows] + columns * i;
#endif
  }

  return res;
}