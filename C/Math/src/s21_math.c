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

