#include "../include/s21_matrix.h"

int _matrix_is_square(matrix_t *A) {
  if (!_is_valid_source(A)) return S21_FALSE;
  return (A->columns == A->rows ? S21_TRUE : S21_FALSE);
}

int _get_minor(matrix_t *A, int excluded_row, int excluded_col,
               matrix_t *result) {
  if (!_is_valid_source(A)) return S21_ERROR;

  int res = s21_create_matrix(A->rows - 1, A->columns - 1, result);

  int minor_i = 0, minor_j = 0;
  for (int i = 0; i < A->rows && !res; ++i) {
    if (i == excluded_row) continue;
    for (int j = 0; j < A->columns && !res; ++j) {
      if (j == excluded_col) continue;

      result->matrix[minor_i][minor_j++] = A->matrix[i][j];
    }
    minor_j = 0;
    ++minor_i;
  }

  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = S21_SUCCESS;

  if (!_is_valid_source(A)) res = S21_ERROR;
  if (!_matrix_is_square(A)) res = S21_CALCERR;

  if (!res) {
    switch (A->columns) {
      case 1:
        *result = A->matrix[0][0];
        break;
      case 2:
        *result = (A->matrix[0][0] * A->matrix[1][1]) -
                  (A->matrix[1][0] * A->matrix[0][1]);
        break;
      default:
        *result = 0;
        for (int i = 0; i < A->rows; ++i) {
          matrix_t T;
          _get_minor(A, 0, i, &T);
          double minor_det = 0;
          s21_determinant(&T, &minor_det);
          int sign = (i % 2) ? -1 : 1;
          *result += sign * A->matrix[0][i] * minor_det;
          s21_remove_matrix(&T);
        }
    }
  }

#if 0
  if (!res && A->columns == 1) {
    *result += A->matrix[0][0];
    return S21_SUCCESS;
  }

  if (!res && A->columns == 2) {
    *result += (A->matrix[0][0] * A->matrix[1][1]) -
               (A->matrix[1][0] * A->matrix[0][1]);
    return S21_SUCCESS;
  }

  *result = 0;

  for (int i = 0; i < A->rows && !res; ++i) {
    matrix_t T;
    _get_minor(A, 0, i, &T);
    double minor_det = 0;
    s21_determinant(&T, &minor_det);
    int sign = (i % 2) ? -1.0 : 1.0;
    *result += sign * (A->matrix[0][i] * minor_det);
    s21_remove_matrix(&T);
  }
#endif

  return res;
}