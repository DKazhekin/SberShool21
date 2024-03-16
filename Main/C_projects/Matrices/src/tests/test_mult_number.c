#include "test_matrix.h"

START_TEST(test_mult_number_loop) {
  matrix_t A = {0};
  matrix_t otvet = {0};
  matrix_t res = {0};
  s21_create_matrix(_i, _i, &A);
  s21_create_matrix(_i, _i, &otvet);

  double num = _i + 5.05;

  for (int i = 0; i < _i; i++) {
    for (int j = 0; j < _i; j++) {
      A.matrix[i][j] = (double)_i + 3.03;
    }
  }

  for (int i = 0; i < _i; i++) {
    for (int j = 0; j < _i; j++) {
      otvet.matrix[i][j] = A.matrix[i][j] * num;
    }
  }

  int err = s21_mult_number(&A, num, &res);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&otvet, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_mult_number_error_nan) {
  matrix_t A = {0};
  matrix_t otvet = {0};
  matrix_t res = {0};
  s21_create_matrix(5, 7, &A);
  s21_create_matrix(5, 7, &otvet);

  double num = 5.05;

  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = (double)i - 3.03;
    }
  }

  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 3; j++) {
      otvet.matrix[i][j] = A.matrix[i][j] * num;
    }
  }

  A.matrix[0][0] = NAN;

  int err = s21_mult_number(&A, num, &res);
  ck_assert_int_eq(err, 2);
  ck_assert_int_eq(s21_eq_matrix(&otvet, &res), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_test_mult_number_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_s21_mult_number");
  tc_core = tcase_create("Core");

  suite_add_tcase(s, tc_core);

  tcase_add_loop_test(tc_core, test_mult_number_loop, 1, 100);
  tcase_add_test(tc_core, test_mult_number_error_nan);

  return s;
}