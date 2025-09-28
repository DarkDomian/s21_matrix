#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_same_pointer) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};

  ck_assert_int_eq(s21_eq_matrix(&A, &A), S21_TRUE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_different_dimensions) {
  matrix_t A = {.rows = 4, .columns = 5, .matrix = NULL};
  matrix_t B = {.rows = 4, .columns = 6, .matrix = NULL};

  ck_assert_int_eq(s21_eq_matrix(&A, &B), S21_FALSE);

  B.columns = 6;
  A.rows = 3;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), S21_FALSE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_equal_matrix) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  double num = 1.000001;
  for (int i = 0; i < A.columns * A.rows; ++i) {
    A.matrix[0][i] = num * i;
    B.matrix[0][i] = num * i;
  }

  ck_assert_int_eq(s21_eq_matrix(&A, &B), S21_TRUE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_different_matrix) {
  matrix_t A = {.rows = 0, .columns = 0, .matrix = NULL};
  matrix_t B = {.rows = 0, .columns = 0, .matrix = NULL};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  double num = 1.000001;
  for (int i = 0; i < A.columns * A.rows; ++i) {
    A.matrix[0][i] = num * i;
    B.matrix[0][i] = num * i;
  }
  B.matrix[2][2] = 9.000008;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), S21_FALSE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite* test_eq_matrix(void) {
  Suite* ps = suite_create("equal");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_different_dimensions);
  tcase_add_test(tc, test_same_pointer);
  tcase_add_test(tc, test_equal_matrix);
  tcase_add_test(tc, test_different_matrix);

  suite_add_tcase(ps, tc);
  return ps;
}