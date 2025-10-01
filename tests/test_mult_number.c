#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_scalar_mult_handle_wrong_data) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_mult_number(&A, 1.1, &C), S21_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_easy_numbers) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 3, &A);

  double number = 0.1;

  double digit_a[9] = {1, 2, 3, 0, 4, 5, -7, 1.1, 0.000005};
  double expected_c[9] = {0};
  for (int i = 0; i < 9; ++i) {
    expected_c[i] = digit_a[i] * number;
  }

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_mult_number(&A, number, &C), S21_SUCCESS);

  ptr_digit = expected_c;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_by_zero) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 2, &A);

  double digit_a[9] = {10.235802,  71.790123,  0.001233,
                       199.999998, -16.900000, 5.246913};

  const double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_mult_number(&A, 0, &C), S21_SUCCESS);

  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], 0.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_mult_hard_numbers) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 2, &A);

  // FIRST
  double digit_a[9] = {12.345678, -5.987654, 0.001234,
                       99.999999, -8.450000, 15.123456};
  double expected[9] = {0};
  for (int i = 0; i < 9; ++i) {
    expected[i] = digit_a[i] * 0.001234;
  }

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_mult_number(&A, 0.001234, &C), S21_SUCCESS);
  ptr_digit = expected;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&C);
  // SECOND
  double digit_b[9] = {-2.109876, 77.777777, -0.000001,
                       99.999999, -8.450000, -9.876543};
  for (int i = 0; i < 9; ++i) {
    expected[i] = digit_b[i] * 48.775511;
  }

  ptr_digit = digit_b;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_mult_number(&A, 48.775511, &C), S21_SUCCESS);
  ptr_digit = expected;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&C);
  // THIRD
  double digit_c[9] = {10.235802,  71.790123,  0.001233,
                       199.999998, -16.900000, 5.246913};
  for (int i = 0; i < 9; ++i) {
    expected[i] = digit_c[i] * -100.010001;
  }

  ptr_digit = digit_c;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_mult_number(&A, -100.010001, &C), S21_SUCCESS);
  ptr_digit = expected;
  for (int i = 0; i < A.rows * A.columns; ++i)
    ck_assert_double_eq_tol(C.matrix[0][i], *ptr_digit++, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

Suite* test_mult_number(void) {
  Suite* ps = suite_create("mult_number");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_scalar_mult_handle_wrong_data);
  tcase_add_test(tc, test_mult_easy_numbers);
  tcase_add_test(tc, test_mult_by_zero);
  tcase_add_test(tc, test_mult_hard_numbers);

  suite_add_tcase(ps, tc);
  return ps;
}