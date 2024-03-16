#include "test_matrix.h"

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(NULL);
  srunner_add_suite(sr, s21_test_create_matrix_suite());
  srunner_add_suite(sr, s21_test_eq_matrix_suite());
  srunner_add_suite(sr, s21_test_remove_matrix_suite());
  srunner_add_suite(sr, s21_test_sum_matrix_suite());
  srunner_add_suite(sr, s21_test_sub_matrix_suite());
  srunner_add_suite(sr, s21_test_mult_number_suite());
  srunner_add_suite(sr, s21_test_mult_matrix_suite());
  srunner_add_suite(sr, s21_test_transpose_suite());
  srunner_add_suite(sr, s21_test_calc_complements_suite());
  srunner_add_suite(sr, s21_test_determinant_suite());
  srunner_add_suite(sr, s21_test_inverse_matrix_suite());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}