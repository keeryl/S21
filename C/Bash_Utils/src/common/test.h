#ifndef TEST
#define TEST

#include <stdio.h>

void test(const char *orig_cmd, const char *test_cmd, const char **test_cases,
          int test_cases_cnt);
void leak_test(const char *test_cmd, const char **test_cases,
               int test_cases_cnt);

void test(const char *orig_cmd, const char *test_cmd, const char **test_cases,
          int test_cases_cnt) {
  printf("Testing %s...\n\n", test_cmd);
  int fails = 0, success = 0;
  for (int i = 0; i < test_cases_cnt; i++) {
    int test_res = 1;
    printf("Testing case: %s\n\n", test_cases[i]);
    char original_command[1024];
    char testing_command[1024];
    sprintf(original_command, "%s %s", orig_cmd, test_cases[i]);
    sprintf(testing_command, "./%s %s", test_cmd, test_cases[i]);
    FILE *original_output = popen(original_command, "r");
    FILE *testing_output = popen(testing_command, "r");
    char testing_char;
    char original_char;
    int line_count = 0;
    while ((testing_char = getc(testing_output)) != EOF) {
      original_char = getc(original_output);
      if (testing_char == '\n') line_count += 1;
      if (testing_char != original_char) {
        test_res = 0;
        fails += 1;
        break;
      }
    }
    success += test_res;
    if (test_res != 1) {
      printf("\tTest result: FAILED\n\n");
      printf("\tREASON: original char %d != testing char %d in line %d\n\n",
             original_char, testing_char, line_count);
    } else {
      printf("\tTest result: SUCCESS\n\n");
    }
    pclose(original_output);
    pclose(testing_output);
  }
  printf("TESTS DONE: %d\n", test_cases_cnt);
  printf("FAILS: %d\n", fails);
  printf("SUCCESS: %d\n\n", success);
}

#endif