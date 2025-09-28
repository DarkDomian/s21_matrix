#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_determ_base_case) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = -6;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;

  double determ = 0;

  ck_assert_int_eq(s21_determinant(&A, &determ), S21_SUCCESS);
  ck_assert_double_eq(determ, 18.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_matrix_3_x_3) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(3, 3, &A);

  double digit_a[9] = {6, -1, 7, 10, 5, 3, 4, -8, 9};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  double determ = 0;

  ck_assert_int_eq(s21_determinant(&A, &determ), S21_SUCCESS);
  ck_assert_double_eq(determ, -208);
  s21_remove_matrix(&A);
}
END_TEST

Suite* test_determinant(void) {
  Suite* ps = suite_create("determinant");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_determ_base_case);
  tcase_add_test(tc, test_determ_matrix_3_x_3);

  suite_add_tcase(ps, tc);
  return ps;
}