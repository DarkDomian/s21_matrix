#include "../include/s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int res = S21_SUCCESS;

  if (!res) {
    A->columns = 1;
  }
  if (!res) {
    *result = 0.0;
  }

  return res;
}