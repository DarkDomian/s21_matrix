#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_finish_success_determ) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  s21_create_matrix(3, 3, &A);
  for (int i = 1; i < 10; ++i) A.matrix[0][i - 1] = (double)i;
  double determ = 1.0;

  ck_assert_int_eq(s21_determinant(&A, &determ), S21_SUCCESS);
  ck_assert_double_eq(determ, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

Suite* test_determinant(void) {
  Suite* ps = suite_create("determinant");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_finish_success_determ);

  suite_add_tcase(ps, tc);
  return ps;
}