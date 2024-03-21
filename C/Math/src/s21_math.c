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

long double s21_cos(double x) {
  long double result = 0;
  if (x != x || s21_fabs(x) == S21_INF) {
    result = S21_NAN;
  } else if (x == 0) {
    result = 1;
  } else if (x < 0) {
    result = s21_cos(-x);
  } else if (x > S21_PI * 2) {
    result = s21_cos(s21_fmod(x, 2 * S21_PI));
  } else {
    result = 1;
    long double mul = -x * x;
    long double add = 1;
    for (int i = 1; i < 20; i++) {
      add = add * mul / (2 * i * (2 * i - 1));
      result += add;
    }
  }
  return result;
}

long double s21_exp(double x) {
  long double res = 0.0;
  if (x != x)
    res = S21_NAN;
  else if (x == 0)
    res = 1.0;
  else if (x == -S21_INF)
    res = +0.0;
  else if (x == S21_INF)
    res = S21_INF;
  else {
    long double x_int = s21_floor(s21_fabs(x));
    long double x_dbl = s21_fabs(x) - s21_floor(s21_fabs(x));
    if (x_int != 0) res = binary_pow(S21_EXP, x_int);
    if (x_dbl > 0) {
      long double add_value = 1.0;
      long double i = 1.0;
      long double dbl_res = 0.0;
      do {
        dbl_res += add_value;
        add_value *= x_dbl / i;
        i += 1.0;
        if (dbl_res > S21_DBL_MAX) {
          dbl_res = S21_INF;
          break;
        }
      } while (s21_fabs(add_value) > 1e-16);
      res = (x_int > 0) ? res * dbl_res : dbl_res;
    }
    if (x < 0) res = 1.0 / res;
  }
  return res;
}

long double s21_fabs(double x) {
  long double res = (long double)x;
  if (res < 0) res = -res;
  if (res == S21_INF || res == -S21_INF) res = S21_INF;
  return res;
}

long double s21_floor(double x) {
  long double result = (long long)x;
  if ((x == S21_INF || x == -S21_INF) || x != x)
    return x;
  else if (x <= -S21_FLT_MAX || x >= S21_FLT_MAX)
    result = x;
  if (x < 0. && s21_fabs(x - result) > 0.) result -= 1;
  return result;
}

long double s21_fmod(double x, double y) {
  long double res = 0.0;
  long double div_res = x / y;
  if (x == S21_INF || x == -S21_INF || y == 0 || y != y || x != x)
    res = S21_NAN;
  else if (x == 0 && y == y)
    res = 0.0;
  else if ((y == S21_INF || y == -S21_INF) && (x != S21_INF && x != -S21_INF))
    res = x;
  else if ((x > 0 && x < y) || (x < 0 && x > y))
    res = x;
  else if (div_res > 0)
    res = x - y * s21_floor(div_res);
  else if (div_res < 0)
    res = x - y * s21_ceil(div_res);
  return res;
}

long double s21_log(double x) {
  long double res = 0.0;
  if (x == 0)
    res = -S21_INF;
  else if (x == 1)
    res = 0;
  else if (x < 0 || x != x)
    res = S21_NAN;
  else if (x == S21_INF)
    res = S21_INF;
  else {
    double ln = 0;
    double ln1 = ln + 0.5;
    while (s21_fabs(ln - ln1) > 1e-12) {
      ln = ln1;
      ln1 = ln + 2 * (x - s21_exp(ln)) / (x + s21_exp(ln));
    }
    res = ln1;
  }
  return res;
}

long double s21_pow(double base, double e) {
  long double res = 0.0;
  if (base == 0 && (isInt(e) && isOdd(e) && e < 0.0))
    res = S21_INF;
  else if (base == 0 && (isInt(e) && !isOdd(e) && e < 0.0))
    res = S21_INF;
  else if (base == 0 && (isInt(e) && isOdd(e) && e > 0.0))
    res = 0.0;
  else if (base == 0 && (isInt(e) && !isOdd(e) && e > 0.0))
    res = +0.0;
  else if (base == -1 && (e == -S21_INF || e == S21_INF))
    res = 1.0;
  else if (base == 1 || e == 0)
    res = 1.0;
  else if (base < 0 && isFinite(base) && !isInt(e) && isFinite(e))
    res = S21_NAN;
  else if (e == -S21_INF && s21_fabs(base) < 1)
    res = S21_INF;
  else if (e == -S21_INF && s21_fabs(base) > 1)
    res = +0.0;
  else if (e == S21_INF && s21_fabs(base) < 1)
    res = +0.0;
  else if (e == S21_INF && s21_fabs(base) > 1)
    res = S21_INF;
  else if (base == -S21_INF && (isInt(e) && isOdd(e) && e < 0.0))
    res = -0;
  else if (base == -S21_INF && (isInt(e) && !isOdd(e) && e < 0.0))
    res = +0;
  else if (base == -S21_INF && (isInt(e) && isOdd(e) && e > 0.0))
    res = -S21_INF;
  else if (base == -S21_INF && (isInt(e) && !isOdd(e) && e > 0.0))
    res = S21_INF;
  else if (base == S21_INF && e < 0.0)
    res = +0.0;
  else if (base == S21_INF && e > 0.0)
    res = S21_INF;
  else if (base != base || e != e)
    res = S21_NAN;
  else {
    long double e_int = s21_floor(s21_fabs(e));
    long double e_dbl = s21_fabs(e) - s21_floor(s21_fabs(e));
    if (e_int == 0)
      res = s21_exp(e_dbl * s21_log(base));
    else
      res = simple_pow(base, e_int) * s21_exp(e_dbl * s21_log(base));
    if (e < 0) res = 1.0 / res;
  }
  return res;
}

long double s21_sin(double x) {
  long double res = 0.0;
  if (x == 0.0)
    res = 0.0;
  else if (x == S21_INF || x == -S21_INF || x != x)
    res = S21_NAN;
  else {
    long double f = 1;
    long double sin = s21_fmod(x, 2 * S21_PI);
    long double p = sin;
    while (s21_fabs(p) > 1e-12) {
      res += p;
      p = (-1) * p * (sin * sin) / ((2 * f + 1) * (2 * f));
      f++;
    }
  }
  return res;
}

long double s21_sqrt(double x) {
  long double res = 0.0;
  if (x == -0)
    res = -0.0;
  else if (x < 0)
    res = S21_NAN;
  else
    res = s21_pow(x, 0.5);
  return res;
}

long double s21_tan(double x) {
  long double res = 0.0;
  if (x == 0)
    res = 0.0;
  else if (x == S21_INF || x == -S21_INF || x != x)
    res = S21_NAN;
  else
    res = s21_sin(x) / s21_cos(x);
  return res;
}

int isInt(double x) {
  return (s21_fabs(x) - s21_floor(s21_fabs(x)) == 0) ? 1 : 0;
}

int isOdd(double x) {
  long long int_x = s21_fabs(x);
  return (int_x % 2 == 0) ? 0 : 1;
}

int isFinite(double x) {
  return (x != -S21_INF && x != S21_INF && x == x) ? 1 : 0;
}

long double simple_pow(long double base, unsigned long long e) {
  long double res = 0.0;
  long double val = base;
  for (unsigned long long i = 0; i < e - 1; i++) val *= base;
  res = val;
  return res;
}

long double binary_pow(long double base, unsigned long long e) {
  long double v = 1.0;
  while (e != 0) {
    if ((e & 1) != 0) {
      v *= base;
    }
    base *= base;
    e >>= 1;
  }
  return v;
}