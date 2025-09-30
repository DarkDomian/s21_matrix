#include "../include/s21_matrix.h"

int _is_valid_source(const matrix_t* A) {
  return (A && A->matrix && A->rows > 0 && A->columns > 0);
}

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int res = S21_SUCCESS;

  if (rows <= 0 || columns <= 0 || result == NULL) return S21_ERROR;

  result->matrix =
      malloc((rows * columns * sizeof(double)) + (rows * sizeof(double*)));

  if (result->matrix) {
    result->columns = columns;
    result->rows = rows;

    double* ptr = (double*)(result->matrix + rows);
    for (int i = 0; i < rows; ++i) {
      result->matrix[i] = ptr + columns * i;
    }

    for (int i = 0; i < rows * columns; ++i) result->matrix[0][i] = 0;

  } else {
    res = S21_ERROR;
  }

  return res;
}