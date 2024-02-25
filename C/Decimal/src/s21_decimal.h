#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

typedef struct {
  int bits[4];
} s21_decimal;

#define SCALE 0x00ff0000
#define SIGN 0x80000000

// Arithmetic Operations
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif
