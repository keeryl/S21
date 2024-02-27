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