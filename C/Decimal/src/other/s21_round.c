#include "other.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int status_code = 0;
  if (!result)
    status_code = 1;
  else {
    s21_decimal fraction = init_decimal();
    s21_truncate(value, result);
    int sign = s21_get_sign(value);
    int scale = s21_get_scale(value);
    s21_sub(value, *result, &fraction);
    set_scale(&fraction, scale - 1);
    if (!is_zero_decimal(fraction)) {
      s21_bd fraction_bd = convert_to_bd(fraction);
      s21_decimal one = init_decimal();
      s21_bd point_five = init_bd();
      one.bits[0] = 1;
      point_five.bits[0] = 5;
      normalize_bd(&fraction_bd, &point_five);
      int compare = compare_bd(fraction_bd, point_five);
      if (compare != 2 && sign) s21_sub(*result, one, result);
      if (compare != 2 && !sign) s21_add(*result, one, result);
      s21_set_sign(result, sign);
    }
  }
  return status_code;
}