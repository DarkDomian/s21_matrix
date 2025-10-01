#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_determ_handle_wrong_data) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  double det = 0;

  ck_assert_int_eq(s21_determinant(&A, &det), S21_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_wrong_dimensions) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(10, 11, &A);
  double determ = 0;

  ck_assert_int_eq(s21_determinant(&A, &determ), S21_CALCERR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_matrix_1_x_1_base_case) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 99;

  double determ = 0;

  ck_assert_int_eq(s21_determinant(&A, &determ), S21_SUCCESS);
  ck_assert_double_eq_tol(determ, 99.0, S21_EPSILON);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_matrix_2_x_2_base_case) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = -6;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;

  double determ = 0;

  ck_assert_int_eq(s21_determinant(&A, &determ), S21_SUCCESS);
  ck_assert_double_eq_tol(determ, 18.0, S21_EPSILON);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_matrix_3_x_3) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(3, 3, &A);

  double digit_a[9] = {6, -1, 7, 10, 5, 3, 4, -8, 9};

  const double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  double determ = 0;

  ck_assert_int_eq(s21_determinant(&A, &determ), S21_SUCCESS);
  ck_assert_double_eq_tol(determ, -208, S21_EPSILON);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_matrix_4_x_4) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(4, 4, &A);

  // |A| = -35.4866
  double digits_a[] = {2.5,  -1.3, 0.8, 3.1,  0.7, 1.9,  -2.4, 0.5,
                       -1.2, 3.1,  1.6, -0.9, 2.8, -0.4, 1.1,  2.3};

  const double* ptr_digit = digits_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  double determinant = 0.0;

  ck_assert_int_eq(s21_determinant(&A, &determinant), S21_SUCCESS);
  ck_assert_double_eq_tol(determinant, -35.4866, S21_EPSILON);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_matrix_5_x_5) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(5, 5, &A);

  // |A| = -8.76296
  double digits_a[] = {1.2, -2.7, 3.1, 0.8, -1.5, 2.4, 0.9, -1.3, 2.7,
                       0.6, -0.8, 1.6, 2.2, -1.9, 3.1, 1.7, -2.1, 0.5,
                       1.8, -1.7, 0.3, 2.8, -1.4, 0.9, 2.5};

  const double* ptr_digit = digits_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  double determinant = 0.0;

  ck_assert_int_eq(s21_determinant(&A, &determinant), S21_SUCCESS);
  ck_assert_double_eq_tol(determinant, -8.76296, S21_EPSILON);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determ_matrix_6_x_6) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(6, 6, &A);

  double digit_a[] = {1.57,   2.0,   3.79,  4.0,   5.0,    6.23,   7.0,    8.15,
                      9.0,    10.37, 11.0,  12.0,  13.0,   14.0,   15.584, 16.0,
                      17.83,  18.0,  19.26, 20.0,  21.0,   22.491, 23.0,   24.0,
                      25.0,   26.72, 27.0,  28.0,  29.956, 30.0,   31.0,   32.0,
                      33.138, 34.0,  35.0,  36.671};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  double det = 0, exp_det = -23.715264820856447;

  ck_assert_int_eq(s21_determinant(&A, &det), S21_SUCCESS);

  double abs = fabs(det - exp_det);
  ck_assert_msg(abs < S21_EPSILON,
                "Expected: %.10f, Actual: %.10f, Diff: %.10Lf\n", exp_det, det,
                fabsl(abs));

  s21_remove_matrix(&A);
}
END_TEST

Suite* test_determinant(void) {
  Suite* ps = suite_create("determinant");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_determ_handle_wrong_data);
  tcase_add_test(tc, test_determ_wrong_dimensions);
  tcase_add_test(tc, test_determ_matrix_1_x_1_base_case);
  tcase_add_test(tc, test_determ_matrix_2_x_2_base_case);
  tcase_add_test(tc, test_determ_matrix_3_x_3);
  tcase_add_test(tc, test_determ_matrix_4_x_4);
  tcase_add_test(tc, test_determ_matrix_5_x_5);
  tcase_add_test(tc, test_determ_matrix_6_x_6);

  suite_add_tcase(ps, tc);
  return ps;
}