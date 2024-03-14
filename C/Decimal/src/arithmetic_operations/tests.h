#ifndef S21_ARITHMETIC_TEST_H
#define S21_ARITHMETIC_TEST_H

#include <check.h>

#include "../s21_decimal.h"
#include "helpers.h"

//********************** ADDITION **********************//

START_TEST(addn) {
  int j = -200;
  for (int i = -100; i <= 100; i++) {
    s21_decimal dec_1 = init_decimal();
    s21_decimal dec_2 = init_decimal();
    s21_decimal s21_res = init_decimal();
    dec_1.bits[0] = abs(i);
    dec_2.bits[0] = abs(j);
    if (i < 0) set_sign(&dec_1, 1);
    if (j < 0) set_sign(&dec_2, 1);
    int standard_res = i + j;
    int s21_res_status = s21_add(dec_1, dec_2, &s21_res);
    int sign = 0;
    if (standard_res < 0) sign = 1;
    ck_assert_int_eq(s21_res.bits[0], abs(standard_res));
    ck_assert_int_eq(s21_res_status, 0);
    ck_assert_int_eq(get_sign(s21_res), sign);
    j += 2;
  }
  j = 200;
  for (int i = -100; i <= 100; i++) {
    s21_decimal dec_1 = init_decimal();
    s21_decimal dec_2 = init_decimal();
    s21_decimal s21_res = init_decimal();
    dec_1.bits[0] = abs(i);
    dec_2.bits[0] = abs(j);
    if (i < 0) set_sign(&dec_1, 1);
    if (j < 0) set_sign(&dec_2, 1);
    int standard_res = i + j;
    int s21_res_status = s21_add(dec_1, dec_2, &s21_res);
    int sign = 0;
    if (standard_res < 0) sign = 1;
    ck_assert_int_eq(s21_res.bits[0], abs(standard_res));
    ck_assert_int_eq(s21_res_status, 0);
    ck_assert_int_eq(get_sign(s21_res), sign);
    j -= 2;
  }
  s21_decimal decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000010111;
  decimal_res.bits[0] = 0b01001000011101101110100000000000;
  s21_decimal decimal_5M = init_decimal();  // 50000000000M;
  decimal_5M.bits[3] = 0b00000000000000000000000000000000;
  decimal_5M.bits[2] = 0b00000000000000000000000000000000;
  decimal_5M.bits[1] = 0b00000000000000000000000000001011;
  decimal_5M.bits[0] = 0b10100100001110110111010000000000;
  s21_decimal decimal_2 = decimal_5M;
  s21_decimal s21_res = init_decimal();
  int s21_res_status = s21_add(decimal_5M, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);
  s21_decimal max_decimal = init_decimal();
  max_decimal.bits[3] = 0b00000000000000000000000000000000;
  max_decimal.bits[2] = 0b11111111111111111111111111111111;
  max_decimal.bits[1] = 0b11111111111111111111111111111111;
  max_decimal.bits[0] = 0b11111111111111111111111111111111;
  decimal_2 = init_decimal();
  decimal_2.bits[0] = 1;
  s21_res = init_decimal();
  s21_res_status = s21_add(max_decimal, decimal_2, &s21_res);
  // OVERFLOW LARGE STATUS (1)
  ck_assert_int_eq(s21_res_status, 1);

  // 31601479889.797420472364M
  decimal_res.bits[3] = 0b00000000000010010000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000101000010111100001111;
  decimal_res.bits[0] = 0b10011000000001100111101111011101;
  // 5567.879789789M;
  s21_decimal decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000010010000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000010100010000;
  decimal_1.bits[0] = 0b01011111011111110011110011011101;
  // 5675675.676M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000110000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000001;
  decimal_2.bits[0] = 0b01010010010010111111000000011100;
  s21_res = init_decimal();
  s21_res_status = s21_add(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -5670107.796210211
  decimal_res.bits[3] = 0b10000000000010010000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000101000010010011101110;
  decimal_res.bits[0] = 0b11011001000010000000001000100011;
  // -5675675.676M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b10000000000000110000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000001;
  decimal_1.bits[0] = 0b01010010010010111111000000011100;
  // 5567.879789789M;
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000010010000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000010100010000;
  decimal_2.bits[0] = 0b01011111011111110011110011011101;
  s21_res = init_decimal();
  s21_res_status = s21_add(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // 0
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000000000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000000000;
  // 0
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000000000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000000000000;
  s21_res = init_decimal();
  s21_res_status = s21_add(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 5670107.796210211
  decimal_res.bits[3] = 0b00000000000010010000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000101000010010011101110;
  decimal_res.bits[0] = 0b11011001000010000000001000100011;
  // 5675675.676M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000110000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000001;
  decimal_1.bits[0] = 0b01010010010010111111000000011100;
  // -5567.879789789M;
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000010010000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000010100010000;
  decimal_2.bits[0] = 0b01011111011111110011110011011101;
  s21_res = init_decimal();
  s21_res_status = s21_add(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0.000000000M
  decimal_res.bits[3] = 0b10000000000010010000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // 5567.879789789M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000010010000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000010100010000;
  decimal_1.bits[0] = 0b01011111011111110011110011011101;
  // -5567.879789789M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000010010000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000010100010000;
  decimal_2.bits[0] = 0b01011111011111110011110011011101;
  s21_res = init_decimal();
  s21_res_status = s21_add(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 79228162514264337593543950334M
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[0] = 0b11111111111111111111111111111110;
  // 79228162514264337593543950334M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000000000000000000000;
  decimal_1.bits[2] = 0b11111111111111111111111111111111;
  decimal_1.bits[1] = 0b11111111111111111111111111111111;
  decimal_1.bits[0] = 0b11111111111111111111111111111110;
  // 0.5M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000010000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000000000101;
  s21_res = init_decimal();
  s21_res_status = s21_add(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 79228162514264337593543950334M
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[0] = 0b11111111111111111111111111111110;
  // 79228162514264337593543950333M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000000000000000000000;
  decimal_1.bits[2] = 0b11111111111111111111111111111111;
  decimal_1.bits[1] = 0b11111111111111111111111111111111;
  decimal_1.bits[0] = 0b11111111111111111111111111111101;
  // 0.5M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000010000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000000000101;
  s21_res = init_decimal();
  s21_res_status = s21_add(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // NULL RESULT POINTER CHECK
  s21_res_status = s21_add(decimal_1, decimal_2, NULL);
  ck_assert_int_eq(s21_res_status, 4);
}
END_TEST

//********************** SUBSTRACTION **********************//

START_TEST(subn) {
  s21_decimal decimal_max = init_decimal();  // MAX DECIMAL
  decimal_max.bits[3] = 0b00000000000000000000000000000000;
  decimal_max.bits[2] = 0b11111111111111111111111111111111;
  decimal_max.bits[1] = 0b11111111111111111111111111111111;
  decimal_max.bits[0] = 0b11111111111111111111111111111111;

  int j = -200;
  for (int i = -100; i <= 100; i++) {
    s21_decimal dec_1 = init_decimal();
    s21_decimal dec_2 = init_decimal();
    s21_decimal s21_res = init_decimal();
    dec_1.bits[0] = abs(i);
    dec_2.bits[0] = abs(j);
    if (i < 0) set_sign(&dec_1, 1);
    if (j < 0) set_sign(&dec_2, 1);
    int standard_res = i - j;
    int s21_res_status = s21_sub(dec_1, dec_2, &s21_res);
    int sign = 0;
    if (standard_res < 0) sign = 1;
    ck_assert_int_eq(s21_res.bits[0], abs(standard_res));
    ck_assert_int_eq(s21_res_status, 0);
    ck_assert_int_eq(get_sign(s21_res), sign);
    j += 2;
  }
  j = 200;

  for (int i = -100; i <= 100; i++) {
    s21_decimal dec_1 = init_decimal();
    s21_decimal dec_2 = init_decimal();
    s21_decimal s21_res = init_decimal();
    dec_1.bits[0] = abs(i);
    dec_2.bits[0] = abs(j);
    if (i < 0) set_sign(&dec_1, 1);
    if (j < 0) set_sign(&dec_2, 1);
    int standard_res = i - j;
    int s21_res_status = s21_sub(dec_1, dec_2, &s21_res);
    int sign = 0;
    if (standard_res < 0) sign = 1;
    ck_assert_int_eq(s21_res.bits[0], abs(standard_res));
    ck_assert_int_eq(s21_res_status, 0);
    ck_assert_int_eq(get_sign(s21_res), sign);
    j -= 2;
  }

  s21_decimal decimal_res = init_decimal();
  decimal_res.bits[0] = 0b11111111111111111111111111111110;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal max_decimal = init_decimal();
  max_decimal.bits[0] = 0b11111111111111111111111111111111;
  max_decimal.bits[1] = 0b11111111111111111111111111111111;
  max_decimal.bits[2] = 0b11111111111111111111111111111111;
  max_decimal.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal s21_val1 = max_decimal;
  s21_decimal s21_val2 = init_decimal();
  s21_val2.bits[0] = 0b00000000000000000000000000000001;
  s21_decimal s21_res = init_decimal();
  int s21_res_status = s21_sub(s21_val1, s21_val2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  decimal_res.bits[0] = 0b11111111111111111111111111111111;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  s21_val2.bits[0] = 4;
  set_scale(&s21_val2, 1);
  s21_res = init_decimal();
  s21_res_status = s21_sub(s21_val1, s21_val2, &s21_res);
  for (int i = 0; i < 4; i++) {
    // CHECK DECIMAL_MAX - 0.4M
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  decimal_res.bits[0] = 0b11111111111111111111111111111110;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  s21_val2.bits[0] = 6;
  set_scale(&s21_val2, 1);
  s21_res = init_decimal();
  s21_res_status = s21_sub(decimal_max, s21_val2, &s21_res);
  for (int i = 0; i < 4; i++) {
    // CHECK DECIMAL_MAX - 0.6M
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  decimal_res.bits[0] = 0b11111111111111111111111111111110;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  s21_val2.bits[0] = 5;
  set_scale(&s21_val2, 1);
  s21_res = init_decimal();
  s21_res_status = s21_sub(decimal_max, s21_val2, &s21_res);
  for (int i = 0; i < 4; i++) {
    // CHECK DECIMAL_MAX - 0.5M
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  decimal_res.bits[0] = 0b11111111111111111111111111111111;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  s21_val2 = init_decimal();
  s21_val2.bits[0] = 1;
  s21_res = init_decimal();
  s21_res_status = s21_sub(decimal_res, s21_val2, &s21_res);
  // OVERFLOW - SMALL STATUS (2)
  ck_assert_int_eq(s21_res_status, 2);

  // -79228162514264337593543950334M max decimal
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b11111111111111111111111111111111;
  decimal_res.bits[1] = 0b11111111111111111111111111111111;
  decimal_res.bits[0] = 0b11111111111111111111111111111110;
  // -79228162514264337593543950335M
  s21_decimal decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b10000000000000000000000000000000;
  decimal_1.bits[2] = 0b11111111111111111111111111111111;
  decimal_1.bits[1] = 0b11111111111111111111111111111111;
  decimal_1.bits[0] = 0b11111111111111111111111111111111;
  // -1M
  s21_decimal decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000000000000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000000000001;
  s21_res = init_decimal();
  s21_res_status = s21_sub(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // NULL RESULT POINTER CHECK
  decimal_1 = init_decimal();
  decimal_2 = init_decimal();
  s21_res = init_decimal();
  s21_res_status = s21_sub(decimal_1, decimal_2, NULL);
  ck_assert_int_eq(s21_res_status, 4);
}
END_TEST

//********************** MULTIPLICATION **********************//

START_TEST(muln) {
  int j = -200;
  for (int i = -100; i <= 100; i++) {
    s21_decimal dec_1 = init_decimal();
    s21_decimal dec_2 = init_decimal();
    s21_decimal s21_res = init_decimal();
    dec_1.bits[0] = abs(i);
    dec_2.bits[0] = abs(j);
    if (i < 0) set_sign(&dec_1, 1);
    if (j < 0) set_sign(&dec_2, 1);
    int standard_res = i * j;
    int s21_res_status = s21_mul(dec_1, dec_2, &s21_res);
    int sign = 0;
    if (standard_res < 0) sign = 1;
    ck_assert_int_eq(s21_res.bits[0], abs(standard_res));
    ck_assert_int_eq(s21_res_status, 0);
    ck_assert_int_eq(get_sign(s21_res), sign);
    j += 2;
  }
  j = 200;
  for (int i = -100; i <= 100; i++) {
    s21_decimal dec_1 = init_decimal();
    s21_decimal dec_2 = init_decimal();
    s21_decimal s21_res = init_decimal();
    dec_1.bits[0] = abs(i);
    dec_2.bits[0] = abs(j);
    if (i < 0) set_sign(&dec_1, 1);
    if (j < 0) set_sign(&dec_2, 1);
    int standard_res = i * j;
    int s21_res_status = s21_mul(dec_1, dec_2, &s21_res);
    int sign = 0;
    if (standard_res < 0) sign = 1;
    ck_assert_int_eq(s21_res.bits[0], abs(standard_res));
    ck_assert_int_eq(s21_res_status, 0);
    ck_assert_int_eq(get_sign(s21_res), sign);
    j -= 2;
  }

  s21_decimal decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000010000111;
  decimal_res.bits[1] = 0b10000110011110000011001001101110;
  decimal_res.bits[0] = 0b10101100100100000000000000000000;
  s21_decimal decimal_5M = init_decimal();  // 50000000000M;
  decimal_5M.bits[3] = 0b00000000000000000000000000000000;
  decimal_5M.bits[2] = 0b00000000000000000000000000000000;
  decimal_5M.bits[1] = 0b00000000000000000000000000001011;
  decimal_5M.bits[0] = 0b10100100001110110111010000000000;
  s21_decimal decimal_2 = decimal_5M;
  s21_decimal s21_res = init_decimal();
  int s21_res_status = s21_mul(decimal_5M, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 31601479889.797420472364M
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000011000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000011010110001;
  decimal_res.bits[1] = 0b00011110101000011101111111110100;
  decimal_res.bits[0] = 0b01011001101110001101100000101100;
  // 5567.879789789M;
  s21_decimal decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000010010000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000010100010000;
  decimal_1.bits[0] = 0b01011111011111110011110011011101;
  // 5675675.676M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000110000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000001;
  decimal_2.bits[0] = 0b01010010010010111111000000011100;
  s21_res = init_decimal();
  s21_res_status = s21_mul(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -87932972382998450874926.08618M
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000001010000000000000000;
  decimal_res.bits[2] = 0b00011100011010011010010100011110;
  decimal_res.bits[1] = 0b01110100001010101000011100011000;
  decimal_res.bits[0] = 0b10010111001111001001001001101010;
  // -12365767456475664586545.645645M;
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b10000000000001100000000000000000;
  decimal_1.bits[2] = 0b00100111111101001011100100011101;
  decimal_1.bits[1] = 0b00001001101111110010101111101101;
  decimal_1.bits[0] = 0b01110001110010010100100001001101;
  // 7.111M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000110000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000001101111000111;
  s21_res = init_decimal();
  s21_res_status = s21_mul(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -152912204787632627264781.93755
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000001010000000000000000;
  decimal_res.bits[2] = 0b00110001011010001001100111100011;
  decimal_res.bits[1] = 0b00100110110010001001011010010101;
  decimal_res.bits[0] = 0b01011011001111110110010001011011;
  // 12365767456475664586545.645645M;
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000001100000000000000000;
  decimal_1.bits[2] = 0b00100111111101001011100100011101;
  decimal_1.bits[1] = 0b00001001101111110010101111101101;
  decimal_1.bits[0] = 0b01110001110010010100100001001101;
  // -12.365767456475664586545645645M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000110110000000000000000;
  decimal_2.bits[2] = 0b00100111111101001011100100011101;
  decimal_2.bits[1] = 0b00001001101111110010101111101101;
  decimal_2.bits[0] = 0b01110001110010010100100001001101;
  s21_res = init_decimal();
  s21_res_status = s21_mul(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // NULL RESULT POINTER CHECK
  decimal_1 = init_decimal();
  decimal_2 = init_decimal();
  s21_res = init_decimal();
  s21_res_status = s21_mul(decimal_1, decimal_2, NULL);
  ck_assert_int_eq(s21_res_status, 4);
}
END_TEST

//********************** DIVISION **********************//

START_TEST(divn) {
  // 1482189449.0390620354346331011M scale 19 (29 digits)
  s21_decimal decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000100110000000000000000;
  decimal_res.bits[2] = 0b00101111111001000110001000111110;
  decimal_res.bits[1] = 0b01010111011101001000100101101100;
  decimal_res.bits[0] = 0b01100100000000011010101110000011;
  // 79228162514264337593543950335M max decimal
  s21_decimal s21_decimal_max = init_decimal();
  s21_decimal_max.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal_max.bits[2] = 0b11111111111111111111111111111111;
  s21_decimal_max.bits[1] = 0b11111111111111111111111111111111;
  s21_decimal_max.bits[0] = 0b11111111111111111111111111111111;
  // 53453465456544574574M
  s21_decimal decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000000000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000010;
  decimal_2.bits[1] = 0b11100101110100001101101110011111;
  decimal_2.bits[0] = 0b11000110111100111110110001101110;
  s21_decimal s21_res = init_decimal();
  int s21_res_status = s21_div(s21_decimal_max, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 3.6132173913043478260869565217M scale 28 (29 digits)
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000111000000000000000000;
  decimal_res.bits[2] = 0b01110100101111111101010101110000;
  decimal_res.bits[1] = 0b10101000010001000010111111000110;
  decimal_res.bits[0] = 0b10001000010110010000101100100001;
  // 124.656
  s21_decimal decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000110000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000011110011011110000;
  // 34.5
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000010000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000101011001;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // -10000.00001035841237360772639M scale 23 (28 total)
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000101110000000000000000;
  decimal_res.bits[2] = 0b00000011001110110010111000111100;
  decimal_res.bits[1] = 0b10101110001100001000110001011010;
  decimal_res.bits[0] = 0b11101100100101110000011000011111;
  // -5567445654564.879789789656M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b10000000000011000000000000000000;
  decimal_1.bits[2] = 0b00000000000001001001101011110011;
  decimal_1.bits[1] = 0b11010101011011001111001101111000;
  decimal_1.bits[0] = 0b01111000100001010001000111011000;
  // 556744564.879789
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000001100000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000011111101001011011;
  decimal_2.bits[0] = 0b00110010000001010011000110101101;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0.2678571428571428571428571429M scale 28 (29 total)
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000111000000000000000000;
  decimal_res.bits[2] = 0b00001000101001111010100110010000;
  decimal_res.bits[1] = 0b00011001110010011110100111000111;
  decimal_res.bits[0] = 0b10110110100100100100100100100101;
  // -15M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b10000000000000000000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000001111;
  // -56M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000000000000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000000111000;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0.00M
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000100000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // 0.00M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000100000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000000000;
  // 1M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000000000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000000000001;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0.0M
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000010000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // 0.00M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000100000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000000000;
  // 1.1M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000010000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000000000001011;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0M
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // 0.00M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000100000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000000000;
  // 1.111M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000000110000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000010001010111;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0M
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b10000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // 0.00M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000100000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000000000;
  // -1.111M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000000110000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000010001010111;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0M
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000000000000000000000000;
  decimal_res.bits[2] = 0b00000000000000000000000000000000;
  decimal_res.bits[1] = 0b00000000000000000000000000000000;
  decimal_res.bits[0] = 0b00000000000000000000000000000000;
  // -0.00M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b10000000000000100000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000000000;
  // -1.111M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000000110000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000000010001010111;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 5M
  decimal_res = init_decimal();
  decimal_res.bits[0] = 0b00000000000000000000000000000101;
  // 15M
  decimal_1 = init_decimal();
  decimal_1.bits[0] = 0b00000000000000000000000000001111;
  // 3M
  decimal_2 = init_decimal();
  decimal_2.bits[0] = 0b00000000000000000000000000000011;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 5M
  decimal_res = init_decimal();
  decimal_res.bits[0] = 0b00000000000000000000000000000101;
  // 15.000M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000110000000000000000;
  decimal_1.bits[0] = 0b00000000000000000011101010011000;
  // 3.0000M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000001000000000000000000;
  decimal_2.bits[0] = 0b00000000000000000111010100110000;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 0.0000999999998964158763712194 scale 28 (29 total)
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000111000000000000000000;
  decimal_res.bits[2] = 0b00000000000000001101001111000010;
  decimal_res.bits[1] = 0b00011011110010110001111011010110;
  decimal_res.bits[0] = 0b00001100000100010011111011000010;
  // 556744564.879789
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000001100000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000011111101001011011;
  decimal_1.bits[0] = 0b00110010000001010011000110101101;
  // 5567445654564.879789789656M
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b00000000000011000000000000000000;
  decimal_2.bits[2] = 0b00000000000001001001101011110011;
  decimal_2.bits[1] = 0b11010101011011001111001101111000;
  decimal_2.bits[0] = 0b01111000100001010001000111011000;

  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // 9997571764.208666207833331872
  decimal_res = init_decimal();
  decimal_res.bits[3] = 0b00000000000100100000000000000000;
  decimal_res.bits[2] = 0b00100000010011011100110000101011;
  decimal_res.bits[1] = 0b01010001000101011100100011100110;
  decimal_res.bits[0] = 0b11000100110110001001100010100000;
  // -5567445654564.879789789656M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b10000000000011000000000000000000;
  decimal_1.bits[2] = 0b00000000000001001001101011110011;
  decimal_1.bits[1] = 0b11010101011011001111001101111000;
  decimal_1.bits[0] = 0b01111000100001010001000111011000;
  // -556.879789
  decimal_2 = init_decimal();
  decimal_2.bits[3] = 0b10000000000001100000000000000000;
  decimal_2.bits[2] = 0b00000000000000000000000000000000;
  decimal_2.bits[1] = 0b00000000000000000000000000000000;
  decimal_2.bits[0] = 0b00100001001100010100111110101101;
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(s21_res.bits[i], decimal_res.bits[i]);
  }
  ck_assert_int_eq(s21_res_status, 0);

  // DIVISION BY ZERO CHECK
  // 15M
  decimal_1 = init_decimal();
  decimal_1.bits[3] = 0b00000000000000000000000000000000;
  decimal_1.bits[2] = 0b00000000000000000000000000000000;
  decimal_1.bits[1] = 0b00000000000000000000000000000000;
  decimal_1.bits[0] = 0b00000000000000000000000000001111;
  // 0M
  decimal_2 = init_decimal();
  s21_res = init_decimal();
  s21_res_status = s21_div(decimal_1, decimal_2, &s21_res);
  ck_assert_int_eq(s21_res_status, 3);

  // NULL RESULT POINTER CHECK
  s21_res_status = s21_div(decimal_1, decimal_2, NULL);
  ck_assert_int_eq(s21_res_status, 4);
}
END_TEST

#endif
