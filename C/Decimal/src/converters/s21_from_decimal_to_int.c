#include "converters.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  if (dst == NULL)
    flag = 1;
  else {
    if (src.bits[1] != 0 || src.bits[2] != 0) flag = 1;
    if (!flag) {
      int data = 0;
      s21_decimal integer = init_decimal();
      s21_truncate(src, &integer);
      data = integer.bits[0];
      if (s21_get_sign(src)) {
        if (data != -2147483648) data = -data;
      }
      *dst = data;
    }
  }
  return flag;
}