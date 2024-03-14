#include "helpers.h"

// DEBUG HELPERS BELOW

// void print_s21_decimal(s21_decimal* dst) {
//   for (int i = 3; i >= 0; i--) {
//     printf("BIT-%d | ", i);
//     print_int_binary(dst->bits[i]);
//   }
//   printf("\n");
// }

// void print_s21_bd(s21_bd* dst) {
//   for (int i = 7; i >= 0; i--) {
//     printf("BIT-%d | ", i);
//     print_int_binary(dst->bits[i]);
//   }
//   printf("\n");
// }

// void print_int_binary(int x) {
//   for (int i = 31; i >= 0; i--) {
//     printf("%d", (x >> i) & 1);
//     if (i % 8 == 0) printf(" ");
//     if (i == 0) printf("\n");
//   }
// }

// DEBUG HELPERS END

s21_bd init_bd(void) {
  s21_bd res = {0};
  return res;
}

s21_decimal init_decimal(void) {
  s21_decimal res = {0};
  return res;
}

s21_bd convert_to_bd(s21_decimal dec) {
  s21_bd res = {0};
  for (int i = 0; i < 3; i++) res.bits[i] = dec.bits[i];
  res.bits[7] = dec.bits[3];
  return res;
}

void set_bit_bd(s21_bd* bd, int idx, int val) {
  if (val == 1) bd->bits[idx / 32] |= (1u << (idx % 32));
  if (val == 0) bd->bits[idx / 32] &= ~(1u << (idx % 32));
}

int get_bit_bd(s21_bd bd, int idx) {
  return (bd.bits[idx / 32] & 1u << (idx % 32)) >> (idx % 32);
}

void set_scale_bd(s21_bd* bd, int val) {
  int sign = get_sign_bd(*bd);
  bd->bits[7] = 0;
  bd->bits[7] |= (val << 16);
  set_sign_bd(bd, sign);
}

void set_scale(s21_decimal* decimal, int val) {
  int sign = get_sign(*decimal);
  decimal->bits[3] = 0;
  decimal->bits[3] |= (val << 16);
  set_sign(decimal, sign);
}

int get_scale_bd(s21_bd bd) { return (bd.bits[7] & SCALE) >> 16; }

int get_scale(s21_decimal dec) { return (dec.bits[3] & SCALE) >> 16; }

void set_sign_bd(s21_bd* bd, int val) {
  bd->bits[7] <<= 1;
  bd->bits[7] >>= 1;
  bd->bits[7] |= ((unsigned)val << 31);
}

void set_sign(s21_decimal* dec, int val) {
  if (val == 1) dec->bits[3] |= (1u << 31);
  if (val == 0) dec->bits[3] &= ~(1u << 31);
}

int get_sign_bd(s21_bd bd) { return (bd.bits[7] & SIGN) >> 31; }

int get_sign(s21_decimal dec) { return (dec.bits[3] & SIGN) >> 31; }

s21_bd shift_left_bd(s21_bd bd, int shift_val) {
  s21_bd res = bd;
  if (shift_val <= 31 && shift_val) {
    unsigned memory = 0;
    for (int i = 0; i < 7; i++) {
      unsigned temp = res.bits[i];
      res.bits[i] <<= shift_val;
      res.bits[i] |= memory;
      memory = temp >> (32 - shift_val);
    }
  }
  return res;
}

void normalize_bd(s21_bd* bd_1, s21_bd* bd_2) {
  while (get_scale_bd(*bd_1) != get_scale_bd(*bd_2)) {
    if (get_scale_bd(*bd_1) > get_scale_bd(*bd_2)) {
      handle_normalization_bd(bd_2);
    } else {
      handle_normalization_bd(bd_1);
    }
  }
}

void handle_normalization_bd(s21_bd* bd) {
  s21_bd temp = init_bd();
  bitwise_add_bd(shift_left_bd(*bd, 3), shift_left_bd(*bd, 1), &temp);
  set_scale_bd(&temp, get_scale_bd(*bd) + 1);
  *bd = temp;
}

int compare_bd(s21_bd bd_1, s21_bd bd_2) {
  int res = 0;
  for (int i = 223; i >= 0 && res == 0; i--) {
    int bd_1_bit = get_bit_bd(bd_1, i);
    int bd_2_bit = get_bit_bd(bd_2, i);
    if (bd_1_bit > bd_2_bit) res = 1;
    if (bd_2_bit > bd_1_bit) res = 2;
  }
  return res;
  // returns 1 if big_dec_1 is greater
  // returns 2 if big_dec_2 is greater
  // returns 0 if equal values
}

int is_zero_bd(s21_bd bd) {
  int res = 1;
  for (int i = 0; i < 7; i++)
    if (bd.bits[i] != 0) res = 0;
  return res;
}

int is_zero_decimal(s21_decimal dec) {
  int res = 1;
  for (int i = 0; i < 3; i++)
    if (dec.bits[i] != 0) res = 0;
  return res;
}

void mul_by_ten_bd(s21_bd* bd) {
  bitwise_add_bd(shift_left_bd(*bd, 3), shift_left_bd(*bd, 1), bd);
}

void scale_down_bd_if_overflow(s21_bd* bd) {
  if (!is_zero_bd(*bd)) {
    int sign = get_sign_bd(*bd);
    int scale = get_scale_bd(*bd);
    s21_bd temp_bd = *bd;
    s21_bd ten_bd = init_bd();
    ten_bd.bits[0] = 10;
    s21_bd remainder = init_bd();
    while (scale && is_overflow_in_decimal(&temp_bd)) {
      remainder = bitwise_div_bd(temp_bd, ten_bd, &temp_bd);
      scale -= 1;
    }
    handle_bank_rounding_bd(&temp_bd, remainder);
    *bd = temp_bd;
    set_scale_bd(bd, scale);
    set_sign_bd(bd, sign);
  }
}

void scale_down_bd(s21_bd* bd) {
  if (!is_zero_bd(*bd)) {
    int sign = get_sign_bd(*bd);
    int scale = get_scale_bd(*bd);
    s21_bd temp_bd = *bd;
    s21_bd ten_bd = init_bd();
    ten_bd.bits[0] = 10;
    s21_bd remainder = bitwise_div_bd(temp_bd, ten_bd, &temp_bd);
    while (scale && is_zero_bd(remainder)) {
      if (is_zero_bd(remainder)) {
        scale -= 1;
        *bd = temp_bd;
        set_scale_bd(bd, scale);
        set_sign_bd(bd, sign);
      }
      remainder = bitwise_div_bd(temp_bd, ten_bd, &temp_bd);
    }
  }
}

int handle_result(s21_bd* result_bd, s21_decimal* result) {
  int status_code = OK;
  if (is_overflow_in_decimal(result_bd)) {
    scale_down_bd_if_overflow(result_bd);
  }
  if (is_overflow_in_decimal(result_bd)) {
    if (get_sign_bd(*result_bd))
      status_code = SMALL;
    else
      status_code = LARGE;
  } else {
    convert_bd_to_decimal(result_bd, result);
  }
  return status_code;
}

void handle_bank_rounding_bd(s21_bd* res_bd, s21_bd remainder) {
  int res_sign = get_sign_bd(*res_bd);
  s21_bd zero_point_five = init_bd();
  s21_bd one_bd = init_bd();
  zero_point_five.bits[0] = 5;
  one_bd.bits[0] = 1;
  set_scale_bd(&zero_point_five, get_scale_bd(remainder));
  int compare = compare_bd(remainder, zero_point_five);
  if (compare == 1 || (!compare && get_bit_bd(*res_bd, 0)))
    handle_add_bd(*res_bd, one_bd, res_bd, 0, res_sign);
  else
    set_sign_bd(res_bd, res_sign);
}

int is_overflow_in_decimal(const s21_bd* res_bd) {
  int res = 0;
  for (int i = 3; i < 7; i++)
    if (res_bd->bits[i] != 0) res = 1;
  return res;
}

void convert_bd_to_decimal(s21_bd* result_bd, s21_decimal* result) {
  for (int i = 0; i < 3; i++) result->bits[i] = result_bd->bits[i];
  result->bits[3] = result_bd->bits[7];
}

int count_digits_bd(s21_bd bd) {
  int digits = 0;
  s21_bd ten_bd = init_bd();
  ten_bd.bits[0] = 10;
  s21_bd temp_bd = bd;
  while (!is_zero_bd(temp_bd)) {
    bitwise_div_bd(temp_bd, ten_bd, &temp_bd);
    digits += 1;
  }
  return digits;
}