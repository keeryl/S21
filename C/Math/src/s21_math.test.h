#ifndef S21_MATH_TEST_H
#define S21_MATH_TEST_H

#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_math.h"

START_TEST(test_abs) {
  for (int x = -1000; x < 1000; x += 100) {
    int abs_res = abs(x);
    int s21_abs_res = s21_abs(x);
    ck_assert_int_eq(abs_res, s21_abs_res);
  }
}
END_TEST

START_TEST(test_acos) {
  for (double x = -1; x <= 1; x += 0.015) {
    long double acos_res = acos(x);
    long double s21_acos_res = s21_acos(x);
    ck_assert_ldouble_eq_tol(acos_res, s21_acos_res, 1e-6);
  }
  ck_assert_ldouble_nan(s21_acos(-1.1));
  ck_assert_ldouble_nan(s21_acos(1.1));
  ck_assert_ldouble_eq(s21_acos(1), +0);
  ck_assert_ldouble_eq_tol(s21_acos(0), acos(0), 1e-6);

  ck_assert_ldouble_nan(acos(-1.1));
  ck_assert_ldouble_nan(acos(1.1));
  ck_assert_ldouble_eq(acos(1), +0);
}
END_TEST

START_TEST(test_asin) {
  for (double x = -1.0; x <= 1; x += 0.015) {
    long double asin_res = asin(x);
    long double s21_asin_res = s21_asin(x);
    ck_assert_ldouble_eq_tol(asin_res, s21_asin_res, 1e-6);
  }
  ck_assert_ldouble_nan(s21_asin(-1.1));
  ck_assert_ldouble_nan(s21_asin(1.1));
  ck_assert_ldouble_eq(s21_asin(0), +0);
  ck_assert_ldouble_eq_tol(s21_asin(1), asin(1), 1e-6);

  ck_assert_ldouble_nan(asin(-1.1));
  ck_assert_ldouble_nan(asin(1.1));
  ck_assert_ldouble_eq(asin(0), +0);
}
END_TEST

START_TEST(test_atan) {
  for (double x = -1100000; x < 1100000; x += 10505.333) {
    long double atan_res = atan(x);
    long double s21_atan_res = s21_atan(x);
    ck_assert_ldouble_eq_tol(atan_res, s21_atan_res, 1e-6);
  }

  for (double x = -10; x < 10; x += 0.25) {
    long double atan_res = atan(x);
    long double s21_atan_res = s21_atan(x);
    ck_assert_ldouble_eq_tol(atan_res, s21_atan_res, 1e-6);
  }
  ck_assert_ldouble_nan(s21_atan(NAN));
  ck_assert_ldouble_eq_tol(s21_atan(-INFINITY),
                           (-3.14159265358979323846264338327950288 / 2), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(INFINITY),
                           (3.14159265358979323846264338327950288 / 2), 1e-6);
  ck_assert_ldouble_eq(s21_atan(-0), -0);
  ck_assert_ldouble_eq(s21_atan(+0), +0);

  ck_assert_ldouble_nan(atan(NAN));
  ck_assert_ldouble_eq(atan(-INFINITY),
                       (-3.14159265358979323846264338327950288 / 2));
  ck_assert_ldouble_eq(atan(INFINITY),
                       (3.14159265358979323846264338327950288 / 2));
  ck_assert_ldouble_eq(atan(-0), -0);
  ck_assert_ldouble_eq(atan(+0), +0);
}
END_TEST

START_TEST(test_ceil) {
  for (double x = -1000.545; x < 1000; x += 100.345) {
    long double ceil_res = ceil(x);
    long double s21_ceil_res = s21_ceil(x);
    ck_assert_ldouble_eq(ceil_res, s21_ceil_res);
  }
  ck_assert_ldouble_infinite(s21_ceil(INFINITY));
  ck_assert_ldouble_infinite(s21_ceil(-INFINITY));
  ck_assert_ldouble_eq(s21_ceil(-INFINITY), -INFINITY);
  ck_assert_ldouble_eq(s21_ceil(INFINITY), INFINITY);
  ck_assert_ldouble_eq(s21_ceil(-0), 0);
  ck_assert_ldouble_eq(s21_ceil(+0), 0);
  ck_assert_ldouble_eq(s21_ceil(S21_FLT_MAX + 1000), ceil(S21_FLT_MAX + 1000));
  ck_assert_ldouble_nan(s21_ceil(NAN));

  ck_assert_ldouble_infinite(ceil(INFINITY));
  ck_assert_ldouble_infinite(ceil(-INFINITY));
  ck_assert_ldouble_eq(ceil(-INFINITY), -INFINITY);
  ck_assert_ldouble_eq(ceil(INFINITY), INFINITY);
  ck_assert_ldouble_eq(ceil(-0), 0);
  ck_assert_ldouble_eq(ceil(+0), 0);
  ck_assert_ldouble_nan(ceil(NAN));
}
END_TEST

START_TEST(test_cos) {
  for (double x = -1100000; x < 1100000; x += 10505.333) {
    long double cos_res = cos(x);
    long double s21_cos_res = s21_cos(x);
    ck_assert_ldouble_eq_tol(cos_res, s21_cos_res, 1e-6);
  }
  ck_assert_ldouble_nan(s21_cos(NAN));
  ck_assert_ldouble_nan(s21_cos(-INFINITY));
  ck_assert_ldouble_nan(s21_cos(INFINITY));
  ck_assert_ldouble_eq(s21_cos(0), 1);

  ck_assert_ldouble_nan(cos(NAN));
  ck_assert_ldouble_nan(cos(-INFINITY));
  ck_assert_ldouble_nan(cos(INFINITY));
  ck_assert_ldouble_eq(cos(0), 1);
}
END_TEST

START_TEST(test_exp) {
  for (double x = -50; x < 300.0; x += 1.6733) {
    long double exp_res = exp(x);
    long double s21_exp_res = s21_exp(x);
    if (exp_res < 1e10)
      ck_assert_ldouble_eq_tol(exp_res, s21_exp_res, 1e-6);
    else
      ck_assert_ldouble_lt(fabsl(exp_res - s21_exp_res) / fabsl(s21_exp_res),
                           1e-15);
  }

  ck_assert_ldouble_eq(s21_exp(0), 1);
  ck_assert_ldouble_eq(s21_exp(1), S21_EXP);
  ck_assert_ldouble_eq(s21_exp(+INFINITY), +INFINITY);
  ck_assert_ldouble_eq(s21_exp(-INFINITY), +0);
  ck_assert_ldouble_nan(s21_exp(NAN));

  ck_assert_ldouble_eq(exp(0), 1);
  ck_assert_ldouble_eq_tol(exp(1), s21_exp(1), 1e-6);
  ck_assert_ldouble_eq(exp(+INFINITY), +INFINITY);
  ck_assert_ldouble_eq(exp(-INFINITY), +0);
  ck_assert_ldouble_nan(exp(NAN));
}
END_TEST

#endif
