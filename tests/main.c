#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/s21_matrix.h"
#include "../include/s21_suites.h"

#define FILENAME_SIZE 128

int main(void) {
  int number_failed;
  SRunner *sr = srunner_create(test_remove_matrix());

  srunner_add_suite(sr, test_create_matrix());
  srunner_add_suite(sr, test_eq_matrix());
  srunner_add_suite(sr, test_sum_matrix());
  srunner_add_suite(sr, test_sub_matrix());
  srunner_add_suite(sr, test_mult_number());
  srunner_add_suite(sr, test_mult_matrix());
  srunner_add_suite(sr, test_transpose());
  srunner_add_suite(sr, test_inverse_matrix());
  srunner_add_suite(sr, test_determinant());
  srunner_add_suite(sr, test_calc_complements());

  //  Check for CK_RUN_SUITE and set a custom log file
  const char *suite = getenv("CK_RUN_SUITE");
  if (suite && strlen(suite) > 0) {
    char logname[FILENAME_SIZE];
    snprintf(logname, sizeof(logname), "./%s.log", suite);
    srunner_set_log(sr, logname);
  } else {
    srunner_set_log(sr, "./test.log");
  }

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? S21_SUCCESS : S21_ERROR;
}