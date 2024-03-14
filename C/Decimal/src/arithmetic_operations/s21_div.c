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
    set_sign(result, sign);
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

s21_bd bitwise_div_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res) {
  *res = init_bd();
  s21_bd remainder = bd_1;
  while (compare_bd(remainder, bd_2) != 2) {
    s21_bd temp_divisor = bd_2;
    s21_bd temp_res = init_bd();
    temp_res.bits[0] = 1u;
    while (compare_bd(remainder, shift_left_bd(temp_divisor, 1)) == 1) {
      temp_divisor = shift_left_bd(temp_divisor, 1);
      temp_res = shift_left_bd(temp_res, 1);
    }
    bitwise_sub_bd(remainder, temp_divisor, &remainder);
    bitwise_add_bd(*res, temp_res, res);
  }
  return remainder;
}

void handle_div_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res, int sign) {
  *res = init_bd();
  int bd_1_sc = get_scale_bd(bd_1);
  int bd_2_sc = get_scale_bd(bd_2);
  int scale = bd_1_sc - bd_2_sc;
  if (scale < 0) scale = 0;
  s21_bd remainder = bitwise_div_bd(bd_1, bd_2, res);
  set_scale_bd(res, scale);
  int digits_before_point = count_digits_bd(*res) - scale;
  int digits = digits_before_point + scale;
  if (digits)
    digits -= scale;
  else
    digits = 1;
  int fraction = 0;
  while (!is_zero_bd(remainder) && scale < 29 - digits) {
    scale += 1;
    fraction = 1;
    s21_bd temp = init_bd();
    mul_by_ten_bd(&remainder);
    mul_by_ten_bd(res);
    remainder = bitwise_div_bd(remainder, bd_2, &temp);
    if (scale == 28 && !digits_before_point)
      handle_bank_rounding_bd(&temp, temp);
    bitwise_add_bd(*res, temp, res);
  }
  set_scale_bd(res, scale);
  set_sign_bd(res, sign);
  if (fraction > 0) scale_down_bd(res);
}