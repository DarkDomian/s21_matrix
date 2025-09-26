#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_create_matrix_valid) {
  matrix_t A = {.columns = 0, .rows = 0, .matrix = NULL};
  ck_assert_int_eq(s21_create_matrix(7, 10, &A), S21_SUCCESS);
  ck_assert_int_eq(A.rows, 7);
  ck_assert_int_eq(A.columns, 10);
  ck_assert_ptr_nonnull(A.matrix);
  free(A.matrix);
}
END_TEST

START_TEST(test_wrong_data) {
  matrix_t A = {.columns = 0, .rows = 0, .matrix = NULL};

  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), S21_ERROR);
  ck_assert_int_eq(s21_create_matrix(3, 0, &A), S21_ERROR);
  ck_assert_int_eq(s21_create_matrix(-100, 3, &A), S21_ERROR);
}
END_TEST

START_TEST(test_matrix_structure_valid) {
  matrix_t A = {.columns = 0, .rows = 0, .matrix = NULL};
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), S21_SUCCESS);

  for (int i = 0; i < A.rows; i++) {
    ck_assert_ptr_nonnull(A.matrix[i]);
  }

  free(A.matrix);
}
END_TEST

START_TEST(test_matrix_data_integrity) {
  matrix_t A = {.columns = 0, .rows = 0, .matrix = NULL};
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), S21_SUCCESS);

  // verify matrix can be filled with data
  double test_value = 1.5;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = test_value + i * A.columns + j;
    }
  }

  // verify data was correctly stored and can be retrieved
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      double expected = test_value + i * A.columns + j;
      ck_assert_double_eq(A.matrix[i][j], expected);
    }
  }

  // Test 6: Verify data persistence (write/read consistency)
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] *= 2.0;
    }
  }

  // check values was changed correctly
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      double expected = (test_value + i * A.columns + j) * 2.0;
      ck_assert_double_eq(A.matrix[i][j], expected);
    }
  }

  free(A.matrix);
}
END_TEST
Suite* test_create_matrix(void) {
  Suite* ps = suite_create("create");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_create_matrix_valid);
  tcase_add_test(tc, test_wrong_data);
  tcase_add_test(tc, test_matrix_structure_valid);
  tcase_add_test(tc, test_matrix_data_integrity);

  suite_add_tcase(ps, tc);
  return ps;
}