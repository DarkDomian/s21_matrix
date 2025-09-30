#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_transpose_is_flip) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 1, &A);
  double digit_a[3] = {1, 4, 2};

  const double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_transpose(&A, &B), S21_SUCCESS);

  ck_assert_int_eq(B.rows, A.columns);
  ck_assert_int_eq(B.columns, A.rows);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose_right_data) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 2, &A);

  double digit_a[9] = {1, 4, 2, 5, 3, 6};
  double expected[9] = {1, 2, 3, 4, 5, 6};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_transpose(&A, &B), S21_SUCCESS);

  ptr_digit = expected;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(B.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite* test_transpose(void) {
  Suite* ps = suite_create("transpose");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_transpose_is_flip);
  tcase_add_test(tc, test_transpose_right_data);

  suite_add_tcase(ps, tc);
  return ps;
}