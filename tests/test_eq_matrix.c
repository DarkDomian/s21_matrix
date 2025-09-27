#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_finish_success_equal) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_eq_matrix(&A, &A), S21_TRUE);
  s21_remove_matrix(&A);
}
END_TEST

Suite* test_eq_matrix(void) {
  Suite* ps = suite_create("equal");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_finish_success_equal);

  suite_add_tcase(ps, tc);
  return ps;
}