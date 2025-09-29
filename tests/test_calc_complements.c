#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_calc_complements_v1) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B;
  s21_create_matrix(3, 3, &A);

  double digit_a[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double expected[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_calc_complements(&A, &B), S21_SUCCESS);

  ptr_digit = expected;
  for (int i = 0; i < B.rows * B.columns; ++i)
    ck_assert_double_eq_tol(B.matrix[0][i], *ptr_digit++, S21_EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite* test_calc_complements(void) {
  Suite* ps = suite_create("complements");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_calc_complements_v1);

  suite_add_tcase(ps, tc);
  return ps;
}