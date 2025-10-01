#include "../include/s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = S21_SUCCESS;

  if (!_is_valid_source(A)) res = S21_ERROR;

  if (!res && !(res = s21_create_matrix(A->rows, A->columns, result))) {
    for (int i = 0; i < A->rows * A->columns; ++i)
      result->matrix[0][i] = A->matrix[0][i] * number;
  }

  return res;
}