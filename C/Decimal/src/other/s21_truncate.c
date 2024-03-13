#include "other.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status_code = 0;
  if (!result)
    status_code = 1;
  else {
    s21_bd val_bd = convert_to_bd(value);
    int val_bd_s = get_sign_bd(val_bd);
    int val_bd_sc = get_scale_bd(val_bd);
    s21_bd ten_bd = init_bd();
    ten_bd.bits[0] = 10;
    for (int i = 0; i < val_bd_sc; i++) {
      bitwise_div_bd(val_bd, ten_bd, &val_bd);
    }
    set_sign_bd(&val_bd, val_bd_s);
    convert_bd_to_decimal(&val_bd, result);
  }
  return status_code;
}