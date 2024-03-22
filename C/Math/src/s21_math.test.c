#include "s21_math.test.h"

int main() {
  Suite *s;
  SRunner *sr;
  TCase *tc;
  s = suite_create("S21_MATH TESTS");
  tc = tcase_create("Test");

  tcase_add_test(tc, test_abs);
  tcase_add_test(tc, test_acos);
  tcase_add_test(tc, test_asin);
  tcase_add_test(tc, test_atan);
  tcase_add_test(tc, test_ceil);
  tcase_add_test(tc, test_cos);
  tcase_add_test(tc, test_exp);
  tcase_add_test(tc, test_fabs);
  tcase_add_test(tc, test_floor);
  tcase_add_test(tc, test_fmod);
  tcase_add_test(tc, test_log);
  tcase_add_test(tc, test_pow);
  tcase_add_test(tc, test_pow_1);
  tcase_add_test(tc, test_sin);
  tcase_add_test(tc, test_sqrt);
  tcase_add_test(tc, test_tan);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}