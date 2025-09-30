#include "../include/s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = S21_SUCCESS;

  if (!_is_valid_source(A)) return S21_ERROR;

  if (!(res = s21_create_matrix(A->rows, A->rows, result))) {
    for (int i = 0; i < A->rows && !res; ++i)
      for (int j = 0; j < A->columns && !res; ++j) {
        matrix_t minor;
        res = _get_minor(A, i, j, &minor);
        double det = 0;
        if (!res) res = s21_determinant(&minor, &det);
        result->matrix[i][j] = det;
        s21_remove_matrix(&minor);
      }
  }

  for (int i = 0; i < result->rows && !res; ++i)
    for (int j = 0; j < result->columns && !res; ++j)
      result->matrix[i][j] *= ((i + j) % 2) ? -1.0 : 1.0;

  return res;
}