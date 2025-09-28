#include <float.h>
#include <math.h>

#include "../include/s21_matrix.h"

#define EPSILON 1e-6

int _has_equal_demensions(matrix_t *A, matrix_t *B) {
  int res = S21_TRUE;
  if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res = S21_FALSE;
  }
  return res;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = S21_TRUE;

  if (A == B) {
    return res;
  }

  if (!_has_equal_demensions(A, B)) res = S21_FALSE;

  for (int i = 0; i < (A->columns * A->rows) && res; ++i) {
    if (fabs(A->matrix[0][i] - B->matrix[0][i]) > EPSILON) {
      res = S21_FALSE;
    }
  }

  return res;
}