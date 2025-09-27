#include "../include/s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = S21_SUCCESS;

  if (!res) {
    result->rows = A->rows;
    result->columns = A->columns;
  }

  return res;
}