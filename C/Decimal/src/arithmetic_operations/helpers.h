#ifndef S21_ARITHMETIC_HELPERS_H
#define S21_ARITHMETIC_HELPERS_H

#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

typedef struct {
  unsigned bits[8];
} s21_bd;

// bd = big decimal

enum arithmetic_status_code { OK, LARGE, SMALL, DIVISION_ZERO, ERROR };

void print_s21_decimal(s21_decimal *dst);
void print_s21_bd(s21_bd *dst);
void print_int_binary(int x);
void set_bit_bd(s21_bd *bd, int idx, int val);
void set_scale_bd(s21_bd *bd, int val);
void set_scale(s21_decimal *decimal, int val);
void set_sign_bd(s21_bd *bd, int val);
void set_sign(s21_decimal *dec, int val);
void normalize_bd(s21_bd *bd_1, s21_bd *bd_2);
void handle_normalization_bd(s21_bd *bd);
void scale_down_bd_if_overflow(s21_bd *bd);
void scale_down_bd(s21_bd *bd);
void mul_by_ten_bd(s21_bd *bd);
void convert_bd_to_decimal(s21_bd *result_bd, s21_decimal *result);
void handle_bank_rounding_bd(s21_bd *res_bd, s21_bd remainder);
void handle_div_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res, int sign);
void handle_add_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res, int sc, int sign);
void handle_sub_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res, int sc, int sign);
void handle_mul_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res, int sc, int sign);
void bitwise_add_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res);
void bitwise_sub_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res);
void bitwise_mul_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res);
s21_bd bitwise_div_bd(s21_bd bd_1, s21_bd bd_2, s21_bd *res);
s21_bd init_bd(void);
s21_bd convert_to_bd(s21_decimal dec);
s21_bd shift_left_bd(s21_bd bd, int shift_val);
s21_decimal init_decimal(void);
int compare_bd(s21_bd bd_1, s21_bd bd_2);
int get_bit_bd(s21_bd bd, int idx);
int get_scale_bd(s21_bd bd);
int get_scale(s21_decimal dec);
int get_sign_bd(s21_bd bd);
int get_sign(s21_decimal dec);
int is_zero_bd(s21_bd bd);
int is_zero_decimal(s21_decimal dec);
int is_overflow_in_decimal(const s21_bd *res_bd);
int handle_result(s21_bd *result_bd, s21_decimal *result);
int count_digits_bd(s21_bd bd);

#endif