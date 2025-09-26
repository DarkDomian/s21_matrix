#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

START_TEST(test_is_null_returned) {
  matrix_t A;

  // initialize matrix by ourself
  A.columns = A.rows = 3;
  A.matrix =
      (double**)malloc((A.columns * A.rows + A.columns) * sizeof(double));

  ck_assert_msg(A.matrix != NULL,
                "malloc() didn't allocate memory. Can't proceed with test.");
  if (A.matrix) {
    ck_assert_ptr_nonnull(A.matrix);
    s21_remove_matrix(&A);
    if (A.matrix != NULL) {
      free(A.matrix);
      ck_assert_msg(0, "s21_remove_matrix() didn't free memory");
    }
    ck_assert_msg(A.rows == 0 && A.columns == 0,
                  "Numbers of colomns and rows are not returned to zero");
  }
}
END_TEST

Suite* test_remove_matrix(void) {
  Suite* ps = suite_create("add");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_is_null_returned);

  suite_add_tcase(ps, tc);
  return ps;
}