#include "s21_cat.test.h"

void makeTestFile();

int main() {
  makeTestFile();
  test("cat", "s21_cat", test_cases, TEST_CASES_QTY);
  return 0;
}

void makeTestFile() {
  FILE *file = fopen("test.txt", "w");
  fprintf(file, "\n");
  fprintf(file, "\n");
  for (int i = 0; i <= 127; i++) {
    char c = (char)i;
    fprintf(file, "%d - %c\n", i, c);
    fprintf(file, "\n");
    fprintf(file, "\n");
  }
  fclose(file);
}
