#include "test_matrix.h"

START_TEST(test_sum_matrix_loop) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t otvet = {0};
  matrix_t res = {0};

  s21_create_matrix(_i, _i, &A);
  s21_create_matrix(_i, _i, &B);
  s21_create_matrix(_i, _i, &otvet);

  for (int i = 0; i < _i; i++) {
    for (int j = 0; j < _i; j++) {
      A.matrix[i][j] = (double)_i + 5.05;
    }
  }

  for (int i = 0; i < _i; i++) {
    for (int j = 0; j < _i; j++) {
      B.matrix[i][j] = (double)_i + 3.03;
    }
  }
  for (int i = 0; i < _i; i++) {
    for (int j = 0; j < _i; j++) {
      otvet.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }

  int err = s21_sum_matrix(&A, &B, &res);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&otvet, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_sum_matrix_error_diff_rows_cols) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t otvet = {0};
  matrix_t res = {0};

  s21_create_matrix(5, 7, &A);
  s21_create_matrix(2, 14, &B);
  s21_create_matrix(3, 6, &otvet);

  int err = s21_sum_matrix(&A, &B, &res);
  ck_assert_int_eq(err, 2);
  ck_assert_int_eq(s21_eq_matrix(&otvet, &res), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_sum_matrix_error_nan) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t otvet = {0};
  matrix_t res = {0};

  s21_create_matrix(5, 7, &A);
  s21_create_matrix(5, 7, &B);
  s21_create_matrix(5, 7, &otvet);

  A.matrix[3][4] = NAN;
  B.matrix[3][5] = INFINITY;

  int err = s21_sum_matrix(&A, &B, &res);
  ck_assert_int_eq(err, 2);
  ck_assert_int_eq(s21_eq_matrix(&otvet, &res), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_test_sum_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_s21_sum_matrix");
  tc_core = tcase_create("Core");

  suite_add_tcase(s, tc_core);

  tcase_add_loop_test(tc_core, test_sum_matrix_loop, 1, 100);
  tcase_add_test(tc_core, test_sum_matrix_error_nan);
  tcase_add_test(tc_core, test_sum_matrix_error_diff_rows_cols);

  return s;
}