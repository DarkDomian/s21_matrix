#ifndef S21_SUITES_H
#define S21_SUITES_H

#include <check.h>

#define HELPER_INITIALIZE \
  (x) x.matrix =          \
      (double **)malloc((x.columns * x.rows + x.columns) * sizeof(double));

Suite *test_remove_matrix(void);
Suite *test_create_matrix(void);

#endif  // S21_SUITES_H