#include "../include/s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = S21_SUCCESS;

  if (!_is_valid_source(A) || !_is_valid_source(B)) res = S21_ERROR;
  if (!_has_equal_demensions(A, B)) res = S21_CALCERR;

  if (!res && !(res = s21_create_matrix(A->rows, A->columns, result))) {
    for (int i = 0; i < A->rows * A->columns; ++i)
      result->matrix[0][i] = A->matrix[0][i] - B->matrix[0][i];
  }
  return res;
}