#include "../include/s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = S21_SUCCESS;

  if (!res) {
    result->rows = A->rows * B->columns;
    result->columns = A->columns * B->rows;
  }

  return res;
}