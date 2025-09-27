#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_finish_success_inverse) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_inverse_matrix(&A, &B), S21_SUCCESS);
  s21_remove_matrix(&A);
}
END_TEST

Suite* test_inverse_matrix(void) {
  Suite* ps = suite_create("inverse");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_finish_success_inverse);

  suite_add_tcase(ps, tc);
  return ps;
}