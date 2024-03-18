#include "s21_math.h"

int s21_abs(int x) {
  int result = 0;
  if (x > 0) {
    result = x;
  } else {
    result = -x;
  }
  return result;
}

long double s21_acos(double x) {
  long double res = 0.0;
  if (x == 1)
    res = +0.0;
  else if (s21_fabs(x) > 1 || x != x)
    res = S21_NAN;
  else if (x == 0.0)
    res = 1.5707963267948965579989817342720925807952880859375;
  else if (x > 0)
    res = s21_atan(s21_sqrt(1.0 - (x * x)) / x);
  else
    res = S21_PI + s21_atan(s21_sqrt(1.0 - (x * x)) / x);
  return res;
}

long double s21_asin(double x) {
  long double res = 0.0;
  if (x == 0)
    res = 0.0;
  else if (s21_fabs(x) > 1 || x != x)
    res = S21_NAN;
  else if (x == 1.0)
    res = 1.5707963267948965579989817342720925807952880859375;
  else if (x == -1.0)
    res = -1.5707963267948965579989817342720925807952880859375;
  else
    res = s21_atan(x / s21_sqrt(1.0 - (x * x)));
  return res;
}

long double s21_atan(double x) {
  long double result = 0.0;
  if (x != x)
    result = S21_NAN;
  else if (x == 0.0)
    result = 0.0;
  else if (x == 1.0)
    result = 0.78539816339744827899949086713604629039764404296875;
  else if (x == -1.0)
    result = -0.78539816339744827899949086713604629039764404296875;
  else if (s21_fabs(x) == S21_INF)
    result = (x < 0) ? -S21_PI / 2.0 : S21_PI / 2.0;
  else if (x > 1)
    result = S21_PI / 2.0 - s21_atan(1.0 / x);
  else if (x < -1)
    result = -S21_PI / 2.0 - s21_atan(1.0 / x);
  else if (-1 < x && x < 1) {
    result = x;
    long double add = x;
    for (long long i = 1; i < 2000; i++) {
      add *= -x * x;
      result += add / (2.0 * i + 1.0);
    }
  }
  return result;
}

long double s21_ceil(double x) {
  long double result = (long long)x;
  if (x != x)
    result = S21_NAN;
  else if (x == 0.0)
    result = 0.0;
  else if (x == S21_INF)
    result = S21_INF;
  else if (x == -S21_INF)
    result = -S21_INF;
  else if (x <= -S21_FLT_MAX || x >= S21_FLT_MAX)
    result = x;
  else if (x > 0. && s21_fabs(x - result) > 0.)
    result += 1;
  return result;
}