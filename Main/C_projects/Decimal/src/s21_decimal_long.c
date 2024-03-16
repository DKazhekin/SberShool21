#include "s21_decimal.h"

int s21_add_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result) {
  reset_decimal_long(result);
  int error = 0;
  int flag = 0;
  int sign1 = get_sign(value_1.bits[6]);
  int sign2 = get_sign(value_2.bits[6]);
  if ((sign1 == 0 && sign2 == 0) || (sign1 == 1 && sign2 == 1)) {
    for (int i = 0; i < 192; i++) {
      start_adding_long(&value_1, &value_2, result, i, &flag);
    }
    if (flag == 1) {
      error = 1;
      reset_decimal_long(result);
    }
    result->bits[6] = value_1.bits[6];
  } else if (sign1 == 0 && sign2 == 1) {
    s21_negate_long(value_2, &value_2);
    s21_sub_long(value_1, value_2, result);
  } else if (sign1 == 1 && sign2 == 0) {
    s21_negate_long(value_1, &value_1);
    s21_sub_long(value_2, value_1, result);
  }
  return error;
}

void start_adding_long(s21_decimal_long *value_1, s21_decimal_long *value_2,
                       s21_decimal_long *result, int i, int *flag) {
  int bit1 = getbit(value_1->bits[i / 32], i % 32);
  int bit2 = getbit(value_2->bits[i / 32], i % 32);
  if (bit1 == 1 && bit2 == 1) {
    if (*flag)
      setbit(&result->bits[i / 32], i % 32, 1);
    else
      setbit(&result->bits[i / 32], i % 32, 0);
    *flag = 1;
  } else if (bit1 == 1 || bit2 == 1) {
    if (*flag) {
      setbit(&result->bits[i / 32], i % 32, 0);
      *flag = 1;
    } else {
      setbit(&result->bits[i / 32], i % 32, 1);
      *flag = 0;
    }
  } else {
    if (*flag)
      setbit(&result->bits[i / 32], i % 32, 1);
    else
      setbit(&result->bits[i / 32], i % 32, 0);
    *flag = 0;
  }
}

void reset_decimal_long(s21_decimal_long *result) {
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  result->bits[4] = 0;
  result->bits[5] = 0;
  result->bits[6] = 0;
}

int s21_mul_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result) {
  int error = 0;
  s21_decimal_long temp = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long temp_result = {{0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 192; i++) {
    for (int j = 0; j < 192; j++) {
      int bit1 = getbit(value_1.bits[i / 32], i % 32);
      int bit2 = getbit(value_2.bits[j / 32], j % 32);
      setbit(&temp.bits[j / 32], j % 32, bit1 * bit2);
    }
    for (int n = 0; n < i && !error; n++) error = shift_left_by_1_long(&temp);
    if (!error) error = s21_add_long(temp, temp_result, &temp_result);
  }
  if (error)
    reset_decimal_long(result);
  else {
    reset_decimal_long(result);
    s21_add_long(temp, temp_result, result);
    set_exponent(&result->bits[6], (int)(get_exponent(value_1.bits[6]) +
                                         get_exponent(value_2.bits[6])));
  }
  return error;
}

void make_div(int *flag_while, int *flag_10, int flag_mod,
              s21_decimal_long *value_1, s21_decimal_long *value_2,
              s21_decimal_long *temp, s21_decimal_long *one,
              s21_decimal_long *result, s21_decimal_long *remainder,
              s21_decimal_long *zero) {
  while (*flag_while == 1) {
    while (!s21_is_less_long(*value_1, *value_2)) {
      shift_left_by_1_long(value_2);
      shift_left_by_1_long(temp);
      if (getbit(value_2->bits[5], 31)) {
        *flag_10 = 0;
        shift_left_by_1_long(temp);
        break;
      }
    }
    while (s21_is_greater_long(*temp, *one)) {
      if (*flag_10) {
        shift_right_by_1_long(value_2);
      }
      shift_right_by_1_long(temp);
      *flag_10 = 1;
      if (!s21_is_less_long(*value_1, *value_2)) {
        s21_sub_long(*value_1, *value_2, value_1);
        s21_add_long(*result, *temp, result);
      }
    }
    *remainder = *value_1;
    if (!flag_mod) {
      if (s21_is_equal_long(*remainder, *zero)) {
        *flag_while = 0;
      } else {
        int exp_result = (int)get_exponent(result->bits[6]);
        if (exp_result == 56) {
          *flag_while = 0;
        } else {
          mul_10_long(value_1);
          mul_10_long(result);
          set_exponent(&result->bits[6], exp_result + 1);
        }
      }
    } else {
      *flag_while = 0;
    }
  }
}

int s21_div_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result, s21_decimal_long *remainder,
                 int flag_mod) {
  int error = 0;
  reset_decimal_long(result);
  s21_decimal_long zero = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long one = {{1, 0, 0, 0, 0, 0, 0}};
  if (s21_is_equal_long(value_2, zero)) {
    error = 3;
  } else if (s21_is_equal_long(value_1, zero)) {
    *result = zero;
    *remainder = zero;
  } else {
    int exp1 = (int)get_exponent(value_1.bits[6]);
    int exp2 = (int)get_exponent(value_2.bits[6]);
    set_exponent(&value_1.bits[6], 0);
    set_exponent(&value_2.bits[6], 0);
    int new_exp = exp1 - exp2;
    s21_decimal_long temp = {{1, 0, 0, 0, 0, 0, 0}};
    int flag_while = 1;
    int flag_10 = 1;

    make_div(&flag_while, &flag_10, flag_mod, &value_1, &value_2, &temp, &one,
             result, remainder, &zero);

    while (new_exp < 0) {
      mul_10_long(result);
      no_zero(result);
      new_exp++;
    }
    if (new_exp > 0) {
      int exp = (int)get_exponent(result->bits[6]);
      set_exponent(&result->bits[6], new_exp + exp);
    }
  }
  return error;
}

int s21_mod_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result) {
  int error = 0;
  s21_decimal_long remainder = {{0, 0, 0, 0, 0, 0}};
  reset_decimal_long(result);
  s21_decimal_long zero = {{0, 0, 0, 0, 0, 0, 0}};
  if (s21_is_equal_long(value_2, zero)) {
    error = 3;
  } else if (s21_is_equal_long(value_1, zero)) {
    *result = zero;
    remainder = zero;
  } else {
    int exp1 = (int)get_exponent(value_1.bits[6]);
    int exp2 = (int)get_exponent(value_2.bits[6]);
    int new_exp = 0;
    if (exp1 - exp2 > 0) {
      new_exp = exp1 - exp2;
      set_exponent(&value_1.bits[6], 0);
      set_exponent(&value_2.bits[6], 0);
      for (int i = 0; i < new_exp; i++) {
        mul_10_long(&value_2);
      }
      s21_div_long(value_1, value_2, result, &remainder, 1);
      set_exponent(&remainder.bits[6], exp1);
    } else if (exp1 - exp2 < 0) {
      new_exp = exp2 - exp1;
      set_exponent(&value_1.bits[6], 0);
      set_exponent(&value_2.bits[6], 0);
      for (int i = 0; i < new_exp; i++) {
        mul_10_long(&value_1);
      }
      s21_div_long(value_1, value_2, result, &remainder, 1);
      set_exponent(&remainder.bits[6], exp2);
    } else {
      set_exponent(&value_1.bits[6], 0);
      set_exponent(&value_2.bits[6], 0);
      s21_div_long(value_1, value_2, result, &remainder, 1);
      set_exponent(&remainder.bits[6], exp1);
    }
  }
  *result = remainder;
  return error;
}

void no_zero(s21_decimal_long *value) {
  int sign = get_sign(value->bits[6]);
  int exp = (int)get_exponent(value->bits[6]);
  s21_decimal_long ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long mod = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long zero = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long temp = *value;
  set_exponent(&temp.bits[6], 0);
  while (exp > 0) {
    s21_mod_long(temp, ten, &mod);
    if (s21_is_equal_long(mod, zero)) {
      s21_div_long(temp, ten, &temp, &mod, 0);
      exp--;
    } else {
      break;
    }
  }
  *value = temp;
  set_sign(&value->bits[6], sign);
  set_exponent(&value->bits[6], exp);
}

int mul_10_long(s21_decimal_long *value) {
  int error = 0;
  s21_decimal_long temp_1 = *value;
  error = shift_left_by_1_long(&temp_1);
  s21_decimal_long temp_2 = temp_1;
  if (!error) {
    for (int i = 0; i < 2 && !error; i++) {
      error = shift_left_by_1_long(&temp_2);
    }
    if (!error) s21_add_long(temp_1, temp_2, value);
  }
  return error;
}

int shift_left_by_1_long(s21_decimal_long *value) {
  int error = 0;
  int flag = 0;
  for (int i = 0; i < 6; i++) {
    if (getbit(value->bits[i], 31)) {
      if (i == 5) error = 1;
      set_for_shift_long(value, i, flag, error);
      flag = 1;
    } else {
      set_for_shift_long(value, i, flag, error);
      flag = 0;
    }
  }
  return error;
}

void set_for_shift_long(s21_decimal_long *value, int i, int flag, int error) {
  value->bits[i] = value->bits[i] << 1;
  if (flag && !error && i != 0) {
    setbit(&value->bits[i], 0, 1);
  }
}

int shift_left_long(s21_decimal_long *value_1, int n) {
  int error = 0;
  for (int i = 0; i < n && !error; i++) {
    error = shift_left_by_1_long(value_1);
  }
  return error;
}

void set_for_shift_right_long(s21_decimal_long *value, int i, int flag,
                              int error) {
  value->bits[i] = value->bits[i] >> 1;
  if (flag && !error && i != 5) {
    setbit(&value->bits[i], 31, 1);
  }
}

int shift_right_by_1_long(s21_decimal_long *value) {
  int error = 0;
  int flag = 0;
  for (int i = 5; i >= 0; i--) {
    if (getbit(value->bits[i], 0)) {
      if (i == 0) error = 1;
      set_for_shift_right_long(value, i, flag, error);
      flag = 1;
    } else {
      set_for_shift_right_long(value, i, flag, error);
      flag = 0;
    }
  }
  return error;
}

int s21_sub_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result) {
  reset_decimal_long(result);
  int error = 0;
  if (get_sign(value_1.bits[6]) == 0 && get_sign(value_2.bits[6]) == 0) {
    if (s21_is_less_long(value_2, value_1)) {
      for (int i = 0; i < 192; i++) {
        start_subbing_long(&value_1, &value_2, result, i);
      }
    } else if (s21_is_equal_long(value_1, value_2)) {
      reset_decimal_long(result);
    } else {
      for (int i = 0; i < 192; i++)
        start_subbing_long(&value_2, &value_1, result, i);
      s21_negate_long(*result, result);
    }
  } else if ((get_sign(value_1.bits[6]) == 1 &&
              get_sign(value_2.bits[6]) == 1)) {
    s21_negate_long(value_1, &value_1);
    s21_negate_long(value_2, &value_2);
    s21_sub_long(value_2, value_1, result);
  } else if (get_sign(value_1.bits[6]) == 1 && get_sign(value_2.bits[6]) == 0) {
    s21_negate_long(value_1, &value_1);
    error = s21_add_long(value_1, value_2, result);
    s21_negate_long(*result, result);
  } else if ((get_sign(value_1.bits[6]) == 0 &&
              get_sign(value_2.bits[6]) == 1)) {
    s21_negate_long(value_2, &value_2);
    error = s21_add_long(value_1, value_2, result);
  }
  if (error) error = 2;
  int exp = (int)get_exponent(value_1.bits[6]);
  set_exponent(&result->bits[6], exp);
  return error;
}

void start_subbing_long(s21_decimal_long *value_1, s21_decimal_long *value_2,
                        s21_decimal_long *result, int i) {
  int bit1 = getbit(value_1->bits[i / 32], i % 32);
  int bit2 = getbit(value_2->bits[i / 32], i % 32);
  if ((bit1 == 1 && bit2 == 1) || (bit1 == 0 && bit2 == 0)) {
    setbit(&result->bits[i / 32], i % 32, 0);
  } else if (bit1 == 1 && bit2 == 0) {
    setbit(&result->bits[i / 32], i % 32, 1);
  } else if (bit1 == 0 && bit2 == 1) {
    int k = 1;
    int n = 0;

    if ((i + k) % 32 == 0) {
      n += 32;
    }
    while (getbit(value_1->bits[(i + n) / 32], (i + k) % 32) != 1) {
      setbit(&value_1->bits[(i + n) / 32], (i + k) % 32, 1);
      k++;
      if ((i + k) % 32 == 0) n += 32;
    }
    setbit(&value_1->bits[(i + n) / 32], (i + k) % 32, 0);
    setbit(&result->bits[i / 32], i % 32, 1);
  }
}

int s21_reduce_long(s21_decimal_long *value_1, s21_decimal_long *value_2) {
  int ex_1 = (int)get_exponent(value_1->bits[6]);
  int ex_2 = (int)get_exponent(value_2->bits[6]);
  int error = 0;
  int flag = 0;
  int result = 0;
  if (ex_1 > ex_2) {
    result = ex_1 - ex_2;
    flag = 1;
  } else {
    result = ex_2 - ex_1;
  }

  for (int i = 0; i < result && !error; i++) {
    if (flag) {
      error = mul_10_long(value_2);
    } else {
      error = mul_10_long(value_1);
    }
  }
  if (!error) {
    if (flag)
      value_2->bits[6] = value_1->bits[6];
    else
      value_1->bits[6] = value_2->bits[6];
  }
  return error;
}

void s21_dec_to_longdec(s21_decimal input_dec,
                        s21_decimal_long *output_longdec) {
  for (int i = 0; i < 3; i++) output_longdec->bits[i] = input_dec.bits[i];
  for (int i = 4; i < 7; i++) output_longdec->bits[i] = 0;
  output_longdec->bits[6] = input_dec.bits[3];
  int sing = getbit(input_dec.bits[3], 31);
  setbit(&output_longdec->bits[6], 31, sing);
}

void bank_round(s21_decimal_long mod, s21_decimal_long *temp_long_dec,
                s21_decimal_long *long_decimal) {
  s21_decimal_long zero_five = {{5, 0, 0, 0, 0, 0, 65536}};
  s21_decimal_long ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long temp = {{0, 0, 0, 0, 0, 0, 0}};
  int sign = get_sign(long_decimal->bits[6]);
  if (!s21_is_less_long(mod, zero_five)) {
    s21_decimal_long temp3 = {{0, 0, 0, 0, 0, 0, 0}};
    int exp = (int)get_exponent(temp_long_dec->bits[6]);
    set_exponent(&temp_long_dec->bits[6], 0);
    s21_div_long(*temp_long_dec, ten, &temp, &temp3, 1);
    set_exponent(&temp_long_dec->bits[6], exp);
    reset_decimal_long(&temp);
    int digit = (int)temp3.bits[0];
    if (digit % 2 != 0 ||
        (digit % 2 == 0 && !s21_is_equal_long(mod, zero_five))) {
      s21_decimal_long one = {{1, 0, 0, 0, 0, 0, 0}};
      set_exponent(&one.bits[6], exp);
      set_sign(&one.bits[6], sign);
      s21_add_long(*temp_long_dec, one, temp_long_dec);
    }
    no_zero(temp_long_dec);
    *long_decimal = *temp_long_dec;
  } else {
    no_zero(temp_long_dec);
    *long_decimal = *temp_long_dec;
  }
}

void div10_with_round(s21_decimal_long *long_decimal) {
  int exp_long = (int)get_exponent(long_decimal->bits[6]);
  s21_decimal_long ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long mod = {{0, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long zero_five = {{5, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long temp = {{0, 0, 0, 0, 0, 0, 0}};

  s21_decimal_long temp_long_dec = *long_decimal;
  int sign = get_sign(long_decimal->bits[6]);
  set_exponent(&temp_long_dec.bits[6], 0);

  s21_div_long(temp_long_dec, ten, &temp_long_dec, &mod, 1);

  if (!s21_is_less_long(mod, zero_five)) {
    s21_decimal_long temp3 = {{0, 0, 0, 0, 0, 0, 0}};

    s21_div_long(temp_long_dec, ten, &temp, &temp3, 1);

    int digit = (int)temp3.bits[0];
    if (digit % 2 != 0 ||
        (digit % 2 == 0 && !s21_is_equal_long(mod, zero_five))) {
      s21_decimal_long one = {{1, 0, 0, 0, 0, 0, 0}};
      s21_add_long(temp_long_dec, one, &temp_long_dec);
    }
    set_exponent(&temp_long_dec.bits[6], --exp_long);
    *long_decimal = temp_long_dec;
  } else {
    set_exponent(&temp_long_dec.bits[6], --exp_long);
    *long_decimal = temp_long_dec;
  }
  set_sign(&long_decimal->bits[6], sign);
}

void get_mod_from_longdec(int exp_long, s21_decimal_long *long_decimal) {
  s21_decimal_long temp = *long_decimal;

  int x = 0;
  while (temp.bits[3] || temp.bits[4] || temp.bits[5]) {
    div10_with_round(&temp);
    x++;
    if (x == exp_long) {
      break;
    }
  }
  int temp_exp = (int)get_exponent(temp.bits[6]);
  temp_exp = temp_exp == exp_long ? 28 : temp_exp;

  int mod_exp = 0;
  if (temp_exp < 28) {
    mod_exp = exp_long - temp_exp;
  } else {
    mod_exp = exp_long >= 28 ? exp_long - 28 : temp_exp;
  }
  int new_exp = temp_exp >= 28 ? 28 : temp_exp;

  s21_decimal_long temp_div = {{1, 0, 0, 0, 0, 0, 0}};
  s21_decimal_long mod = {{0, 0, 0, 0, 0, 0, 0}};

  s21_decimal_long temp_long_dec = *long_decimal;

  for (int i = 0; i < mod_exp; i++) {
    mul_10_long(&temp_div);
  }

  set_exponent(&temp_long_dec.bits[6], 0);
  int sign3 = get_sign(temp_long_dec.bits[6]);
  s21_div_long(temp_long_dec, temp_div, &temp_long_dec, &mod, 1);
  set_sign(&temp_long_dec.bits[6], sign3);
  set_exponent(&temp_long_dec.bits[6], new_exp);
  set_exponent(&mod.bits[6], mod_exp);

  bank_round(mod, &temp_long_dec, long_decimal);
}

int s21_longdec_to_dec(s21_decimal_long long_decimal, s21_decimal *decimal) {
  int error = 0;
  int sign = get_sign(long_decimal.bits[6]);
  set_sign(&long_decimal.bits[6], 0);
  int exp_long = (int)get_exponent(long_decimal.bits[6]);

  if (exp_long > 28 ||
      ((long_decimal.bits[3] || long_decimal.bits[4] || long_decimal.bits[5]) &&
       exp_long != 0)) {
    get_mod_from_longdec(exp_long, &long_decimal);
  }
  if (!long_decimal.bits[3] && !long_decimal.bits[4] && !long_decimal.bits[5]) {
    decimal->bits[0] = long_decimal.bits[0];
    decimal->bits[1] = long_decimal.bits[1];
    decimal->bits[2] = long_decimal.bits[2];
    decimal->bits[3] = long_decimal.bits[6];
    set_sign(&decimal->bits[3], sign);
  } else {
    if (get_sign(long_decimal.bits[6])) {
      error = 2;  // слишком маленькое (меньше MIN_DEC)
    } else {
      error = 1;  // слишком большое (больше MAX_DEC)
    }
  }
  return error;
}

int s21_floor_long(s21_decimal_long value, s21_decimal_long *result) {
  int sign = get_sign(value.bits[6]);
  set_sign(&value.bits[6], 0);
  int exp = (int)get_exponent(value.bits[6]);
  int error = 0;
  if (exp > 0) {
    s21_decimal_long temp_div = {{1, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long mod = {{0, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long zero = {{0, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long one = {{1, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long temp_long_dec = value;
    set_exponent(&temp_long_dec.bits[6], 0);
    for (int i = 0; i < exp; i++) {
      error = mul_10_long(&temp_div);
    }
    error = s21_div_long(temp_long_dec, temp_div, &temp_long_dec, &mod, 1);
    if (sign && !s21_is_equal_long(mod, zero)) {
      s21_add_long(temp_long_dec, one, &temp_long_dec);
    }
    *result = temp_long_dec;
  } else {
    *result = value;
  }
  set_sign(&result->bits[6], sign);
  return error;
}

int s21_round_long(s21_decimal_long value, s21_decimal_long *result) {
  int sign = get_sign(value.bits[6]);
  set_sign(&value.bits[6], 0);
  int exp = (int)get_exponent(value.bits[6]);
  int error = 0;
  if (exp > 0) {
    s21_decimal_long temp_div = {{1, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long mod = {{0, 0, 0, 0, 0, 0, 0}};
    s21_decimal_long zero_five = {{5, 0, 0, 0, 0, 0, 65536}};
    s21_decimal_long one = {{1, 0, 0, 0, 0, 0, 0}};

    s21_decimal_long temp_long_dec = value;
    set_exponent(&temp_long_dec.bits[6], 0);

    for (int i = 0; i < exp; i++) {
      error = mul_10_long(&temp_div);
    }
    error = s21_div_long(temp_long_dec, temp_div, &temp_long_dec, &mod, 1);
    set_exponent(&mod.bits[6], exp);
    if (!s21_is_less_long(mod, zero_five)) {
      error = s21_add_long(temp_long_dec, one, &temp_long_dec);
    }
    *result = temp_long_dec;
    set_sign(&result->bits[6], sign);
  } else {
    *result = value;
  }
  set_sign(&result->bits[6], sign);
  return error;
}

int s21_is_greater_long(s21_decimal_long value_1, s21_decimal_long value_2) {
  return !(s21_is_less_long(value_1, value_2) |
           s21_is_equal_long(value_1, value_2));
}

int s21_is_equal_long(s21_decimal_long value_1, s21_decimal_long value_2) {
  int result = 1;
  int sign1 = get_sign(value_1.bits[6]);
  int sign2 = get_sign(value_1.bits[6]);
  s21_reduce_long(&value_1, &value_2);
  set_sign(&value_1.bits[6], sign1);
  set_sign(&value_1.bits[6], sign2);
  for (int i = 0; i < 7 && result; i++)
    result = (value_1.bits[i] == value_2.bits[i]);
  return result;
}

int s21_negate_long(s21_decimal_long value, s21_decimal_long *result) {
  *result = value;
  result->bits[6] = value.bits[6] ^ 2147483648;
  return 0;
}

int s21_is_less_long(s21_decimal_long value_1, s21_decimal_long value_2) {
  int s1 = getbit(value_1.bits[6], 31);
  int s2 = getbit(value_2.bits[6], 31);
  int result = (s1 > s2) - (s1 == s2);
  if (result == -1) s21_reduce_long(&value_1, &value_2);
  for (int i = 6; i >= 0 && result == -1; i--)
    if (value_1.bits[i] != value_2.bits[i])
      result = (value_1.bits[i] < value_2.bits[i]) ^ s1;
  return result == -1 ? 0 : result;
}
