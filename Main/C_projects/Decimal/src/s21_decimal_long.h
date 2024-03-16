#ifndef C5_S21_DECIMAL_0_SRC_S21_DECIMAL_LONG_H_
#define C5_S21_DECIMAL_0_SRC_S21_DECIMAL_LONG_H_

typedef struct {
  unsigned int bits[7];
} s21_decimal_long;

void get_mod_from_longdec(int exp_long, s21_decimal_long *long_decimal);

void div10_with_round(s21_decimal_long *long_decimal);
void bank_round(s21_decimal_long mod, s21_decimal_long *temp_long_dec,
                s21_decimal_long *long_decimal);

int s21_floor_long(s21_decimal_long value, s21_decimal_long *result);
int s21_round_long(s21_decimal_long value, s21_decimal_long *result);

int s21_reduce_long(s21_decimal_long *value_1, s21_decimal_long *value_2);

void reset_decimal_long(s21_decimal_long *result);

void start_adding_long(s21_decimal_long *value_1, s21_decimal_long *value_2,
                       s21_decimal_long *result, int i, int *flag);

int s21_add_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result);

int s21_mul_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result);

int shift_left_by_1_long(s21_decimal_long *value);

void set_for_shift_long(s21_decimal_long *value, int i, int flag, int error);

int s21_sub_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result);

void start_subbing_long(s21_decimal_long *value_1, s21_decimal_long *value_2,
                        s21_decimal_long *result, int i);

int s21_div_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result, s21_decimal_long *remainder,
                 int flag_mod);

int s21_mod_long(s21_decimal_long value_1, s21_decimal_long value_2,
                 s21_decimal_long *result);

int s21_is_less_long(s21_decimal_long value_1, s21_decimal_long value_2);
int s21_is_greater_long(s21_decimal_long value_1, s21_decimal_long value_2);
int s21_is_equal_long(s21_decimal_long value_1, s21_decimal_long value_2);
int s21_negate_long(s21_decimal_long value, s21_decimal_long *result);

int shift_right_by_1_long(s21_decimal_long *value);
void set_for_shift_right_long(s21_decimal_long *value, int i, int flag,
                              int error);
int mul_10_long(s21_decimal_long *value);
void no_zero(s21_decimal_long *value);

#endif  // C5_S21_DECIMAL_0_SRC_S21_DECIMAL_LONG_H_
