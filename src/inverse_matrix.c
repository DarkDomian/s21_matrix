#include "../include/s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = S21_SUCCESS;

  if (!_is_valid_source(A)) return S21_ERROR;

  double det = 0;
  res = s21_determinant(A, &det);
  if (!res && !det) res = S21_CALCERR;

  matrix_t T;
  if (!res) res = s21_calc_complements(A, result);

  if (!res) {
    res = s21_transpose(result, &T);
    s21_remove_matrix(result);
  }

  if (!res) {
    res = s21_mult_number(&T, 1 / det, result);
    s21_remove_matrix(&T);
  }

  return res;
}