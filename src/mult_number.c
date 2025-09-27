#include "../include/s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = S21_SUCCESS;

  if (!res) {
    result->rows = A->rows * number;
    result->columns = A->columns * number;
  }

  return res;
}