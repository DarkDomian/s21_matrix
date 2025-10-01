#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_inverse_handle_wrong_data) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), S21_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

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

  const double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), S21_CALCERR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_6_x_6) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B;
  s21_create_matrix(6, 6, &A);

  double digit_a[] = {1.57,   2.0,   3.79,  4.0,   5.0,    6.23,   7.0,    8.15,
                      9.0,    10.37, 11.0,  12.0,  13.0,   14.0,   15.584, 16.0,
                      17.83,  18.0,  19.26, 20.0,  21.0,   22.491, 23.0,   24.0,
                      25.0,   26.72, 27.0,  28.0,  29.956, 30.0,   31.0,   32.0,
                      33.138, 34.0,  35.0,  36.671};

  double expected[] = {
      2.752607462063702,   -2.9999723372105445, -2.3530870608340417,
      2.70838419714177,    1.9056234801110243,  -1.6624426517370892,
      -1.362878143302364,  1.9849740538420746,  0.49905261882935054,
      -2.1083634376589915, -0.3907566866413481, 1.036555265763049,
      -2.634325426502395,  1.9708465545880351,  3.1158250011164563,
      -2.369504804497918,  -2.572392624040364,  1.9284102631812126,
      -1.6278187130490545, 1.2347790019265106,  1.0989456676730849,
      0.16075434552918189, -1.2925800970833543, 0.285300078014295,
      1.3172207258197484,  -1.6391872016256288, -0.7409856171264773,
      1.3818773968447087,  1.4027058573030429,  -1.375597361332857,
      1.494932128524281,   -0.5574125168106171, -1.5736099344206387,
      0.22352849574835354, 0.914260619011167,   -0.16612583806557946};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), S21_SUCCESS);

  ptr_digit = expected;
  for (int i = 0; i < B.rows * B.columns; ++i) {
    double abs = fabs(B.matrix[0][i] - *ptr_digit++);
    ck_assert_msg(abs < S21_EPSILON,
                  "Expected: %.10f, Actual: %.10f, Diff: %.10Lf\n",
                  *(--ptr_digit), B.matrix[0][i], fabsl(abs));
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite* test_inverse_matrix(void) {
  Suite* ps = suite_create("inverse");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_inverse_handle_wrong_data);
  tcase_add_test(tc, test_inverse_from_readme);
  tcase_add_test(tc, test_inverse_zero_determ);
  tcase_add_test(tc, test_inverse_6_x_6);

  suite_add_tcase(ps, tc);
  return ps;
}