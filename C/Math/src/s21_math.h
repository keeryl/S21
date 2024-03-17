#ifndef S21_MATH_H
#define S21_MATH_H

#define S21_INF 1.0 / 0.0
#define S21_FLT_MAX 3.402823466e+38F
#define S21_EXP 2.7182818284590452353602874713527L
#define S21_EXP_15 3.0590232050182578837147949770228963937E-7
#define S21_SMALL_EPS 0.00000000001L
#define S21_DBL_MAX 1.7976931348623158e+308
#define S21_PI 3.14159265358979323846L
#define S21_NAN 0.0 / 0.0

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double e);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

int isInt(double x);
int isOdd(double x);
int isFinite(double x);
long double simple_pow(long double base, unsigned long long e);
long double binary_pow(long double base, unsigned long long e);
#endif
