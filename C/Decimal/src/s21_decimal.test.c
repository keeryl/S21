#include "arithmetic_operations/tests.h"

int main() {
  Suite *s;
  SRunner *sr;
  TCase *tc;
  printf("\n\n//////////// ARITHMETIC TESTS ////////////\n\n");
  s = suite_create("ARITHMETIC TESTS");
  tc = tcase_create("Test");

  tcase_add_test(tc, add);
  tcase_add_test(tc, sub);
  tcase_add_test(tc, mul);
  tcase_add_test(tc, division);
  tcase_add_test(tc, is_less);

  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}
