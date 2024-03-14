#include "other.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status_code = 0;
  if (!result)
    status_code = 1;
  else {
    s21_decimal fraction = init_decimal();
    s21_truncate(value, result);
    int sign = get_sign(value);
    s21_sub(value, *result, &fraction);
    if (!is_zero_decimal(fraction) && sign) {
      s21_decimal one = init_decimal();
      one.bits[0] = 1;
      s21_sub(*result, one, result);
    }
    set_sign(result, sign);
  }
  return status_code;
}