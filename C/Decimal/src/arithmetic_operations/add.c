#include "../s21_decimal.h"
#include "helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int status_code = OK;
  if (!result)
    status_code = ERROR;
  else {
    s21_bd val_1_big = convert_to_bd(value_1);
    s21_bd val_2_big = convert_to_bd(value_2);
    s21_bd res_big = init_bd();
    int val_1_s = get_sign_bd(val_1_big);
    int val_2_s = get_sign_bd(val_2_big);
    normalize_bd(&val_1_big, &val_2_big);
    int normalized_sc = get_scale_bd(val_2_big);
    if (!val_1_s && !val_2_s) {
      handle_add_bd(val_1_big, val_2_big, &res_big, normalized_sc, 0);
    } else if (val_1_s && val_2_s) {
      handle_add_bd(val_1_big, val_2_big, &res_big, normalized_sc, 1);
    } else {
      int compare_res = compare_bd(val_1_big, val_2_big);
      if (val_1_s && compare_res == 1)
        handle_sub_bd(val_1_big, val_2_big, &res_big, normalized_sc, 1);
      if (val_1_s && compare_res == 2)
        handle_sub_bd(val_2_big, val_1_big, &res_big, normalized_sc, 0);
      if (val_2_s && compare_res == 1)
        handle_sub_bd(val_1_big, val_2_big, &res_big, normalized_sc, 0);
      if (val_2_s && compare_res == 2)
        handle_sub_bd(val_2_big, val_1_big, &res_big, normalized_sc, 1);
      if (compare_res == 0)
        handle_sub_bd(val_2_big, val_1_big, &res_big, normalized_sc, 1);
    }
    status_code = handle_result(&res_big, result);
  }
  return status_code;
}

void bitwise_add_bd(s21_bd bd_1, s21_bd bd_2, s21_bd* res) {
  *res = init_bd();
  int memory = 0;
  for (int i = 0; i < 224; i++) {
    int bit_to_set = get_bit_bd(bd_1, i) + get_bit_bd(bd_2, i) + memory;
    memory = bit_to_set / 2;
    bit_to_set %= 2;
    set_bit_bd(res, i, bit_to_set);
  }
}
