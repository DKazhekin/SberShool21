#include "test_matrix.h"

START_TEST(test_create_matrix_correct) {
  matrix_t result;
  int rows = 5;
  int columns = 7;

  int err = s21_create_matrix(rows, columns, &result);

  ck_assert_int_eq(err, 0);

  ck_assert_int_eq(result.rows, rows);
  ck_assert_int_eq(result.columns, columns);
  ck_assert_ptr_nonnull(result.matrix);

  for (int i = 0; i < rows; i++) {
    ck_assert_ptr_nonnull(result.matrix[i]);
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0, 1e-7);
    }
  }
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_matrix_incorrect) {
  matrix_t result;
  int rows = 0;
  int columns = 7;

  int err = s21_create_matrix(rows, columns, &result);

  ck_assert_int_eq(err, 1);
}

START_TEST(test_create_matrix_null_ptr) {
  int rows = 5;
  int columns = 7;

  int err = s21_create_matrix(rows, columns, NULL);

  ck_assert_int_eq(err, 1);
}

Suite* s21_test_create_matrix_suite(void) {
  Suite* suite = suite_create("\n test_s21_create_matrix");
  TCase* test_case = tcase_create("Core");

  tcase_add_test(test_case, test_create_matrix_correct);
  tcase_add_test(test_case, test_create_matrix_incorrect);
  tcase_add_test(test_case, test_create_matrix_null_ptr);

  suite_add_tcase(suite, test_case);

  return suite;
}
