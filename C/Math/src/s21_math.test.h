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

START_TEST(test_fabs) {
  for (double x = -1000; x < 1000; x += 100.567) {
    double fabs_res = fabs(x);
    long double s21_fabs_res = s21_fabs(x);
    ck_assert_ldouble_eq((long double)fabs_res, s21_fabs_res);
  }
  ck_assert_ldouble_infinite(s21_fabs(INFINITY));
  ck_assert_ldouble_infinite(s21_fabs(-INFINITY));
  ck_assert_ldouble_eq(s21_fabs(-0), 0);
  ck_assert_ldouble_eq(s21_fabs(+0), 0);
  ck_assert_ldouble_nan(s21_fabs(NAN));

  ck_assert_ldouble_infinite(fabs(INFINITY));
  ck_assert_ldouble_infinite(fabs(-INFINITY));
  ck_assert_ldouble_eq(fabs(-0.0), 0);
  ck_assert_ldouble_eq(fabs(+0.0), 0);
  ck_assert_ldouble_nan(fabs(NAN));
}
END_TEST

START_TEST(test_floor) {
  for (double x = -5.055; x < 50; x += 0.05) {
    double floor_res = floor(x);
    long double s21_floor_res = s21_floor(x);
    ck_assert_ldouble_eq((long double)floor_res, s21_floor_res);
  }
  ck_assert_ldouble_infinite(s21_floor(INFINITY));
  ck_assert_ldouble_infinite(s21_floor(-INFINITY));
  ck_assert_ldouble_eq(s21_floor(-0), 0);
  ck_assert_ldouble_eq(s21_floor(+0), 0);
  ck_assert_ldouble_eq(s21_floor(S21_FLT_MAX + 1000),
                       floor(S21_FLT_MAX + 1000));
  ck_assert_ldouble_nan(s21_floor(NAN));

  ck_assert_ldouble_infinite(floor(INFINITY));
  ck_assert_ldouble_infinite(floor(-INFINITY));
  ck_assert_ldouble_eq(floor(-0), 0);
  ck_assert_ldouble_eq(floor(+0), 0);
  ck_assert_ldouble_nan(floor(NAN));
}
END_TEST

START_TEST(test_fmod) {
  for (double x = -100.50, y = -90.50; x < 100; x += 0.50, y += 0.35) {
    double fmod_res = fmod(x, y);
    long double s21_fmod_res = s21_fmod(x, y);
    ck_assert_ldouble_eq((long double)fmod_res, s21_fmod_res);
  }
  ck_assert_ldouble_eq((long double)fmod(-100, -101), s21_fmod(-100, -101));
  ck_assert_ldouble_eq((long double)fmod(100, 101), s21_fmod(100, 101));
  ck_assert_ldouble_eq(s21_fmod(10, INFINITY), 10);
  ck_assert_ldouble_eq(s21_fmod(10, -INFINITY), 10);
  ck_assert_ldouble_eq(s21_fmod(-0, 2), 0);
  ck_assert_ldouble_eq(s21_fmod(+0, 2), 0);
  ck_assert_ldouble_nan(s21_fmod(+0, NAN));
  ck_assert_ldouble_nan(s21_fmod(-0, NAN));
  ck_assert_ldouble_nan(s21_fmod(5, NAN));
  ck_assert_ldouble_nan(s21_fmod(-5, NAN));
  ck_assert_ldouble_nan(s21_fmod(NAN, -0));
  ck_assert_ldouble_nan(s21_fmod(NAN, +0));
  ck_assert_ldouble_nan(s21_fmod(NAN, 5));
  ck_assert_ldouble_nan(s21_fmod(NAN, -5));
  ck_assert_ldouble_nan(s21_fmod(101, 0));
  ck_assert_ldouble_nan(s21_fmod(INFINITY, 101));
  ck_assert_ldouble_nan(s21_fmod(-INFINITY, 101));

  ck_assert_ldouble_eq(fmod(10, INFINITY), 10);
  ck_assert_ldouble_eq(fmod(10, -INFINITY), 10);
  ck_assert_ldouble_eq(fmod(-0, 2), 0);
  ck_assert_ldouble_eq(fmod(+0, 2), 0);
  ck_assert_ldouble_nan(fmod(+0, NAN));
  ck_assert_ldouble_nan(fmod(-0, NAN));
  ck_assert_ldouble_nan(fmod(5, NAN));
  ck_assert_ldouble_nan(fmod(-5, NAN));
  ck_assert_ldouble_nan(fmod(NAN, -0));
  ck_assert_ldouble_nan(fmod(NAN, +0));
  ck_assert_ldouble_nan(fmod(NAN, 5));
  ck_assert_ldouble_nan(fmod(NAN, -5));
  ck_assert_ldouble_nan(fmod(101, 0));
  ck_assert_ldouble_nan(fmod(INFINITY, 101));
  ck_assert_ldouble_nan(fmod(-INFINITY, 101));
}
END_TEST

START_TEST(test_log) {
  for (double x = 1; x < 100; x += 0.50) {
    double log_res = log(x);
    long double s21_log_res = s21_log(x);
    ck_assert_ldouble_eq_tol((long double)log_res, s21_log_res, 1e-6);
  }
  ck_assert_ldouble_eq_tol((long double)log(10.23E+208), s21_log(10.23E+208),
                           1e-6);
  ck_assert_ldouble_infinite(s21_log(0));
  ck_assert_ldouble_infinite(s21_log(INFINITY));
  ck_assert_ldouble_eq(s21_log(1), 0);
  ck_assert_ldouble_nan(s21_log(-1));
  ck_assert_ldouble_nan(s21_log(NAN));

  ck_assert_ldouble_infinite(log(0));
  ck_assert_ldouble_infinite(log(INFINITY));
  ck_assert_ldouble_eq(log(1), 0);
  ck_assert_ldouble_nan(log(-1));
  ck_assert_ldouble_nan(log(NAN));
}
END_TEST

START_TEST(test_pow) {
  double x = 1.55;
  for (double y = -20.7; y < 1000; y += 1.555) {
    double pow_res = pow(x, y);
    long double s21_pow_res = s21_pow(x, y);
    if (pow_res < 1e10)
      ck_assert_ldouble_eq_tol((long double)pow_res, s21_pow_res, 1e-6);
    else
      ck_assert_ldouble_lt(
          fabsl((long double)pow_res - s21_pow_res) / fabsl(s21_pow_res),
          1e-15);
  }
}
END_TEST

START_TEST(test_pow_1) {
  ck_assert_ldouble_infinite(s21_pow(+0, -5));
  ck_assert_ldouble_infinite(s21_pow(+0, -6));
  ck_assert_ldouble_eq(s21_pow(0, -10), INFINITY);
  ck_assert_ldouble_eq(s21_pow(0, 9), 0);
  ck_assert_ldouble_eq(s21_pow(0, 10), +0);
  ck_assert_ldouble_eq(s21_pow(-1, INFINITY), 1);
  ck_assert_ldouble_eq(s21_pow(-1, -INFINITY), 1);
  ck_assert_ldouble_eq(s21_pow(1, NAN), 1);
  ck_assert_ldouble_eq(s21_pow(1, INFINITY), 1);
  ck_assert_ldouble_eq(s21_pow(1, -INFINITY), 1);
  ck_assert_ldouble_eq(s21_pow(1, 5), 1);
  ck_assert_ldouble_eq(s21_pow(1, -5), 1);
  ck_assert_ldouble_eq(s21_pow(1, 6), 1);
  ck_assert_ldouble_eq(s21_pow(1, -6), 1);
  ck_assert_ldouble_eq(s21_pow(1, 6.666), 1);
  ck_assert_ldouble_eq(s21_pow(NAN, 0), 1);
  ck_assert_ldouble_eq(s21_pow(INFINITY, 0), 1);
  ck_assert_ldouble_eq(s21_pow(-INFINITY, 0), 1);
  ck_assert_ldouble_eq(s21_pow(5, 0), 1);
  ck_assert_ldouble_eq(s21_pow(-5, 0), 1);
  ck_assert_ldouble_eq(s21_pow(6, 0), 1);
  ck_assert_ldouble_eq(s21_pow(-6, 0), 1);
  ck_assert_ldouble_eq(s21_pow(6.666, 0), 1);
  ck_assert_ldouble_nan(s21_pow(-10, 95.456));
  ck_assert_ldouble_eq(s21_pow(-0.333, -INFINITY), INFINITY);
  ck_assert_ldouble_eq(s21_pow(-4.333, -INFINITY), +0);
  ck_assert_ldouble_eq(s21_pow(-0.333, INFINITY), +0);
  ck_assert_ldouble_eq(s21_pow(-4.333, INFINITY), INFINITY);
  ck_assert_ldouble_eq(s21_pow(-INFINITY, -9), -0);
  ck_assert_ldouble_eq(s21_pow(-INFINITY, -10), +0);
  ck_assert_ldouble_eq(s21_pow(-INFINITY, 9), -INFINITY);
  ck_assert_ldouble_eq(s21_pow(-INFINITY, 10), INFINITY);
  ck_assert_ldouble_eq(s21_pow(INFINITY, -1.1), +0);
  ck_assert_ldouble_eq(s21_pow(INFINITY, 1.1), INFINITY);
  ck_assert_ldouble_nan(s21_pow(NAN, 3));
  ck_assert_ldouble_nan(s21_pow(3, NAN));

  ck_assert_ldouble_infinite(pow(+0, -5));
  ck_assert_ldouble_infinite(pow(-0, -5));
  ck_assert_ldouble_eq(pow(0, -10), INFINITY);
  ck_assert_ldouble_eq(pow(0, 9), 0);
  ck_assert_ldouble_eq(pow(0, 10), +0);
  ck_assert_ldouble_eq(pow(-1, INFINITY), 1);
  ck_assert_ldouble_eq(pow(-1, -INFINITY), 1);
  ck_assert_ldouble_eq(pow(1, NAN), 1);
  ck_assert_ldouble_eq(pow(1, INFINITY), 1);
  ck_assert_ldouble_eq(pow(1, -INFINITY), 1);
  ck_assert_ldouble_eq(pow(1, 5), 1);
  ck_assert_ldouble_eq(pow(1, -5), 1);
  ck_assert_ldouble_eq(pow(1, 6), 1);
  ck_assert_ldouble_eq(pow(1, -6), 1);
  ck_assert_ldouble_eq(pow(1, 6.666), 1);
  ck_assert_ldouble_eq(pow(NAN, 0), 1);
  ck_assert_ldouble_eq(pow(INFINITY, 0), 1);
  ck_assert_ldouble_eq(pow(-INFINITY, 0), 1);
  ck_assert_ldouble_eq(pow(5, 0), 1);
  ck_assert_ldouble_eq(pow(-5, 0), 1);
  ck_assert_ldouble_eq(pow(6, 0), 1);
  ck_assert_ldouble_eq(pow(-6, 0), 1);
  ck_assert_ldouble_eq(pow(6.666, 0), 1);
  ck_assert_ldouble_nan(pow(-10, 95.456));
  ck_assert_ldouble_eq(pow(-0.333, -INFINITY), INFINITY);
  ck_assert_ldouble_eq(pow(-4.333, -INFINITY), +0);
  ck_assert_ldouble_eq(pow(-0.333, INFINITY), +0);
  ck_assert_ldouble_eq(pow(-4.333, INFINITY), INFINITY);
  ck_assert_ldouble_eq(pow(-INFINITY, -9), -0);
  ck_assert_ldouble_eq(pow(-INFINITY, -10), +0);
  ck_assert_ldouble_eq(pow(-INFINITY, 9), -INFINITY);
  ck_assert_ldouble_eq(pow(-INFINITY, 10), INFINITY);
  ck_assert_ldouble_eq(pow(INFINITY, -1.1), +0);
  ck_assert_ldouble_eq(pow(INFINITY, 1.1), INFINITY);
  ck_assert_ldouble_nan(pow(NAN, 3));
  ck_assert_ldouble_nan(pow(3, NAN));
}
END_TEST

START_TEST(test_sin) {
  for (double x = -1100000; x < 1100000; x += 10505.333) {
    double sin_res = sin(x);
    long double s21_sin_res = s21_sin(x);
    ck_assert_ldouble_eq_tol((long double)sin_res, s21_sin_res, 1e-6);
  }
  for (double x = -10; x < 10; x += 0.333) {
    double sin_res = sin(x);
    long double s21_sin_res = s21_sin(x);
    ck_assert_ldouble_eq_tol((long double)sin_res, s21_sin_res, 1e-6);
  }
  ck_assert_ldouble_nan(s21_sin(NAN));
  ck_assert_ldouble_nan(s21_sin(-INFINITY));
  ck_assert_ldouble_nan(s21_sin(INFINITY));
  ck_assert_ldouble_eq(s21_sin(-0), -0);
  ck_assert_ldouble_eq(s21_sin(+0), +0);

  ck_assert_ldouble_nan(sin(NAN));
  ck_assert_ldouble_nan(sin(-INFINITY));
  ck_assert_ldouble_nan(sin(INFINITY));
  ck_assert_ldouble_eq(sin(-0), -0);
  ck_assert_ldouble_eq(sin(+0), +0);
}
END_TEST

#endif
