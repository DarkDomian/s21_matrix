#include "../include/s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = S21_SUCCESS;

  double det = 0;
  res = s21_determinant(A, &det);
  if (!res && !det) res = S21_CALCERR;

  if (!res) {
    matrix_t T;

    s21_calc_complements(A, result);

    s21_transpose(result, &T);

    s21_remove_matrix(result);

    s21_mult_number(&T, 1 / det, result);

    s21_remove_matrix(&T);
  }

  return res;
}