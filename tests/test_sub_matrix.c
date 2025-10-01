#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_sub_handle_wrong_data) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), S21_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_different_matrix) {
  matrix_t A = {.rows = 4, .columns = 5, .matrix = NULL};
  matrix_t B = {.rows = 4, .columns = 6, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), S21_CALCERR);

  B.columns = 6;
  A.rows = 3;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), S21_CALCERR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}

START_TEST(test_sum_easy_numbers) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  double digit_a[9] = {1, 2, 3, 0, 4, 5, 0, 0, 6};
  double digit_b[9] = {1, 0, 0, 2, 0, 0, 3, 4, 1};
  double expected_c[9] = {0, 2, 3, -2, 4, 5, -3, -4, 5};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ptr_digit = digit_b;
  for (int i = 0; i < A.rows * A.columns; ++i) B.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), S21_SUCCESS);

  ptr_digit = expected_c;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_sum_hard_numbers) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);

  double digit_a[9] = {12.345678, -5.987654, 0.001234,
                       99.999999, -8.450000, 15.123456};
  double digit_b[9] = {-2.109876, 77.777777, -0.000001,
                       99.999999, -8.450000, -9.876543};
  double expected_c[9] = {14.455554, -83.765431, 0.001235, 0, 0, 24.999999};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ptr_digit = digit_b;
  for (int i = 0; i < A.rows * A.columns; ++i) B.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), S21_SUCCESS);

  ptr_digit = expected_c;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

Suite* test_sub_matrix(void) {
  Suite* ps = suite_create("sub");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_sub_handle_wrong_data);
  tcase_add_test(tc, test_sum_different_matrix);
  tcase_add_test(tc, test_sum_easy_numbers);
  tcase_add_test(tc, test_sum_hard_numbers);

  suite_add_tcase(ps, tc);
  return ps;
}