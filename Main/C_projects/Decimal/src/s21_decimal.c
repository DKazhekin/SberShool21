#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  int error = 0;

  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long result_long = {{0, 0, 0, 0, 0, 0, 0}};

  preparing_long_dec(value_1, value_2, &value1_long, &value2_long);

  error = s21_add_long(value1_long, value2_long, &result_long);

  if (!error) error = s21_longdec_to_dec(result_long, result);

  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  int error = 0;

  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long result_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_dec_to_longdec(value_1, &value1_long);
  s21_dec_to_longdec(value_2, &value2_long);

  int sign1 = get_sign(value1_long.bits[6]);
  int sign2 = get_sign(value2_long.bits[6]);
  int sign3 = (sign1 && sign2) || (sign1 == 0 && sign2 == 0) ? 0 : 1;

  error = s21_mul_long(value1_long, value2_long, &result_long);

  set_sign(&result_long.bits[6], sign3);
  if (!error) {
    error = s21_longdec_to_dec(result_long, result);
  }
  if (error) error = sign3 == 0 ? 1 : 2;

  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  int error = 0;

  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long result_long = {{0, 0, 0, 0, 0, 0, 0}};

  preparing_long_dec(value_1, value_2, &value1_long, &value2_long);

  error = s21_sub_long(value1_long, value2_long, &result_long);

  if (!error) error = s21_longdec_to_dec(result_long, result);

  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  int error = 0;

  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long result_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long mod_long = {{0, 0, 0, 0, 0, 0, 0}};

  s21_dec_to_longdec(value_1, &value1_long);
  s21_dec_to_longdec(value_2, &value2_long);
  int sign1 = get_sign(value1_long.bits[6]);
  int sign2 = get_sign(value2_long.bits[6]);
  set_sign(&value1_long.bits[6], 0);
  set_sign(&value2_long.bits[6], 0);
  int sign3 = (sign1 && sign2) || (sign1 == 0 && sign2 == 0) ? 0 : 1;

  error = s21_div_long(value1_long, value2_long, &result_long, &mod_long, 0);

  set_sign(&result_long.bits[6], sign3);
  if (!error) error = s21_longdec_to_dec(result_long, result);

  if (error && (error != 3)) error = sign3 == 0 ? 1 : 2;

  return error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset_decimal(result);
  int error = 0;

  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long mod_long = {{0, 0, 0, 0, 0, 0, 0}};

  s21_dec_to_longdec(value_1, &value1_long);
  s21_dec_to_longdec(value_2, &value2_long);
  int sign = get_sign(value1_long.bits[6]);
  set_sign(&value1_long.bits[6], 0);
  set_sign(&value2_long.bits[6], 0);

  error = s21_mod_long(value1_long, value2_long, &mod_long);
  set_sign(&mod_long.bits[6], sign);
  if (!error) error = s21_longdec_to_dec(mod_long, result);

  return error;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  preparing_long_dec(value_1, value_2, &value1_long, &value2_long);
  result = s21_is_less_long(value1_long, value2_long);
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  preparing_long_dec(value_1, value_2, &value1_long, &value2_long);
  result = !s21_is_greater_long(value1_long, value2_long);
  return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  preparing_long_dec(value_1, value_2, &value1_long, &value2_long);
  result = s21_is_greater_long(value1_long, value2_long);
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  preparing_long_dec(value_1, value_2, &value1_long, &value2_long);
  result = !s21_is_less_long(value1_long, value2_long);
  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long value2_long = {{0, 0, 0, 0, 0, 0, 0}};
  preparing_long_dec(value_1, value_2, &value1_long, &value2_long);
  result = s21_is_equal_long(value1_long, value2_long);
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  reset_decimal(dst);
  int error = 1;
  int flag = 0;
  if (src < 0) {
    flag = 1;
    src *= -1;
  }
  dst->bits[0] = src;
  if (flag) {
    set_sign(&dst->bits[3], 1);
  }
  error = 0;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  reset_decimal(dst);
  int error = 1;
  int sign = get_float_sign(&src);
  int exponent = get_float_exponent(&src);
  if (dst != NULL && isnan(src) == 0 && isinf(src) == 0 && src != 0) {
    reset_decimal(dst);
    double temp = (double)fabs(src);
    int scale = 0;
    while (scale < 28 && (int)temp / (int)pow(2, 21) == 0) {
      temp *= 10;
      scale++;
    }
    temp = round(temp);
    if ((exponent > -94 && exponent < 96) && scale <= 28) {
      union float_to_dec mantissa;
      temp = (float)temp;
      while (fmod(temp, 10) == 0 && scale > 0) {
        scale--;
        temp /= 10;
      }
      mantissa.fl = temp;
      exponent = get_float_exponent(&mantissa.fl);
      dst->bits[exponent / 32] |= 1 << exponent % 32;
      for (int i = exponent - 1, j = 22; j >= 0; i--, j--) {
        if ((mantissa.d & (1 << j)) != 0) {
          dst->bits[i / 32] |= 1 << i % 32;
        }
      }
      dst->bits[3] = (sign << 31) | (scale << 16);
      error = 0;
    }
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;

  s21_decimal_long value = {{0, 0, 0, 0, 0, 0}};
  s21_dec_to_longdec(src, &value);
  s21_decimal_long ipart_long = {{0, 0, 0, 0, 0, 0}};
  s21_decimal_long mod = {{0, 0, 0, 0, 0, 0}};
  s21_decimal_long temp_div = {{1, 0, 0, 0, 0, 0}};
  int exp = (int)get_exponent(value.bits[6]);
  for (int i = 0; i < exp; i++) {
    mul_10_long(&temp_div);
  }
  int sign_temp = get_sign(value.bits[6]);
  set_sign(&value.bits[6], 0);
  error = s21_div_long(value, temp_div, &ipart_long, &mod, 1);
  set_sign(&ipart_long.bits[6], sign_temp);
  s21_decimal ipart = {{0, 0, 0}};

  if (!error) {
    s21_longdec_to_dec(ipart_long, &ipart);
    if (ipart.bits[1] || ipart.bits[2]) {
      error = 1;
    } else {
      unsigned int x = 2147483647;
      if (ipart.bits[0] > x) {
        error = 1;
      } else {
        int sign = get_sign(ipart.bits[3]);
        int temp = (int)ipart.bits[0];
        if (sign) {
          temp *= -1;
        }
        *dst = temp;
      }
    }
  }
  if (error) error = 1;
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 1;
  double temp = 0;
  int scale = 0;
  for (int i = 0; i < 96; i++) {
    if ((src.bits[i / 32] & (1 << i % 32)) != 0) {
      temp += pow(2, i);
    }
  }
  scale = (src.bits[3] & ~0x80000000) >> 16;
  if (scale > 0) {
    for (int i = scale; i > 0; i--) {
      temp /= 10.0;
    }
  }
  *dst = (float)temp;
  if (src.bits[3] >> 31) {
    *dst *= -1;
  } else {
    *dst *= 1;
  }
  error = 0;
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  reset_decimal(result);

  int error = 0;

  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long result_long = {{0, 0, 0, 0, 0, 0, 0}};

  s21_dec_to_longdec(value, &value1_long);

  error = s21_floor_long(value1_long, &result_long);

  if (!error) error = s21_longdec_to_dec(result_long, result);

  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  reset_decimal(result);

  int error = 0;

  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long result_long = {{0, 0, 0, 0, 0, 0, 0}};

  s21_dec_to_longdec(value, &value1_long);
  error = s21_round_long(value1_long, &result_long);

  if (!error) error = s21_longdec_to_dec(result_long, result);

  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  reset_decimal(result);
  int error = 0;
  s21_decimal_long value1_long = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long result_long = {{0, 0, 0, 0, 0, 0, 0}};

  s21_dec_to_longdec(value, &value1_long);

  int sign = get_sign(value1_long.bits[6]);
  set_sign(&value1_long.bits[6], 0);
  int exp = (int)get_exponent(value1_long.bits[6]);
  if (exp > 0) {
    s21_decimal_long temp_div = {{1, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long mod = {{0, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long temp_long_dec = value1_long;
    set_exponent(&temp_long_dec.bits[6], 0);

    for (int i = 0; i < exp; i++) {
      error = mul_10_long(&temp_div);
    }
    error = s21_div_long(temp_long_dec, temp_div, &temp_long_dec, &mod, 1);
    result_long = temp_long_dec;
  } else {
    result_long = value1_long;
  }
  set_sign(&result_long.bits[6], sign);
  if (!error) error = s21_longdec_to_dec(result_long, result);

  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  result->bits[3] = value.bits[3] ^ 2147483648;
  return 0;
}

int get_float_sign(float *src) { return *(int *)src >> 31; }

int get_float_exponent(float *src) {
  return ((*(int *)src & ~0x80000000) >> 23) - 127;
}

void preparing_long_dec(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal_long *value1_long,
                        s21_decimal_long *value2_long) {
  s21_dec_to_longdec(value_1, value1_long);
  s21_dec_to_longdec(value_2, value2_long);

  int sign1 = get_sign(value1_long->bits[6]);
  int sign2 = get_sign(value2_long->bits[6]);
  s21_reduce_long(value1_long, value2_long);
  set_sign(&value1_long->bits[6], sign1);
  set_sign(&value2_long->bits[6], sign2);
}

int getbit(unsigned int x, int i) {
  unsigned int y = 1 << i;
  return (x & y) ? 1 : 0;
}

void setbit(unsigned int *x, int i, int bit) {
  int y = 1 << i;
  *x = bit ? *x | y : *x & (~y);
}

void reset_decimal(s21_decimal *result) {
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
}

unsigned int get_exponent(unsigned int value) {
  value = (value << 1) >> 17;
  return value;
}

void set_exponent(unsigned int *value, int d) {
  int sign = get_sign(*value);
  *value = 0;
  *value = *value >> 16;
  *value = *value | d;
  *value = *value << 16;
  setbit(value, 31, sign);
}

int get_sign(unsigned int x) { return getbit(x, 31); }

void set_sign(unsigned int *x, int sign) { setbit(x, 31, sign); }
