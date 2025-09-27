#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_finish_success_compl) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_calc_complements(&A, &B), S21_SUCCESS);
}
END_TEST

Suite* test_calc_complements(void) {
  Suite* ps = suite_create("complements");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_finish_success_compl);

  suite_add_tcase(ps, tc);
  return ps;
}