#include "../s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int fields = 0;
  // Проверка на пустоту строки
  if (!s21_memcmp(str, "", (s21_strlen((char *)str)))) {
    return fields = -1;
  }
  char *p_for = (char *)format;
  char *p_str = (char *)str;
  va_list ptr;
  va_start(ptr, format);
  int count_int_symbols = 0;
  int width = 0;
  int start = 0;
  width = s21_strlen((char *)str);
  sscanf_struct sample = {0, 0, 0, 0, 0};
  while (*p_str == ' ' || *p_str == '+') p_str++;
  while (*p_for == ' ') p_for++;
  while (*p_for) {
    if (sample.flag_stop == 1) break;
    if (*p_for == '%') {
      int count_str = 0;
      count_int_symbols =
          s21_sscanf_hlL(p_for, p_str, &sample, &width, &count_str);
      while (count_int_symbols--) p_for++;
      while (count_str--) p_str++;
      start = 1;
    } else if ((s21_strchr("cspndiouxXfeEgG", *p_for) != S21_NULL) &&
               start == 1) {
      int count = s21_sscanf_specificator(p_for, p_str, str, sample, &fields,
                                          ptr, width);
      p_for++;
      while (count--) p_str++;
      sample.flag_double = sample.flag_long = sample.flag_short =
          sample.asterix = 0;
      start = 0;
    } else if (*p_for == 32 || *p_for == '\t' || *p_for == '\n') {
      while (*p_for == ' ' || *p_for == '\t' || *p_for == '\n') {
        while (*p_str == *p_for) {
          p_str++;
        }
        p_for++;
        count_int_symbols++;
      }
    } else if (*p_for != *p_str) {
      sample.flag_stop = 1;
    } else {
      p_for++;
      p_str++;
    }
  }
  va_end(ptr);
  return fields;
}