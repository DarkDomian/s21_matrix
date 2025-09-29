#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_inverse_from_readme) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B;
  s21_create_matrix(3, 3, &A);

  double digit_a[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double expected[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), S21_SUCCESS);

  ptr_digit = expected;
  for (int i = 0; i < B.rows * B.columns; ++i)
    ck_assert_double_eq_tol(B.matrix[0][i], *ptr_digit++, S21_EPSILON);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_inverse_zero_determ) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B;
  s21_create_matrix(2, 2, &A);

  double digit_a[9] = {2, -7, -2, 7};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), S21_CALCERR);

  s21_remove_matrix(&A);
}
END_TEST

Suite* test_inverse_matrix(void) {
  Suite* ps = suite_create("inverse");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_inverse_from_readme);
  tcase_add_test(tc, test_inverse_zero_determ);

  suite_add_tcase(ps, tc);
  return ps;
}