#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_finish_success_mult_n) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t C = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), S21_SUCCESS);
  s21_remove_matrix(&A);
}
END_TEST

Suite* test_sum_matrix(void) {
  Suite* ps = suite_create("sum");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_finish_success_mult_n);

  suite_add_tcase(ps, tc);
  return ps;
}