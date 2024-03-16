#include "test_matrix.h"

START_TEST(test_calc_complements_1x1) {
  matrix_t A = {0};
  matrix_t proverka = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &proverka);

  A.matrix[0][0] = 3;
  proverka.matrix[0][0] = 1;

  int err = s21_calc_complements(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &proverka), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&proverka);
}
END_TEST

START_TEST(test_calc_complements_2x2) {
  matrix_t A = {0};
  matrix_t proverka = {0};
  matrix_t result = {0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &proverka);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = 3;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 4;

  proverka.matrix[0][0] = 4;
  proverka.matrix[0][1] = -7;
  proverka.matrix[1][0] = -3;
  proverka.matrix[1][1] = 5;

  int err = s21_calc_complements(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &proverka), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&proverka);
}
END_TEST

START_TEST(test_calc_complements_3x3) {
  matrix_t A = {0};
  matrix_t proverka = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &proverka);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  proverka.matrix[0][0] = 0;
  proverka.matrix[0][1] = 10;
  proverka.matrix[0][2] = -20;
  proverka.matrix[1][0] = 4;
  proverka.matrix[1][1] = -14;
  proverka.matrix[1][2] = 8;
  proverka.matrix[2][0] = -8;
  proverka.matrix[2][1] = -2;
  proverka.matrix[2][2] = 4;

  int err = s21_calc_complements(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &proverka), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&proverka);
}
END_TEST

START_TEST(test_calc_complements_5x5) {
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

  proverka.matrix[0][0] = 22916.226;
  proverka.matrix[0][1] = -20588.6;
  proverka.matrix[0][2] = -3882.89;
  proverka.matrix[0][3] = -3086.544;
  proverka.matrix[0][4] = 1189.4;
  proverka.matrix[1][0] = -122603.2;
  proverka.matrix[1][1] = 145614.284;
  proverka.matrix[1][2] = 33947.76;
  proverka.matrix[1][3] = -32007.752;
  proverka.matrix[1][4] = 23583.4;
  proverka.matrix[2][0] = 2824.63;
  proverka.matrix[2][1] = -10974.52;
  proverka.matrix[2][2] = -4660.812;
  proverka.matrix[2][3] = 5061.48;
  proverka.matrix[2][4] = -2459.2;
  proverka.matrix[3][0] = -7518.128;
  proverka.matrix[3][1] = 9823.528;
  proverka.matrix[3][2] = 1167.496;
  proverka.matrix[3][3] = -2588.7976;
  proverka.matrix[3][4] = 754.52;
  proverka.matrix[4][0] = 16494.1;
  proverka.matrix[4][1] = -19795.12;
  proverka.matrix[4][2] = -4218.41;
  proverka.matrix[4][3] = 4137.44;
  proverka.matrix[4][4] = -3180.558;

  int err = s21_calc_complements(&A, &result);

  ck_assert_int_eq(err, 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &proverka), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&proverka);
}
END_TEST

START_TEST(test_calc_complements_not_square) {
  matrix_t a = {0};
  matrix_t res = {0};
  s21_create_matrix(1, 2, &a);

  int err = s21_calc_complements(&a, &res);
  ck_assert_int_eq(err, 2);

  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_calc_complements_incorrect) {
  matrix_t a = {0};
  matrix_t res = {0};
  ck_assert_int_eq(s21_calc_complements(&a, &res), 1);
  s21_remove_matrix(&res);
}
END_TEST

Suite *s21_test_calc_complements_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("test_s21_calc_complements");
  tc_core = tcase_create("Core");

  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_calc_complements_1x1);
  tcase_add_test(tc_core, test_calc_complements_2x2);
  tcase_add_test(tc_core, test_calc_complements_3x3);
  tcase_add_test(tc_core, test_calc_complements_5x5);
  tcase_add_test(tc_core, test_calc_complements_not_square);
  tcase_add_test(tc_core, test_calc_complements_incorrect);

  return s;
}