#include "s21_matrix.test.h"

int main() {
  Suite *s;
  SRunner *sr;
  TCase *tc;
  printf("\n\n//////////// MATRIX TESTS ////////////\n\n");
  s = suite_create("MATRIX TESTS");
  tc = tcase_create("Test");

  tcase_add_test(tc, create_matrix);
  tcase_add_test(tc, create_matrix_1);
  tcase_add_test(tc, create_matrix_2);
  tcase_add_test(tc, create_matrix_3);
  tcase_add_test(tc, equal_matrix);
  tcase_add_test(tc, equal_matrix_1);
  tcase_add_test(tc, equal_matrix_2);
  tcase_add_test(tc, sum_matrix);
  tcase_add_test(tc, sum_matrix_1);
  tcase_add_test(tc, sum_matrix_2);
  tcase_add_test(tc, sum_matrix_3);
  tcase_add_test(tc, sum_matrix_4);
  tcase_add_test(tc, sub_matrix);
  tcase_add_test(tc, sub_matrix_1);
  tcase_add_test(tc, sub_matrix_2);
  tcase_add_test(tc, sub_matrix_3);
  tcase_add_test(tc, sub_matrix_4);
  tcase_add_test(tc, mult_number);
  tcase_add_test(tc, mult_number_1);
  tcase_add_test(tc, mult_number_2);
  tcase_add_test(tc, mult_number_3);
  tcase_add_test(tc, mult_number_4);
  tcase_add_test(tc, mult_number_5);
  tcase_add_test(tc, mult_matrix_1);
  tcase_add_test(tc, mult_matrix_2);
  tcase_add_test(tc, mult_matrix_3);
  tcase_add_test(tc, mult_matrix_4);
  tcase_add_test(tc, mult_matrix_5);
  tcase_add_test(tc, transpose_1);
  tcase_add_test(tc, transpose_2);
  tcase_add_test(tc, transpose_3);
  tcase_add_test(tc, calc_complements_1);
  tcase_add_test(tc, calc_complements_2);
  tcase_add_test(tc, calc_complements_3);
  tcase_add_test(tc, calc_complements_4);
  tcase_add_test(tc, calc_complements_5);
  tcase_add_test(tc, calc_complements_6);
  tcase_add_test(tc, determinant_1);
  tcase_add_test(tc, determinant_2);
  tcase_add_test(tc, determinant_3);
  tcase_add_test(tc, determinant_4);
  tcase_add_test(tc, determinant_5);
  tcase_add_test(tc, determinant_6);
  tcase_add_test(tc, inverse_1);
  tcase_add_test(tc, inverse_2);
  tcase_add_test(tc, inverse_3);
  tcase_add_test(tc, inverse_4);
  tcase_add_test(tc, inverse_5);
  tcase_add_test(tc, inverse_6);

  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}