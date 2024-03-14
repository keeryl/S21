#include "arithmetic_operations/tests.h"
#include "other/tests.h"

int main() {
  Suite *s;
  SRunner *sr;
  TCase *tc;
  printf("\n\n//////////// DECIMAL TESTS ////////////\n\n");
  s = suite_create("DECIMAL TESTS");
  tc = tcase_create("Test");

  tcase_add_test(tc, addn);  // addition
  tcase_add_test(tc, subn);  // substraction
  tcase_add_test(tc, muln);  // multiplication
  tcase_add_test(tc, divn);  // division
  tcase_add_test(tc, trun);  // truncate
  tcase_add_test(tc, flr);   // floor
  tcase_add_test(tc, rnd);   // round

  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}
