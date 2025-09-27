#include <float.h>
#include <math.h>

#include "../include/s21_matrix.h"

#define EPSILON 1e-6

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = S21_TRUE;

  if (A == B) {
    return res;
  }

  if (A->columns != B->columns || A->rows != B->rows) {
    res = S21_FALSE;
  }

  for (int i = 0; i < (A->columns * A->rows) && res; ++i) {
    if (fabs(A->matrix[0][i] - B->matrix[0][i]) > EPSILON) {
      res = S21_FALSE;
    }
  }

  return res;
}