#include "../include/s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = S21_SUCCESS;

  if (A->columns != B->rows) res = S21_CALCERR;

  // C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + ... + A(i,k) × B(k,j)
  if (!res && !(res = s21_create_matrix(A->rows, B->columns, result))) {
    for (int i = 0; i < result->rows; ++i)
      for (int j = 0; j < result->columns; ++j)
        for (int k = 0; k < A->columns; ++k)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
  }

  return res;
}