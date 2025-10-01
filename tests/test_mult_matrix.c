#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_mult_matrix_handle_wrong_data) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), S21_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_wrong_dimensions_mult_m) {
  matrix_t A = {.rows = 3, .columns = 3, .matrix = NULL};
  matrix_t B = {.rows = 4, .columns = 3, .matrix = NULL};
  matrix_t C;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(4, 3, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), S21_CALCERR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_expend_to_zero_mult_m) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  double digit_a[4] = {2, -3, 4, -6};
  double digit_b[4] = {9, -6, 6, -4};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ptr_digit = digit_b;
  for (int i = 0; i < B.rows * B.columns; ++i) B.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), S21_SUCCESS);

  for (int i = 0; i < C.rows * C.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], 0, 1e-6);

  // same data, switch the part of multiplication
  s21_remove_matrix(&C);
  ck_assert_int_eq(s21_mult_matrix(&B, &A, &C), S21_SUCCESS);

  double expected[4] = {-6, 9, -4, 6};
  ptr_digit = expected;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_different_dimension_mult_m) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 1, &B);

  double digit_a[9] = {5, 8, -4, 6, 9, -5, 4, 7, -3};
  double digit_b[3] = {2, -3, 1};
  double expected[3] = {-18, -20, -16};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ptr_digit = digit_b;
  for (int i = 0; i < B.rows * B.columns; ++i) B.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), S21_SUCCESS);

  ptr_digit = expected;
  for (int i = 0; i < C.rows * C.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

Suite* test_mult_matrix(void) {
  Suite* ps = suite_create("mult_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_mult_matrix_handle_wrong_data);
  tcase_add_test(tc, test_wrong_dimensions_mult_m);
  tcase_add_test(tc, test_expend_to_zero_mult_m);
  tcase_add_test(tc, test_different_dimension_mult_m);

  suite_add_tcase(ps, tc);
  return ps;
}