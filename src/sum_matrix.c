#include "../include/s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = S21_SUCCESS;

#if 0  // possible to check everything for NULL
  if (A == NULL || B == NULL || result = NULL) res = S21_ERROR;
  if (A->matrix == NULL || B->matrix == NULL) res = S21_ERROR;
#endif

  // TODO(trelawnm): make reusable function from lines downstairs
  if (A->rows != B->rows || A->columns != B->columns) {
    res = S21_CALCERR;
  }

  if (!res && !(res = s21_create_matrix(A->rows, A->columns, result))) {
    for (int i = 0; i < A->rows * A->columns; ++i)
      result->matrix[0][i] = A->matrix[0][i] + B->matrix[0][i];
  }

  return res;
}