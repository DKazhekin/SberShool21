#include "test_matrix.h"

START_TEST(test_inverse_matrix_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 7.0;

  matrix_t result = {0};
  int err = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.142857142857143, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_2x2) {
  matrix_t A;
  matrix_t otvet;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &otvet);

  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 9.0;
  A.matrix[1][1] = 3.0;

  otvet.matrix[0][0] = -0.142857142857143;
  otvet.matrix[0][1] = 0.19047619047619;
  otvet.matrix[1][0] = 0.428571428571429;
  otvet.matrix[1][1] = -0.238095238095238;

  matrix_t result = {0};
  int err = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &otvet), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_3x3) {
  matrix_t A;
  matrix_t otvet;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &otvet);

  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 4.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 3.0;
  A.matrix[2][1] = 4.0;
  A.matrix[2][2] = 5.0;

  otvet.matrix[0][0] = 0.1875;
  otvet.matrix[0][1] = 0.5;
  otvet.matrix[0][2] = -0.3125;
  otvet.matrix[1][0] = 0.25;
  otvet.matrix[1][1] = -1.0;
  otvet.matrix[1][2] = 0.25;
  otvet.matrix[2][0] = -0.3125;
  otvet.matrix[2][1] = 0.5;
  otvet.matrix[2][2] = 0.1875;

  matrix_t result = {0};
  int err = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &otvet), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&otvet);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_5x5) {
  matrix_t A = {0};
  matrix_t proverka = {0};
  matrix_t result = {0};

  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &proverka);

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

  proverka.matrix[0][0] = -0.525365643866845;
  proverka.matrix[0][1] = 2.810738081747647;
  proverka.matrix[0][2] = -0.064756018667105;
  proverka.matrix[0][3] = 0.172356746586168;
  proverka.matrix[0][4] = -0.378135277008707;
  proverka.matrix[1][0] = 0.472003683997397;
  proverka.matrix[1][1] = -3.338278391471161;
  proverka.matrix[1][2] = 0.251596216843453;
  proverka.matrix[1][3] = -0.225209164579018;
  proverka.matrix[1][4] = 0.453812768482099;
  proverka.matrix[2][0] = 0.089017144660475;
  proverka.matrix[2][1] = -0.778268934432621;
  proverka.matrix[2][2] = 0.106851385447251;
  proverka.matrix[2][3] = -0.026765414503765;
  proverka.matrix[2][4] = 0.096709104096998;
  proverka.matrix[3][0] = 0.070760524699108;
  proverka.matrix[3][1] = 0.733793306027366;
  proverka.matrix[3][2] = -0.116036894518284;
  proverka.matrix[3][3] = 0.059349446019818;
  proverka.matrix[3][4] = -0.094852827405369;
  proverka.matrix[4][0] = -0.027267574373513;
  proverka.matrix[4][1] = -0.540660932806709;
  proverka.matrix[4][2] = 0.056378357910999;
  proverka.matrix[4][3] = -0.017297738537332;
  proverka.matrix[4][4] = 0.072915841444653;

  int err = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &proverka), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&proverka);
}
END_TEST

START_TEST(test_inverse_matrix_error_null) {
  int err = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_inverse_matrix_error_not_square) {
  matrix_t A;
  s21_create_matrix(5, 7, &A);

  matrix_t result = {0};
  int err = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(err, 2);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_s21_inverse_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_inverse_matrix_1x1);
  tcase_add_test(tc_core, test_inverse_matrix_2x2);
  tcase_add_test(tc_core, test_inverse_matrix_3x3);
  tcase_add_test(tc_core, test_inverse_matrix_5x5);
  tcase_add_test(tc_core, test_inverse_matrix_error_null);
  tcase_add_test(tc_core, test_inverse_matrix_error_not_square);

  suite_add_tcase(s, tc_core);

  return s;
}