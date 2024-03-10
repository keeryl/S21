#include "../s21_decimal.h"
#include "helpers.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status_code = OK;
  if (!result)
    status_code = ERROR;
  else {
    s21_bd val_1_big = convert_to_bd(value_1);
    s21_bd val_2_big = convert_to_bd(value_2);
    s21_bd res_big = init_bd();
    int val_1_s = get_sign_bd(val_1_big);
    int val_2_s = get_sign_bd(val_2_big);
    int result_sc = get_scale_bd(val_1_big) + get_scale_bd(val_2_big);
    if (val_1_s ^ val_2_s)
      handle_mul_bd(val_1_big, val_2_big, &res_big, result_sc, 1);
    else
      handle_mul_bd(val_1_big, val_2_big, &res_big, result_sc, 0);
    status_code = handle_result(&res_big, result);
  }
  return status_code;
}

void bitwise_mul_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res) {
  *res = init_bd();
  int higest_multiplier_bit_idx = 0;
  for (int i = 223; i >= 0; i--) {
    if (get_bit_bd(bd_2, i)) higest_multiplier_bit_idx = 1;
    if (higest_multiplier_bit_idx) {
      if (get_bit_bd(bd_2, i)) bitwise_add_bd(bd_1, *res, res);
      if (i > 0) *res = shift_left_bd(*res, 1);
    }
  }
}