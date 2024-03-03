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
  s21_set_sign(decimal, sign);
}

int get_scale_bd(s21_bd bd) { return (bd.bits[7] & SCALE) >> 16; }

int get_scale(s21_decimal dec) { return (dec.bits[3] & SCALE) >> 16; }

void set_sign_bd(s21_bd* bd, int val) {
  bd->bits[7] <<= 1;
  bd->bits[7] >>= 1;
  bd->bits[7] |= ((unsigned)val << 31);
}

int get_sign_bd(s21_bd bd) { return (bd.bits[7] & SIGN) >> 31; }

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