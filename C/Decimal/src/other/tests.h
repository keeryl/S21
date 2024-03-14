#ifndef S21_OTHERS_TEST_H
#define S21_OTHERS_TEST_H

#include <check.h>

#include "../arithmetic_operations/helpers.h"
#include "../s21_decimal.h"
#include "other.h"

START_TEST(trun) {
  // 1482189449
  s21_decimal decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b01011000010110000110101010001001;
  // 1482189449.0390620354346331011M
  s21_decimal decimal = init_decimal();
  decimal.bits[3] = 0b00000000000100110000000000000000;
  decimal.bits[2] = 0b00101111111001000110001000111110;
  decimal.bits[1] = 0b01010111011101001000100101101100;
  decimal.bits[0] = 0b01100100000000011010101110000011;
  s21_decimal s21_res = init_decimal();
  int s21_res_status = s21_truncate(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -1482189449
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b01011000010110000110101010001001;
  // -1482189449.0390620354346331011M
  decimal = init_decimal();
  decimal.bits[3] = 0b10000000000100110000000000000000;
  decimal.bits[2] = 0b00101111111001000110001000111110;
  decimal.bits[1] = 0b01010111011101001000100101101100;
  decimal.bits[0] = 0b01100100000000011010101110000011;
  s21_res = init_decimal();
  s21_res_status = s21_truncate(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 124656
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000011110011011110000;
  // 124656
  decimal = init_decimal();
  decimal.bits[3] = 0b00000000000000000000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[0] = 0b00000000000000011110011011110000;
  s21_res = init_decimal();
  s21_res_status = s21_truncate(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -0
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // -0.000
  decimal = init_decimal();
  decimal.bits[3] = 0b10000000000000110000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[0] = 0b00000000000000000000000000000000;
  s21_res = init_decimal();
  s21_res_status = s21_truncate(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -0
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // -0.111111111111111111M
  decimal = init_decimal();
  decimal.bits[3] = 0b10000000000100100000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[1] = 0b00000001100010101011111011110111;
  decimal.bits[0] = 0b10000100011000000111000111000111;
  s21_res = init_decimal();
  s21_res_status = s21_truncate(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // NULL POINTER CHECK
  s21_res_status = s21_truncate(decimal, NULL);
  ck_assert_int_eq(s21_res_status, 1);
}
END_TEST

START_TEST(flr) {
  // 1482189449
  s21_decimal decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b01011000010110000110101010001001;
  // 1482189449.0390620354346331011M
  s21_decimal decimal = init_decimal();
  decimal.bits[3] = 0b00000000000100110000000000000000;
  decimal.bits[2] = 0b00101111111001000110001000111110;
  decimal.bits[1] = 0b01010111011101001000100101101100;
  decimal.bits[0] = 0b01100100000000011010101110000011;
  s21_decimal s21_res = init_decimal();
  int s21_res_status = s21_floor(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -1482189450
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b01011000010110000110101010001010;
  // -1482189449.0390620354346331011M
  decimal = init_decimal();
  decimal.bits[3] = 0b10000000000100110000000000000000;
  decimal.bits[2] = 0b00101111111001000110001000111110;
  decimal.bits[1] = 0b01010111011101001000100101101100;
  decimal.bits[0] = 0b01100100000000011010101110000011;
  s21_res = init_decimal();
  s21_res_status = s21_floor(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -0
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // -0.000
  decimal = init_decimal();
  decimal.bits[3] = 0b10000000000000110000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[0] = 0b00000000000000000000000000000000;
  s21_res = init_decimal();
  s21_res_status = s21_floor(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -1
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000001;
  // -0.001
  decimal = init_decimal();
  decimal.bits[3] = 0b10000000000000110000000000000000;
  decimal.bits[2] = 0b00000000000000000000000000000000;
  decimal.bits[1] = 0b00000000000000000000000000000000;
  decimal.bits[0] = 0b00000000000000000000000000000001;
  s21_res = init_decimal();
  s21_res_status = s21_floor(decimal, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // NULL POINTER CHECK
  s21_res_status = s21_floor(decimal, NULL);
  ck_assert_int_eq(s21_res_status, 1);
}
END_TEST



#endif