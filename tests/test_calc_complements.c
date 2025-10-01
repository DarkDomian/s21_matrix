#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_cofactor_handle_wrong_data) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_calc_complements(&A, &B), S21_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

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

START_TEST(test_calc_complements_v2) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B;
  s21_create_matrix(6, 6, &A);

  double digit_a[] = {1.57,   2.0,   3.79,  4.0,   5.0,    6.23,   7.0,    8.15,
                      9.0,    10.37, 11.0,  12.0,  13.0,   14.0,   15.584, 16.0,
                      17.83,  18.0,  19.26, 20.0,  21.0,   22.491, 23.0,   24.0,
                      25.0,   26.72, 27.0,  28.0,  29.956, 30.0,   31.0,   32.0,
                      33.138, 34.0,  35.0,  36.671};

  double expected[] = {
      -65.27881491070625,  32.32101608697266,   62.47372511381992,
      38.60415186030401,   -31.238238340336025, -35.45271131715993,
      71.14513843219159,   -47.07418534939398,  -46.73914796332735,
      -29.28311102591974,  38.873758577510266,  13.219185450623906,
      55.804082794209975,  -11.835165015079998, -73.89261503692192,
      -26.061787532599926, 17.572670138600017,  37.31857631951607,
      -64.23004847183968,  50.000397262694456,  56.193433932959564,
      -3.812331875328372,  -32.771588416127905, -5.301037471679884,
      -45.19236547967493,  9.266898304220003,   61.004972302334906,
      30.653879304499963,  -33.26554087170807,  -21.681932695130005,
      39.42526773543183,   -24.582182629024032, -45.73276007459979,
      -6.765966903519821,  32.62265571088002,   3.939718243311926};

  double* ptr_digit = digit_a;
  for (int i = 0; i < A.rows * A.columns; ++i) A.matrix[0][i] = *ptr_digit++;

  ck_assert_int_eq(s21_calc_complements(&A, &B), S21_SUCCESS);

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

START_TEST(test_calc_complements_wrong_dimensions) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(5, 4, &A);

  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_CALCERR);

  s21_remove_matrix(&A);
}

Suite* test_calc_complements(void) {
  Suite* ps = suite_create("complements");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_cofactor_handle_wrong_data);
  tcase_add_test(tc, test_calc_complements_wrong_dimensions);
  tcase_add_test(tc, test_calc_complements_v1);
  tcase_add_test(tc, test_calc_complements_v2);

  suite_add_tcase(ps, tc);
  return ps;
}