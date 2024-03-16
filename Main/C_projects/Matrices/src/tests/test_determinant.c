#include "test_matrix.h"

START_TEST(test_determinant_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 432.23;

  double result;
  int err = s21_determinant(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(result, 432.23, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 3.0;
  A.matrix[0][1] = 3.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 7.0;

  double result;
  int err = s21_determinant(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(result, 15.0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  double result;
  int err = s21_determinant(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(result, 0.0, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5x5) {
  matrix_t A = {0};
  double result = 0.0;

  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 1.2;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[0][4] = -5;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 7.3;
  A.matrix[1][2] = -8;
  A.matrix[1][3] = 9;
  A.matrix[1][4] = 8;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 5.4;
  A.matrix[2][3] = 4;
  A.matrix[2][4] = -3;
  A.matrix[3][0] = 2;
  A.matrix[3][1] = -1;
  A.matrix[3][2] = 10;
  A.matrix[3][3] = 20.5;
  A.matrix[3][4] = 30;
  A.matrix[4][0] = 40;
  A.matrix[4][1] = 50;
  A.matrix[4][2] = -60;
  A.matrix[4][3] = 70;
  A.matrix[4][4] = 80.6;

  int err = s21_determinant(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(result, -43619.5748, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_error_null_ptr) {
  double result = 0.0;
  int err = s21_determinant(NULL, &result);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_determinant_error_not_square_matrix) {
  matrix_t A;
  s21_create_matrix(5, 7, &A);

  double result;
  int err = s21_determinant(&A, &result);

  ck_assert_int_eq(err, 2);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_determinant_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_s21_determinant");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_determinant_1x1);
  tcase_add_test(tc_core, test_determinant_2x2);
  tcase_add_test(tc_core, test_determinant_3x3);
  tcase_add_test(tc_core, test_determinant_5x5);
  tcase_add_test(tc_core, test_determinant_error_null_ptr);
  tcase_add_test(tc_core, test_determinant_error_not_square_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}
