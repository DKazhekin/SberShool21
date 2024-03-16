#include "test_matrix.h"
START_TEST(test_eq_matrix_no_err) {
  matrix_t A;
  matrix_t B;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);

  A.matrix[0][1] = 12.23;
  A.matrix[1][0] = 432;
  A.matrix[1][2] = -47;

  B.matrix[0][1] = 12.23;
  B.matrix[1][0] = 432;
  B.matrix[1][2] = -47;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_error) {
  matrix_t A;
  matrix_t B;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);

  A.matrix[0][1] = 12.23;
  A.matrix[1][0] = 4322;
  A.matrix[1][2] = -47;

  B.matrix[0][1] = 12.23;
  B.matrix[1][0] = 432;
  B.matrix[1][2] = -47;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_null) {
  matrix_t B;
  s21_create_matrix(2, 2, &B);

  B.matrix[0][1] = 12.23;
  B.matrix[1][0] = 432;
  B.matrix[1][1] = -47;

  int result = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_test_eq_matrix_suite(void) {
  Suite *suite = suite_create("test_s21_eq_matrix");
  TCase *test_case = tcase_create("Core");

  tcase_add_test(test_case, test_eq_matrix_no_err);
  tcase_add_test(test_case, test_eq_matrix_error);
  tcase_add_test(test_case, test_s21_eq_matrix_null);

  suite_add_tcase(suite, test_case);

  return suite;
}