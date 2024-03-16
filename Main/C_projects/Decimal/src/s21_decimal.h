#ifndef C5_S21_DECIMAL_0_SRC_S21_DECIMAL_H_
#define C5_S21_DECIMAL_0_SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdlib.h>

#include "s21_decimal_long.h"

typedef struct {
  unsigned int bits[4];
} s21_decimal;

union float_to_dec {
  float fl;
  int d;
};

int getbit(unsigned int x, int i);

void setbit(unsigned int *x, int i, int bit);
void set_sign(unsigned int *x, int sign);

void preparing_long_dec(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal_long *value1_long,
                        s21_decimal_long *value2_long);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int get_float_sign(float *src);
int get_float_exponent(float *src);

void reset_decimal(s21_decimal *result);

void set_exponent(unsigned int *value, int d);

unsigned int get_exponent(unsigned int value);
int get_sign(unsigned int x);

void s21_dec_to_longdec(s21_decimal input_dec,
                        s21_decimal_long *output_longdec);

int s21_longdec_to_dec(s21_decimal_long long_decimal, s21_decimal *decimal);

#endif  // C5_S21_DECIMAL_0_SRC_S21_DECIMAL_H_