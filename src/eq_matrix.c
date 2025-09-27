#include "../include/s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = S21_TRUE;

  if (!res) {
    A->columns = B->columns;
    A->rows = B->rows;
  }

  return res;
}