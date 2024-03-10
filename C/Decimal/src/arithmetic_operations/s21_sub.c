#include "../s21_decimal.h"
#include "helpers.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
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
    int compare_res = compare_bd(val_1_big, val_2_big);
    if (compare_res == 0 && ((!val_1_s && !val_2_s) || (val_1_s && val_2_s)))
      handle_sub_bd(val_2_big, val_1_big, &res_big, normalized_sc, 0);
    else if (val_1_s && val_2_s) {
      if (compare_res == 1)
        handle_sub_bd(val_1_big, val_2_big, &res_big, normalized_sc, 1);
      if (compare_res == 2)
        handle_sub_bd(val_2_big, val_1_big, &res_big, normalized_sc, 0);
    } else if (!val_1_s && !val_2_s) {
      if (compare_res == 1)
        handle_sub_bd(val_1_big, val_2_big, &res_big, normalized_sc, 0);
      if (compare_res == 2)
        handle_sub_bd(val_2_big, val_1_big, &res_big, normalized_sc, 1);
    } else {
      if (val_1_s)
        handle_add_bd(val_1_big, val_2_big, &res_big, normalized_sc, 1);
      else if (val_2_s)
        handle_add_bd(val_2_big, val_1_big, &res_big, normalized_sc, 0);
    }
    status_code = handle_result(&res_big, result);
  }
  return status_code;
}