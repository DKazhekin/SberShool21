#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_decimal_long.h"

#define BUFF_SIZE 512

void print_decimal(s21_decimal dec);
void s21_dec_to_string(s21_decimal dec, char *str);
void set_array_from_dec(s21_decimal dec, int *result);
void s21_long_dec_to_string(s21_decimal_long ldec, char *str);
void set_array_from_long_dec(s21_decimal_long ldec, int *result);

void reduce_str(char *str_original, char *str_s21) {
  int size_str_s21 = (int)strlen(str_s21);
  int size_str_orig = (int)strlen(str_original);

  for (int i = 0; i < size_str_s21; i++) {
    if (str_s21[size_str_s21 - 1 - i] == '0') {
      str_s21[size_str_s21 - 1 - i] = '\0';
    } else if ((str_s21[size_str_s21 - 1 - i] == '.')) {
      str_s21[size_str_s21 - 1 - i] = '\0';
    } else {
      break;
    }
  }

  for (int i = 0; i < size_str_orig; i++) {
    if (str_original[size_str_orig - 1 - i] == '0') {
      str_original[size_str_orig - 1 - i] = '\0';
    } else if ((str_original[size_str_orig - 1 - i] == '.')) {
      str_original[size_str_orig - 1 - i] = '\0';
    } else {
      break;
    }
  }
}

START_TEST(s21_add_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}},
                                    {{0, 0, 0, 262144}}}};
  FILE *fp = fopen("tests/s21_add_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        s21_decimal output = {0};
        int error = s21_add(input_array[0][i], input_array[0][j], &output);

        if (!error)
          s21_dec_to_string(output, str_s21);
        else
          strcpy(str_s21, "error");

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_sub_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}},
                                    {{0, 0, 0, 262144}}}};
  FILE *fp = fopen("tests/s21_sub_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        s21_decimal output = {0};
        int error = s21_sub(input_array[0][i], input_array[0][j], &output);

        if (!error)
          s21_dec_to_string(output, str_s21);
        else
          strcpy(str_s21, "error");
        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_mul_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}},
                                    {{0, 0, 0, 262144}}}};
  FILE *fp = fopen("tests/s21_mul_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        s21_decimal output = {0};
        int error = s21_mul(input_array[0][i], input_array[0][j], &output);

        if (!error)
          s21_dec_to_string(output, str_s21);
        else
          strcpy(str_s21, "error");

        reduce_str(str_original, str_s21);
        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_div_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}}}};
  FILE *fp = fopen("tests/s21_div_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        s21_decimal output = {0};
        int error = s21_div(input_array[0][i], input_array[0][j], &output);

        if (!error)
          s21_dec_to_string(output, str_s21);
        else
          strcpy(str_s21, "error");

        reduce_str(str_original, str_s21);

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_mod_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}}}};
  FILE *fp = fopen("tests/s21_mod_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        s21_decimal output = {0};
        int error = s21_mod(input_array[0][i], input_array[0][j], &output);

        if (!error)
          s21_dec_to_string(output, str_s21);
        else
          strcpy(str_s21, "error");

        reduce_str(str_original, str_s21);
        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_less_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}}}};
  FILE *fp = fopen("tests/s21_less_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        int result = s21_is_less(input_array[0][i], input_array[0][j]);
        if (result)
          strcpy(str_s21, "True");
        else
          strcpy(str_s21, "False");

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_less_eq_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}}}};
  FILE *fp = fopen("tests/s21_less_eq_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        int result = s21_is_less_or_equal(input_array[0][i], input_array[0][j]);
        if (result)
          strcpy(str_s21, "True");
        else
          strcpy(str_s21, "False");

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_is_greater_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}}}};
  FILE *fp = fopen("tests/s21_is_greater_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        int result = s21_is_greater(input_array[0][i], input_array[0][j]);
        if (result)
          strcpy(str_s21, "True");
        else
          strcpy(str_s21, "False");

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_is_greater_or_equal_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}}}};
  FILE *fp = fopen("tests/s21_is_greater_or_equal_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        int result =
            s21_is_greater_or_equal(input_array[0][i], input_array[0][j]);
        if (result)
          strcpy(str_s21, "True");
        else
          strcpy(str_s21, "False");

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_is_equal_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}}}};
  FILE *fp = fopen("tests/s21_is_equal_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        int result = s21_is_equal(input_array[0][i], input_array[0][j]);
        if (result)
          strcpy(str_s21, "True");
        else
          strcpy(str_s21, "False");

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_is_not_equal_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}}}};
  FILE *fp = fopen("tests/s21_is_not_equal_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        fgets(str_original, sizeof(str_original), fp);
        str_original[strlen(str_original) - 1] = '\0';

        int result = s21_is_not_equal(input_array[0][i], input_array[0][j]);
        if (result)
          strcpy(str_s21, "True");
        else
          strcpy(str_s21, "False");

        ck_assert_str_eq(str_s21, str_original);
      }
    fclose(fp);
  }
}
END_TEST

START_TEST(from_float_to_decimal) {
  float input_array[] = {1.0, 0.0125, 3.14E5, -5.6E-27};

  FILE *fp = fopen("tests/s21_from_float.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 4; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      s21_decimal output = {0};
      s21_from_float_to_decimal(input_array[i], &output);
      s21_dec_to_string(output, str_s21);

      ck_assert_str_eq(str_s21, str_original);
    }
    fclose(fp);
  }
}
END_TEST

START_TEST(from_int_to_decimal) {
  int input_array[] = {0, -1, 2147483647, -2147483647};

  FILE *fp = fopen("tests/s21_from_int_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 4; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      s21_decimal output = {0};
      s21_from_int_to_decimal(input_array[i], &output);
      s21_dec_to_string(output, str_s21);

      ck_assert_str_eq(str_s21, str_original);
    }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_round_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}},
                                    {{0, 0, 0, 262144}}}};

  FILE *fp = fopen("tests/s21_round_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 9; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';

      s21_decimal output = {0};
      s21_round(input_array[0][i], &output);

      s21_dec_to_string(output, str_s21);
      ck_assert_str_eq(str_s21, str_original);
    }
    fclose(fp);
  }
}

END_TEST

START_TEST(s21_floor_test) {
  s21_decimal input_array[][19] = {
      {{{1, 0, 0, 0}},
       {{1, 0, 0, 262144}},
       {{1, 0, 0, 1835008}},
       {{1, 0, 0, 2147483648}},
       {{1, 0, 0, 2147745792}},
       {{1, 0, 0, 2149318656}},
       {{0, 65535, 0, 0}},
       {{0, 65535, 0, 262144}},
       {{0, 65535, 0, 1835008}},
       {{0, 65535, 0, 2147483648}},
       {{0, 65535, 0, 2147745792}},
       {{0, 65535, 0, 2149318656}},
       {{4294967295, 4294967295, 4294967295, 0}},
       {{4294967295, 4294967295, 4294967295, 262144}},
       {{4294967295, 4294967295, 4294967295, 1835008}},
       {{4294967295, 4294967295, 4294967295, 2147483648}},
       {{4294967295, 4294967295, 4294967295, 2147745792}},
       {{4294967295, 4294967295, 4294967295, 2149318656}},
       {{0, 0, 0, 262144}}}};

  FILE *fp = fopen("tests/s21_floor_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 19; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      s21_decimal output = {0};
      s21_floor(input_array[0][i], &output);
      s21_dec_to_string(output, str_s21);
      ck_assert_str_eq(str_s21, str_original);
    }
  }
  fclose(fp);
}
END_TEST

START_TEST(s21_negate_test) {
  s21_decimal input_array[][19] = {{{{1, 0, 0, 0}},
                                    {{1, 0, 0, 262144}},
                                    {{1, 0, 0, 2147483648}},
                                    {{1, 0, 0, 2147745792}},
                                    {{0, 65535, 0, 0}},
                                    {{0, 65535, 0, 262144}},
                                    {{0, 65535, 0, 2147483648}},
                                    {{0, 65535, 0, 2147745792}},
                                    {{0, 0, 0, 262144}}}};

  FILE *fp = fopen("tests/s21_negate_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 8; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      s21_decimal output = {0};
      s21_negate(input_array[0][i], &output);
      s21_dec_to_string(output, str_s21);
      ck_assert_str_eq(str_s21, str_original);
    }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_truncate_test) {
  s21_decimal input_array[][19] = {
      {{{1, 0, 0, 0}},
       {{1, 0, 0, 262144}},
       {{1, 0, 0, 1835008}},
       {{1, 0, 0, 2147483648}},
       {{1, 0, 0, 2147745792}},
       {{1, 0, 0, 2149318656}},
       {{0, 65535, 0, 0}},
       {{0, 65535, 0, 262144}},
       {{0, 65535, 0, 1835008}},
       {{0, 65535, 0, 2147483648}},
       {{0, 65535, 0, 2147745792}},
       {{0, 65535, 0, 2149318656}},
       {{4294967295, 4294967295, 4294967295, 0}},
       {{4294967295, 4294967295, 4294967295, 262144}},
       {{4294967295, 4294967295, 4294967295, 1835008}},
       {{4294967295, 4294967295, 4294967295, 2147483648}},
       {{4294967295, 4294967295, 4294967295, 2147745792}},
       {{4294967295, 4294967295, 4294967295, 2149318656}},
       {{0, 0, 0, 262144}}}};

  FILE *fp = fopen("tests/s21_truncate_data.txt", "r");
  if (fp) {
    char str_original[1024];
    char str_s21[1024];

    for (int i = 0; i < 19; i++) {
      fgets(str_original, sizeof(str_original), fp);
      str_original[strlen(str_original) - 1] = '\0';
      s21_decimal output = {0};
      s21_truncate(input_array[0][i], &output);
      s21_dec_to_string(output, str_s21);

      ck_assert_str_eq(str_s21, str_original);
    }
    fclose(fp);
  }
}
END_TEST

START_TEST(s21_decimal_to_float_test) {
  s21_decimal input_array[][19] = {
      {{{1, 0, 0, 0}},
       {{1, 0, 0, 262144}},
       {{1, 0, 0, 1835008}},
       {{1, 0, 0, 2147483648}},
       {{1, 0, 0, 2147745792}},
       {{1, 0, 0, 2149318656}},
       {{0, 65535, 0, 0}},
       {{0, 65535, 0, 262144}},
       {{0, 65535, 0, 1835008}},
       {{0, 65535, 0, 2147483648}},
       {{0, 65535, 0, 2147745792}},
       {{0, 65535, 0, 2149318656}},
       {{4294967295, 4294967295, 4294967295, 0}},
       {{4294967295, 4294967295, 4294967295, 262144}},
       {{4294967295, 4294967295, 4294967295, 1835008}},
       {{4294967295, 4294967295, 4294967295, 2147483648}},
       {{4294967295, 4294967295, 4294967295, 2147745792}},
       {{4294967295, 4294967295, 4294967295, 2149318656}},
       {{0, 0, 0, 262144}}}};

  float output_array[19] = {1,
                            0.0001,
                            1E-28,
                            -1,
                            -0.0001,
                            -1E-28,
                            2.814707E+14,
                            2.814707E+10,
                            2.814707E-14,
                            -2.814707E+14,
                            -2.814707E+10,
                            -2.814707E-14,
                            7.922816E+28,
                            7.922816E+24,
                            7.922816,
                            -7.922816E+28,
                            -7.922816E+24,
                            -7.922816,
                            0};
  float current = 0;
  int error = -1;
  for (int i = 0; i < 18; i++) {
    error = s21_from_decimal_to_float(input_array[0][i], &current);
    ck_assert_float_lt(fabs(current - output_array[i]) / output_array[i],
                       1e-07);
    ck_assert_int_eq(error, 0);
  }
  error = s21_from_decimal_to_float(input_array[0][18], &current);
  ck_assert_float_lt(fabs(current), 1e-07);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_decimal_to_int_test) {
  s21_decimal input_array[][15] = {
      {{{1, 0, 0, 0}},
       {{1, 0, 0, 262144}},
       {{1, 0, 0, 1835008}},
       {{1, 0, 0, 2147483648}},
       {{1, 0, 0, 2147745792}},
       {{1, 0, 0, 2149318656}},
       {{2147483647, 0, 0, 0}},
       {{2147483647, 0, 0, 262144}},
       {{2147483647, 0, 1835008}},
       {{2147483647, 0, 0, 2147483648}},
       {{2147483647, 0, 0, 2147745792}},
       {{2147483647, 0, 0, 2149318656}},
       {{4294967295, 4294967295, 4294967295, 0}},
       {{4294967295, 4294967295, 4294967295, 2149318656}},
       {{0, 0, 0, 262144}}}};

  int output_array[15] = {1,       0,          0,      -1,   0,
                          0,       2147483647, 214748, 6666, -2147483647,
                          -214748, 0,          6666,   -7,   0};
  int error_array[15] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0};
  int current = 0;
  int error = -1;
  for (int i = 0; i < 15; i++) {
    error = s21_from_decimal_to_int(input_array[0][i], &current);
    ck_assert_int_eq(error, error_array[i]);
    if (!error) ck_assert_int_eq(current, output_array[i]);
  }
}
END_TEST

/* ===== TEST SUITE 1 of 26 ===== */
Suite *test_suite_truncate() {
  Suite *s = suite_create("test_suite_s21_truncate");
  TCase *tc = tcase_create("test_case_s21_truncate");
  tcase_add_test(tc, s21_truncate_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_decimal_to_float() {
  Suite *s = suite_create("test_suite_s21_decimal_to_float");
  TCase *tc = tcase_create("test_case_s21_decimal_to_float");
  tcase_add_test(tc, s21_decimal_to_float_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_decimal_to_int() {
  Suite *s = suite_create("test_suite_s21_decimal_to_int");
  TCase *tc = tcase_create("test_case_s21_decimal_to_int");
  tcase_add_test(tc, s21_decimal_to_int_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_negate() {
  Suite *s = suite_create("test_suite_s21_negate");
  TCase *tc = tcase_create("test_case_s21_negate");
  tcase_add_test(tc, s21_negate_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_floor() {
  Suite *s = suite_create("test_suite_s21_floor");
  TCase *tc = tcase_create("test_case_s21_floor");
  tcase_add_test(tc, s21_floor_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_add_test() {
  Suite *s = suite_create("test_suite_s21_decimal_add");
  TCase *tc = tcase_create("test_case_s21_decimal_add");
  tcase_add_test(tc, s21_add_test);
  suite_add_tcase(s, tc);
  return s;
}

/* ===== TEST SUITE 1 of 26 ===== */
Suite *test_suite_s21_sub_test() {
  Suite *s = suite_create("test_suite_s21_decimal_sub");
  TCase *tc = tcase_create("test_case_s21_decimal_sub");
  tcase_add_test(tc, s21_sub_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_mul_test() {
  Suite *s = suite_create("test_suite_s21_decimal_mul");
  TCase *tc = tcase_create("test_case_s21_decimal_mul");
  tcase_add_test(tc, s21_mul_test);
  suite_add_tcase(s, tc);
  return s;
}
Suite *test_suite_s21_div_test() {
  Suite *s = suite_create("test_suite_s21_decimal_div");
  TCase *tc = tcase_create("test_case_s21_decimal_div");
  tcase_add_test(tc, s21_div_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_mod_test() {
  Suite *s = suite_create("test_suite_s21_decimal_mod");
  TCase *tc = tcase_create("test_case_s21_decimal_mod");
  tcase_add_test(tc, s21_mod_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_less_test() {
  Suite *s = suite_create("test_suite_s21_decimal_less");
  TCase *tc = tcase_create("test_case_s21_decimal_less");
  tcase_add_test(tc, s21_less_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_less_eq_test() {
  Suite *s = suite_create("test_suite_s21_decimal_less_eq");
  TCase *tc = tcase_create("test_case_s21_decimal_less_eq");
  tcase_add_test(tc, s21_less_eq_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_is_greater() {
  Suite *s = suite_create("test_suite_s21_is_greater");
  TCase *tc = tcase_create("test_case_s21_is_greater");
  tcase_add_test(tc, s21_is_greater_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_is_greater_or_equal() {
  Suite *s = suite_create("test_suite_s21_is_greater_or_equal");
  TCase *tc = tcase_create("test_case_s21_is_greater_or_equal");
  tcase_add_test(tc, s21_is_greater_or_equal_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_is_equal() {
  Suite *s = suite_create("test_suite_s21_is_equal");
  TCase *tc = tcase_create("test_case_s21_is_equal");
  tcase_add_test(tc, s21_is_equal_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_s21_is_not_equal() {
  Suite *s = suite_create("test_suite_s21_is_not_equal");
  TCase *tc = tcase_create("test_case_s21_is_not_equal");
  tcase_add_test(tc, s21_is_not_equal_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_from_float_to_decimal() {
  Suite *s = suite_create("test_suite_s21_from_float_to_decimal");
  TCase *tc = tcase_create("test_case_s21_from_float_to_decimal");
  tcase_add_test(tc, from_float_to_decimal);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_from_int_to_decimal() {
  Suite *s = suite_create("test_suite_s21_from_int_to_decimal");
  TCase *tc = tcase_create("test_case_s21_from_int_to_decimal");
  tcase_add_test(tc, from_int_to_decimal);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_round() {
  Suite *s = suite_create("test_suite_s21_round");
  TCase *tc = tcase_create("test_case_s21_round");
  tcase_add_test(tc, s21_round_test);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int no_failed = 0;
  Suite *test_suites[] = {test_suite_s21_add_test(),
                          test_suite_s21_sub_test(),
                          test_suite_s21_mul_test(),
                          test_suite_s21_div_test(),
                          test_suite_s21_mod_test(),
                          test_suite_s21_less_test(),
                          test_suite_s21_less_eq_test(),
                          test_suite_s21_less_eq_test(),
                          test_suite_s21_is_greater(),
                          test_suite_s21_is_greater_or_equal(),
                          test_suite_s21_is_equal(),
                          test_suite_s21_is_not_equal(),
                          test_suite_from_float_to_decimal(),
                          test_suite_from_int_to_decimal(),
                          test_suite_round(),
                          test_suite_floor(),
                          test_suite_negate(),
                          test_suite_truncate(),
                          test_suite_decimal_to_float(),
                          test_suite_decimal_to_int(),

                          NULL};
  for (Suite **suite = test_suites; *suite != NULL; suite++) {
    SRunner *runner = srunner_create(*suite);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  return no_failed;
}

void set_array_from_long_dec(s21_decimal_long ldec, int *result) {
  int fract[192] = {-1};
  for (int i = 0; i < 192; i++) fract[i] = getbit(ldec.bits[i / 32], i % 32);
  int s[58] = {0};
  s[0] = 1;
  for (int i = 0; i < 192; i++) {
    if (fract[i]) {
      int vu = 0;
      for (int j = 0; j < 58; j++) {
        result[j] += s[j];
        result[j] += vu;
        if (result[j] > 9) {
          vu = 1;
          result[j] -= 10;
        } else {
          vu = 0;
        }
      }
    }
    int vu = 0;
    for (int j = 0; j < 58; j++) {
      s[j] *= 2;
      s[j] += vu;
      if (s[j] > 9) {
        vu = 1;
        s[j] -= 10;
      } else {
        vu = 0;
      }
    }
  }
}

void s21_long_dec_to_string(s21_decimal_long ldec, char *str) {
  char *c = str;
  if (get_sign(ldec.bits[6])) {
    *c = '-';
    c++;
  }
  int ex = (int)get_exponent(ldec.bits[6]);
  int array_of_int[58] = {0};
  set_array_from_long_dec(ldec, array_of_int);
  int flag = 0;
  for (int j = 57; j >= 0; j--) {
    if (flag || array_of_int[j] || j == ex) {
      *c = (char)(array_of_int[j]) + 48;
      c++;
      flag = 1;
      if (j == ex && j) {
        *c = '.';
        c++;
      }
    }
  }
  if (*str == '-' && c == str + 1 && *c == '0') {
    *str = 0;
    c = str + 1;
  }
  *c = '\0';
}

void set_array_from_dec(s21_decimal dec, int *result) {
  int fract[96] = {-1};
  for (int i = 0; i < 96; i++) fract[i] = getbit(dec.bits[i / 32], i % 32);
  int s[29] = {0};
  s[0] = 1;
  for (int i = 0; i < 96; i++) {
    if (fract[i]) {
      int vu = 0;
      for (int j = 0; j < 29; j++) {
        result[j] += s[j];
        result[j] += vu;
        if (result[j] > 9) {
          vu = 1;
          result[j] -= 10;
        } else {
          vu = 0;
        }
      }
    }
    int vu = 0;
    for (int j = 0; j < 29; j++) {
      s[j] *= 2;
      s[j] += vu;
      if (s[j] > 9) {
        vu = 1;
        s[j] -= 10;
      } else {
        vu = 0;
      }
    }
  }
}

void s21_dec_to_string(s21_decimal dec, char *str) {
  char *c = str;
  if (get_sign(dec.bits[3])) {
    *c = '-';
    c++;
  }
  int ex = (int)get_exponent(dec.bits[3]);
  int array_of_int[29] = {0};
  set_array_from_dec(dec, array_of_int);
  int flag = 0;
  for (int j = 28; j >= 0; j--) {
    if (flag || array_of_int[j] || j == ex) {
      *c = (char)(array_of_int[j]) + 48;
      c++;
      flag = 1;
      if (j == ex && j) {
        *c = '.';
        c++;
      }
    }
  }
  if (*str == '-' && c == str + 1 && *c == '0') {
    *str = 0;
    c = str + 1;
  }
  *c = '\0';
}

void print_decimal(s21_decimal dec) {
  char output_str[31];
  s21_dec_to_string(dec, output_str);
  printf("%s\n", output_str);
}
