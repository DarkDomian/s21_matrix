#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_finish_success_mult_n) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  double number = 1.0;
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_mult_number(&A, number, &B), S21_SUCCESS);
  s21_remove_matrix(&A);
}
END_TEST

Suite* test_mult_number(void) {
  Suite* ps = suite_create("mult_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_finish_success_mult_n);

  suite_add_tcase(ps, tc);
  return ps;
}