#include "../s21_decimal.h"
#include "helpers.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status_code = OK;
  if (!result)
    status_code = ERROR;
  else if (is_zero_decimal(value_2))
    status_code = DIVISION_ZERO;
  else if (is_zero_decimal(value_1)) {
    *result = value_1;
    int scale = get_scale(value_1) - get_scale(value_2);
    int sign = 0;
    if (get_sign(value_1) ^ get_sign(value_2)) sign = 1;
    s21_set_sign(result, sign);
    if (scale > 0)
      set_scale(result, scale);
    else
      set_scale(result, 0);
  } else {
    s21_bd val_1_big = convert_to_bd(value_1);
    s21_bd val_2_big = convert_to_bd(value_2);
    s21_bd res_big = init_bd();
    int val_1_s = get_sign_bd(val_1_big);
    int val_2_s = get_sign_bd(val_2_big);
    normalize_bd(&val_1_big, &val_2_big);
    if (val_1_s ^ val_2_s)
      handle_div_bd(val_1_big, val_2_big, &res_big, 1);
    else
      handle_div_bd(val_1_big, val_2_big, &res_big, 0);
    status_code = handle_result(&res_big, result);
  }
  return status_code;
}