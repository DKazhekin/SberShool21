#include "test_matrix.h"

START_TEST(test_mult_matrix_loop) {
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

  for (int z = 0; z < _i; z++) {
    for (int x = 0; x < _i; x++) {
      for (int c = 0; c < _i; c++) {
        otvet.matrix[z][x] += A.matrix[z][c] * B.matrix[c][x];
      }
    }
  }

  int err = s21_mult_matrix(&A, &B, &res);
  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&otvet, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_mult_matrix_error_nan) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t otvet = {0};
  matrix_t res = {0};
  s21_create_matrix(5, 7, &A);
  s21_create_matrix(5, 7, &B);
  s21_create_matrix(5, 7, &otvet);

  A.matrix[3][4] = NAN;
  B.matrix[3][5] = INFINITY;

  int err = s21_mult_matrix(&A, &B, &res);
  ck_assert_int_eq(err, 2);
  ck_assert_int_eq(s21_eq_matrix(&otvet, &res), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_test_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_s21_mult_matrix");
  tc_core = tcase_create("Core");

  suite_add_tcase(s, tc_core);

  tcase_add_loop_test(tc_core, test_mult_matrix_loop, 1, 100);
  tcase_add_test(tc_core, test_mult_matrix_error_nan);

  return s;
}