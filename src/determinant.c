#include "../include/s21_matrix.h"

int _matrix_is_square(matrix_t *A) {
  int res = S21_FALSE;
  if (A->columns == A->rows) res = S21_TRUE;
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = S21_SUCCESS;

  if (!_matrix_is_square(A)) res = S21_CALCERR;

  if (!res) {
    A->columns = 1;
  }
  if (!res) {
    *result = 0.0;
  }

  return res;
}