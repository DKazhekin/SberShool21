#include "test_matrix.h"

START_TEST(test_remove) {
  matrix_t A;
  s21_create_matrix(5, 7, &A);

  s21_remove_matrix(&A);

  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

Suite* s21_test_remove_matrix_suite(void) {
  Suite* suite = suite_create("test_s21_remove_matrix");
  TCase* test_case = tcase_create("Core");

  tcase_add_test(test_case, test_remove);

  suite_add_tcase(suite, test_case);
  return suite;
}