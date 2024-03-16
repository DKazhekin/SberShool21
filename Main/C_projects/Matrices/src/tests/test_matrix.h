#ifndef TEST_S21_MATRIX_H
#define TEST_S21_MATRIX_H

#include <check.h>

#include "../s21_matrix.h"

Suite* s21_test_create_matrix_suite(void);
Suite* s21_test_eq_matrix_suite(void);
Suite* s21_test_remove_matrix_suite(void);
Suite* s21_test_sum_matrix_suite(void);
Suite* s21_test_sub_matrix_suite(void);
Suite* s21_test_mult_number_suite(void);
Suite* s21_test_mult_matrix_suite(void);
Suite* s21_test_transpose_suite(void);
Suite* s21_test_calc_complements_suite(void);
Suite* s21_test_determinant_suite(void);
Suite* s21_test_inverse_matrix_suite(void);

#endif  // TEST_S21_MATRIX_H